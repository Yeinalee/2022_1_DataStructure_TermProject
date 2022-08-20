//프로젝트명 : Project #5 Singly Circular Linked List for Escaping Island
//작성자 : naNana
//작성일 : 2022년 5월 23일 월요일
//알고리즘 설명 : 원형연결리스트를 사용하여 섬에서 살아남을 사람을 뽑는다.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX 11    //전체 사람 수
#define SURVIVE 3 // 3인승 배

typedef struct Node
{
    int order;
    char data;
    struct Node *link;
} Node;

void insert_node(Node **tail, char name, int su, int *k);
void delete (Node **pretrace, Node **trace, Node **Tail, int *k);

int main(void)
{
    srand(time(NULL));
    int skip_num = rand() % 9 + 1;                                              // 뽑은 임의의 번호
    char people[MAX] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K'}; //사람들 이름
    int num = 0;                                                                //남아있는 사람 수

    // 원형연결리스트 생성, 초기화
    Node *tail = NULL; //꼬리 노드를 가리키는 포인터

    //(1) 원형연결리스트 만들기
    for (int i = 0; i < MAX; i++)
    {
        insert_node(&tail, people[i], i + 1, &num);
    }
    Node *head = tail->link;  //리스트 시작
    Node *trail = tail->link; //첫번째 노드부터 시작

    //초기 상태 출력
    printf("초기 사람들 번호 : ");
    for (int i = 0; i < num; i++)
    {
        printf("[%d] - %c  ", head->order, head->data);
        head = head->link;
    }

    printf("\nskip number : %d\n", skip_num); // skip_number 출력

    while (num > SURVIVE)
    {
        Node *pretrail = NULL;
        for (int i = 0; i < skip_num; i++)
        {
            pretrail = trail;
            trail = trail->link;
        }

        printf("탈락하는 사람 : [%d] - %c\n", trail->order, trail->data); //빠지는 사람
        delete (&pretrail, &trail, &head, &num);
        printf("남아있는 사람들 : ");
        for (int i = 0; i < num; i++) //남아았는 사람들의 리스트
        {
            printf("[%d] - %c  ", head->order, head->data);
            head = head->link;
        }
        printf("\n\n");
    }

    printf("살아남은 사람 : ");
    for (int i = 0; i < SURVIVE; i++)
    {
        printf("[%d] - %c  ", head->order, head->data);
        head = head->link;
    }
    return 0;
}

void insert_node(Node **Tail, char name, int su, int *k) //뒤쪽 노드 삽입
{
    Node *temp = (Node *)malloc(sizeof(Node));
    temp->data = name;
    temp->order = su;
    if (!(*Tail)) //첫 노드
    {
        temp->link = temp;
        *Tail = temp;
    }
    else
    {
        temp->link = (*Tail)->link;
        (*Tail)->link = temp;
        (*Tail) = temp;
    }
    (*k)++;
    // printf("%p", tail);
}

void delete (Node **pretrace, Node **trace, Node **headd, int *k)
{
    if (k > 0)
    {
        (*pretrace)->link = (*trace)->link;
    }

    if ((*trace) == (*headd))
    {
        // printf("%p\n", *headd);
        (*headd) = (*trace)->link;
        // printf("%p\n", *headd);
    }
    (*pretrace) = (*trace);
    (*trace) = (*trace)->link;
    free((*pretrace));
    (*k)--;
}