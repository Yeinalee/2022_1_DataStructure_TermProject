//프로젝트명 : Project #2 Selection Sort using Bi-directional Circular Linked List
//작성자 : naNana
//작성일 : 2022년 5월 22일 일요일
//알고리즘 설명 : 12개의 정수를 입력 받아 선택 정렬을 수행하고 원소의 합과 평균을 구한다. (이중원형연결리스트 이용)

#include <stdio.h>
#include <stdlib.h>
#define MAX 12

typedef struct node //이중연결리스트의 노드 구조체
{
    struct node *rp;
    struct node *lp;
    int data;
} node;

int insert_node(node *list, node **pre, int key);
void sort_node(node *list);
void printr(node *list);
void printl(node *list);

int main(void)
{
    int sum = 0;

    // bcList생성, 초기화
    node *bcList = (node *)malloc(sizeof(node)); //헤더노드의 포인터
    bcList->rp = NULL;
    bcList->lp = NULL;
    node *now = bcList;

    // bcList 만들기 + 리스트 상태 순회하며 출력
    int k = 0;
    for (int i = 0; i < MAX; i++)
    {
        scanf("%d", &k);
        insert_node(bcList, &now, k);
        printf("현재 리스트의 상태(우측 순회) : ");
        printr(bcList);
        printf("현재 리스트의 상태(좌측 순회) : ");
        printl(bcList);
        printf("\n");
    }

    printf("\n선택 정렬 수행(순서가 바뀌게 되는 경우에만 출력)\n");
    // bcList 정렬하기
    sort_node(bcList);

    //오름차순 출력
    printf("\n오름차순 : ");
    printr(bcList);

    //내림차순 출력
    printf("내림차순 : ");

    //원소의 합 구하기
    node *sump = bcList;
    while (sump != bcList->rp)
    {
        sum += sump->rp->data;
        sump = sump->rp;
    }

    //원소의 합 sum과 평균 출력
    printf("\n원소의 합 : %d\n원소의 평균 : %.2f\n", sum, (float)sum / MAX);

    return 0;
}

// list에 인자로 전달된 key값 삽입
int insert_node(node *list, node **pre, int key)
{
    node *new = (node *)malloc(sizeof(node));
    new->data = key;
    if (*pre == list) //빈 노드(첫번째 노드) 삽입 방법
    {
        new->rp = new;
        new->lp = new;
        list->rp = new;
        list->lp = new;
    }

    else
    {
        list->lp = new;
        list->rp->lp = new;
        (**pre).rp = new;
        new->lp = *pre;
        new->rp = list->rp;
    }
    *pre = new;
    return (**pre).data; //추가된 data return
}

//선택 정렬 사용
void sort_node(node *list)
{
    node *stand = list->rp;

    while (stand != (list->lp->lp))
    {
        node *min = stand;
        node *trace = stand;

        while (trace != (list->lp))
        {
            if ((min->data) > (trace->rp->data))
            {
                min = trace->rp;
            }
            trace = trace->rp; //한 칸 전진
        }
        // printf("%d  ", min->data);

        if (min != stand) // swap하는 과정
        {
            node *temp = (node *)malloc(sizeof(node));
            temp->data = stand->data;

            min->rp->lp = temp;
            min->lp->rp = temp;
            stand->rp->lp = min;
            stand->lp->rp = min;

            temp->rp = min->rp;
            temp->lp = min->lp;
            min->rp = stand->rp;
            min->lp = stand->lp;

            if (min == list->lp) //최솟값이 리스트의 마지막 값일 때
            {
                list->lp = temp;
                temp->rp = list->rp;
            }

            if (stand == list->rp) //기준값이 리스트의 첫번째 노드일 때
            {
                list->rp = min;
                min->lp = list->lp;
            }

            if (min == list->lp)
            {
                temp->rp = list->rp;
            }

            if (temp->lp == stand) //양 옆 교환할 때
            {
                temp->lp = min;
            }

            // printf("%p\n", list->rp);
            // printf("%p\n", list->lp);
            // printf("%p\n", min);
            // printf("%p\n", temp);
            printr(list);
        }
        stand = min->rp;
    }
}

void printr(node *list)
{
    node *print = list;
    while (print != list->lp)
    {
        printf("%d ", print->rp->data);
        print = print->rp;
    }
    printf("\n");
}

void printl(node *list)
{
    node *print = list;
    while (print != list->rp)
    {
        printf("%d ", print->lp->data);
        print = print->lp;
    }
    printf("\n");
}
