#include <stdio.h>
#include <malloc.h>
#include <string.h>
#define OK 1
#define ERROR 0
#define MAXSIZE 20
typedef double SElemType;

typedef struct{
    SElemType *base;
    SElemType *top;
    int stacksize;
}SqStack;

int InitStack(SqStack *S){//ջ�ĳ�ʼ��
    S->base=(SElemType *)malloc(sizeof(SElemType)*MAXSIZE);
    if(!S->base)
        exit(0);
    S->top=S->base;
    S->stacksize=MAXSIZE;
    return OK;
}

int Push(SqStack *S, SElemType e){//��ջ
    if(IsFull(S))
        return ERROR;
    *(S->top++)=e;
    return OK;
}

int Pop(SqStack *S, SElemType *e){//��ջ
    if(IsEmpty(S))
        return ERROR;
    *e=*(--S->top);
    return OK;
}

double GetTop(SqStack *S){//ȡջ��Ԫ��
    if(S->top!=S->base)
        return *(S->top-1);
}

int IsEmpty(SqStack *S){//ջ��
    return S->top==S->base;
}

int IsFull(SqStack *S){//ջ��
    return S->top-S->base==S->stacksize;
}

double Postfix(){
    SqStack stack;
    InitStack(&stack);

    double num=0.0;

    char ch=getchar();
    while(ch!='$'){
        int i=0;
        char data[5];
        while((ch>='0'&&ch<='9')||ch=='.'){
            data[i]=ch;
            i++;
            ch=getchar();
        }

        num=atof(data);
        Push(&stack, num);

        double a, b;
        switch(ch){
            case ' ': break;
            case '+': Pop(&stack, &b); Pop(&stack, &a); Push(&stack, a+b); break;
            case '-': Pop(&stack, &b); Pop(&stack, &a); Push(&stack, a-b); break;
            case '*': Pop(&stack, &b); Pop(&stack, &a); Push(&stack, a*b); break;
            case '/': Pop(&stack, &b); Pop(&stack, &a); Push(&stack, a/b); break;
        }

        ch=getchar();
    }

    return GetTop(&stack);
}

void main(){
    printf("�������׺���ʽ��'$'Ϊ��������:\n");
    printf("������Ϊ��%5f", Postfix());
}

/*
    �Ӽ�������һ����׺���ʽ���Ա�д�㷨������ʽ��ֵ���涨���沨�����ʽ�ĳ��Ȳ�����һ�У��ԡ�$����Ϊ��������
    ������֮���ÿո�ָ�����������ֻ������+��-��*��/�������㡣���磺234 34+2*$
*/
