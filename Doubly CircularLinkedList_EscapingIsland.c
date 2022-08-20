//프로젝트명 : Project #6 Doubly Circular Linked List for Escaping Island
//작성자 : naNana
//작성일 : 2022년 5월 23일 월요일
//알고리즘 설명 : 이중원형연결리스트를 사용하여 섬에서 살아남을 사람을 뽑는다.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX 11
#define SURVIVE 3

typedef struct Node
{
    int order;
    char data;
    struct Node *lp;
    struct Node *rp;
} Node;

void insert_node(Node *Head, Node **pre, char name, int su, int *k);
void delete (Node **trace, Node *headd, int *k);
void printr(Node *headd);

int main(void)
{
    srand(time(NULL));
    int skip_num = rand() % 9 + 1;                                              // 뽑은 임의의 번호
    char people[MAX] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K'}; //사람들 이름
    int num = 0;                                                                //남아있는 사람 수

    // 이중원형연결리스트 생성, 초기화
    Node *head = (Node *)malloc(sizeof(Node));
    head->rp = NULL;
    head->lp = NULL;
    Node *tailr = head->rp;

    //(1) 원형연결리스트 만들기
    for (int i = 0; i < MAX; i++)
    {
        insert_node(head, &tailr, people[i], i + 1, &num);
        printf("\n현재 리스트에 추가된 사람 : ");
        printr(head);
    }

    printf("\nskip number : %d\n순방향으로 회전하는 경우 ", skip_num);

    //순방향으로 돌 때
    Node *trail = head->rp; //첫번째 노드부터 시작
    while (num > SURVIVE)   //남은 사람이 살아남을 사람보다 클 경우 반복
    {
        for (int i = 0; i < skip_num; i++)
        {
            trail = trail->rp;
        }

        printf("\n탈락하는 사람 : [%d] - %c\n", trail->order, trail->data); //지워지는 사람
        delete (&trail, head, &num);
        printf("남아있는 사람들 : ");
        printr(head);
        // trail = trail->rp;
    }

    printf("\n시계 방향으로 회전할 때 살아남은 사람 : ");
    printr(head);

    printf("\n역방향으로 회전하는 경우");
    // 이중원형연결리스트 생성, 초기화
    Node *headl = (Node *)malloc(sizeof(Node));
    headl->rp = NULL;
    headl->lp = NULL;
    Node *taill = headl->rp;
    num = 0;

    //(2) 원형연결리스트 만들기
    for (int i = 0; i < MAX; i++)
    {
        insert_node(headl, &taill, people[i], i + 1, &num);
    }

    //역방향으로 돌 때
    Node *traill = headl->rp; //첫번째 노드부터 시작
    while (num > SURVIVE)
    {
        for (int i = 0; i < skip_num; i++)
        {
            traill = traill->lp;
        }

        printf("\n탈락하는 사람 : [%d] - %c  \n", traill->order, traill->data); //지워지는 사람
        delete (&traill, headl, &num);
        printf("남아있는 사람들 : ");
        printr(headl);
        // traill = traill->lp;
    }
    printf("\n반시계 방향으로 회전할 때 살아남은 사람 : ");
    printr(headl);

    return 0;
}

void insert_node(Node *Head, Node **tail, char name, int su, int *k) //뒤쪽에 노드 삽입
{
    Node *temp = (Node *)malloc(sizeof(Node));
    temp->data = name;
    temp->order = su;
    if (!(Head->rp))
    {
        temp->rp = temp;
        temp->lp = temp;
        Head->rp = temp;
        Head->lp = temp;
    }
    else
    {
        temp->lp = *tail;
        temp->rp = Head->rp;
        Head->lp = temp;
        Head->rp->lp = temp;
        (**tail).rp = temp;
    }
    (*k)++;
    *tail = temp;
}

void delete (Node **trace, Node *headd, int *k)
{
    if ((*trace) == headd->rp)
    {
        headd->rp = (*trace)->rp;
    }
    if ((*trace) == headd->lp)
    {
        headd->lp = (*trace)->lp;
    }

    (*trace)->rp->lp = (*trace)->lp;
    (*trace)->lp->rp = (*trace)->rp;

    Node *del = (*trace);
    (*trace) = (*trace)->rp;
    free(del);
    (*k)--;
}

void printr(Node *headd)
{
    Node *print = headd;
    while (print != headd->lp)
    {
        printf("[%d] - %c  ", print->rp->order, print->rp->data);
        print = print->rp;
    }
    printf("\n");
}