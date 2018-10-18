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

int InitStack(SqStack *S){//栈的初始化
    S->base=(SElemType *)malloc(sizeof(SElemType)*MAXSIZE);
    if(!S->base)
        exit(0);
    S->top=S->base;
    S->stacksize=MAXSIZE;
    return OK;
}

int Push(SqStack *S, SElemType e){//进栈
    if(IsFull(S))
        return ERROR;
    *(S->top++)=e;
    return OK;
}

int Pop(SqStack *S, SElemType *e){//出栈
    if(IsEmpty(S))
        return ERROR;
    *e=*(--S->top);
    return OK;
}

double GetTop(SqStack *S){//取栈顶元素
    if(S->top!=S->base)
        return *(S->top-1);
}

int IsEmpty(SqStack *S){//栈空
    return S->top==S->base;
}

int IsFull(SqStack *S){//栈满
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
    printf("请输入后缀表达式（'$'为结束符）:\n");
    printf("计算结果为：%5f", Postfix());
}

/*
    从键盘输入一个后缀表达式，试编写算法计算表达式的值。规定：逆波兰表达式的长度不超过一行，以“$”作为结束符，
    操作数之间用空格分隔，操作符号只可能有+、-、*、/四种运算。例如：234 34+2*$
*/
