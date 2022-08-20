//프로젝트명 : Project #1 Selection Sort Using Array
//작성자 : naNana
//작성일 : 2022년 5월 22일 일요일
//알고리즘 설명 : 12개의 정수를 입력 받아 선택 정렬을 수행하고 원소의 합과 평균을 구한다. (배열 이용)

#include <stdio.h>
#define MAX 12 //입력 개수 최댓값 12

void sorting(int a[]);

int main(void)
{
    int ArrL[MAX] = {0};
    int sum = 0;

    //수를 입력할 때 마다 현재 배열의 상태 출력
    for (int i = 0; i < MAX; i++)
    {
        scanf("%d", &ArrL[i]);
        printf("현재 배열의 상태 : ");
        for (int j = 0; j < i + 1; j++)
        {
            printf("%d ", ArrL[j]);
        }
        printf("\n");
    }

    //선택 정렬
    printf("\n선택 정렬 수행(순서가 바뀌게 되는 경우에만 출력)\n");
    sorting(ArrL);

    printf("\n배열 출력(오름차순) : ");
    for (int i = 0; i < MAX; i++)
    {
        printf("%d ", ArrL[i]);
        sum += ArrL[i];
    }

    printf("\n역순으로 배열 출력(내림차순) : ");
    for (int i = MAX - 1; i > -1; i--)
    {
        printf("%d ", ArrL[i]);
    }

    printf("\n원소의 합 : %d\n원소의 평균 : %.2f\n", sum, ((float)sum / MAX));

    return 0;
}

void sorting(int a[])
{
    for (int i = 0; i < MAX - 1; i++)
    {
        int min = i;
        for (int j = i; j < MAX; j++)
        {
            if (a[min] > a[j])
                min = j;
        }

        //숫자의 순서가 바뀌는 경우
        if (min != i)
        {
            int temp = a[min]; // swap 수행
            a[min] = a[i];
            a[i] = temp;
            for (int k = 0; k < MAX; k++) //바뀐 순서 출력
            {
                printf("%d ", a[k]);
            }
            printf("\n");
        }
    }
}
