//프로젝트명 : Project #3 Express Stack using Array
//작성자 : naNana
//작성일 : 2022년 5월 23일 월요일
//알고리즘 설명 : 0 ~ 9까지의 정수만을 포함하는 중위표기식을 입력받아 후위표기식으로 바꾼 후 계산을 수행한다. 배열로 스택을 구현한다.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX 50

typedef struct Stack //배열을 이용한 스택 구현
{
    int top;
    float data[MAX];
} Stack;

void postfix(char *f_org, char *result);
float evaluate(char *f_post);
char stackTop(Stack *st);
char pop(Stack *st);
float pop_evaluate(Stack *st);
void push(Stack *st, float key);
int pre(char x);

int main(void)
{
    char f_infix[MAX] = {'\0'};
    char F_postfix[MAX] = {'\0'};
    int i = 0;

    scanf("%[^\n]", f_infix); // 엔터 입력할 때까지 입력 받기

    //(1)중위표기식을 후위표기식으로 변환
    postfix(f_infix, F_postfix);                     //후위표기식으로 변환
    printf("(1) 후위표기식 변환 : %s\n", F_postfix); //변환된 후위표기식 출력

    //(2) 후위표기식 계산
    printf("(2) 계산 결과 : %.2f\n", evaluate(F_postfix)); //후위표기식 계산 결과 출력

    return 0;
}

//(1)중위표기식을 후위표기식으로 변환
void postfix(char *f_org, char *result)
{
    Stack stack; //스택 선언, 초기화
    stack.top = -1;

    char ch, op, check;
    int index = 0;

    int i = 0;
    while ((i < MAX) && ((ch = f_org[i]) != '\0'))
    {
        // printf("%c\n", ch);
        if (isdigit(ch) && index < MAX - 1)
        {
            result[index++] = ch;
            // printf("%s\n", result);
        }

        else
        {
            switch (ch)
            {
            case '+':
            case '-':
            case '*':
            case '/':
            case '%':
            case '^':
                check = stackTop(&stack);
                while (check != 'e' && pre(ch) <= pre(check))
                {
                    op = pop(&stack);
                    // printf("%c", op);
                    result[index++] = op;
                    check = stackTop(&stack);
                }
                push(&stack, ch);
                break;

            case '(':
                push(&stack, ch);
                break;

            case ')':

                check = stackTop(&stack);
                // printf("%c\n", check);
                while (check != 'e' && check != '(')
                {
                    result[index++] = check;
                    pop(&stack);
                    check = stackTop(&stack);
                }
                pop(&stack);
                break;
            }
        }
        i++;
    }
    while (stack.top > -1)
    {
        op = pop(&stack);
        if (op != '(')
        {
            result[index++] = op;
        }
    }
}

// 후위표기식 계산
float evaluate(char *f_post)
{
    Stack stack; //스택 선언, 초기화
    stack.top = -1;

    int i = 0;
    char ch;
    float op1, op2, value = 0;

    while ((ch = f_post[i++]) != '\0')
    {
        if (isdigit(ch))
        {
            value = ch - '0'; //문자를 숫자로 변환해서 스택에 저장
            push(&stack, value);
        }
        else
        {
            op2 = pop_evaluate(&stack);
            op1 = pop_evaluate(&stack);
            switch (ch)
            {
            case '+':
                push(&stack, op1 + op2);
                break;
            case '-':
                push(&stack, op1 - op2);
                break;
            case '*':
                push(&stack, op1 * op2);
                break;
            case '/':
                push(&stack, op1 / op2);
                break;
            case '%':
                push(&stack, (int)op1 % (int)op2);
                break;
            case '^':
                push(&stack, (int)op1 ^ (int)op2);
                break;
            }
        }
        // printf("%.1f  ", stackTop(&stack));
    }
    return stackTop(&stack);
}

char stackTop(Stack *st)
{
    if (st->top > -1 && st->top < MAX)
    {
        char value = st->data[st->top];
        // printf("%c\n", value);
        return value;
    }
    return 'e';
}

char pop(Stack *st)
{
    if (st->top > -1)
    {
        char value = st->data[st->top];
        st->top--;
        return value;
    }
    return 'e';
}

float pop_evaluate(Stack *st)
{
    if (st->top > -1)
    {
        float value = st->data[st->top];
        st->top--;
        return value;
    }
    return -1;
}

void push(Stack *st, float key)
{
    if (st->top < MAX - 1) // top++ 되므로 48이하여야 함(용량 50일 때)
    {
        st->top++;
        st->data[st->top] = key;
    }
}

//연산자 우선순위를 반환하는 함수
int pre(char x)
{
    if (x == '(')
        return 0;
    if (x == '+' || x == '-')
        return 1;
    if (x == '*' || x == '/' || x == '%')
        return 2;

    if (x == '^')
        return 3;

    return 100;
}