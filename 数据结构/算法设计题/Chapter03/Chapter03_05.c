#include <stdio.h>
#include <malloc.h>
#include <string.h>
#define OK 1
#define ERROR 0
#define MAXSIZE 20
typedef char SElemType;

typedef struct{
    SElemType *base;
    SElemType *top;
    int stacksize;
}SqStack;

int InitStack(SqStack *S){                   //栈的初始化
    S->base=(SElemType *)malloc(sizeof(SElemType)*MAXSIZE);
    if(!S->base)
        exit(0);
    S->top=S->base;
    S->stacksize=MAXSIZE;
    return OK;
}

int Push(SqStack *S, SElemType e){           //进栈
    if(IsFull(S))
        return ERROR;
    *(S->top++)=e;
    return OK;
}

int Pop(SqStack *S, SElemType *e){          //出栈
    if(IsEmpty(S))
        return ERROR;
    *e=*(--S->top);
    return OK;
}

int IsEmpty(SqStack *S){              //栈空
    return S->top==S->base;
}

int IsFull(SqStack *S){               //栈满
    return S->top-S->base==S->stacksize;
}

//方法1
int IsLegal(char str[]){
    SqStack stack;
    InitStack(&stack);

    for(int i=0; i<strlen(str); i++){
        if(str[i]=='I'){
            if(IsFull(&stack))
                return ERROR;
            else
                Push(&stack, str[i]);
        }
        else if(str[i]=='O'){
            if(IsEmpty(&stack))
                return ERROR;
            else{
                char e;
                Pop(&stack, &e);
            }
        }
    }
    if(IsEmpty(&stack))
        return OK;
    else
        return ERROR;
}

//方法2
/*
int IsLegal(char str[]){
    int i=0;
    int j=0, k=0;

    while(str[i]!='\0'){
        switch(str[i]){
            case 'I':j++; break;
            case 'O':k++;
            if(j<k)
                return ERROR;
        }
        i++;
    }

    if(j!=k)
        return ERROR;
    else
        return OK;
}
*/

void main(){
    char str1[]="IOIIOIOO";
    if(IsLegal(str1)) printf("字符序列%s合法！\n",str1);
    else              printf("该字符序列%s不合法！\n",str1);

    char str2[]="IOOIOIIO";
    if(IsLegal(str2)) printf("该字符序列%s合法！\n",str2);
    else              printf("该字符序列%s不合法！\n",str2);

    char str3[]="IIIOIOIO";
    if(IsLegal(str3)) printf("该字符序列%s合法！\n",str3);
    else              printf("该字符序列%s不合法！\n",str3);

    char str4[]="IIIOOIOO";
    if(IsLegal(str4)) printf("该字符序列%s合法！\n",str4);
    else              printf("该字符序列%s不合法！\n",str4);
}
/*
    假设以I和O分别表示入栈和出栈操作。栈的初态和终态均为空，入站和出栈的操作序列可表示为
    仅由I和O组成的序列，称可以操作的序列为合法序列，否则成为非法序列。
    1.下面所示的序列中哪些是合法的？
    A.IOIIOIOO B.IOOIOIIO C.IIIOIOIO D.IIIOOIOO

    2.通过对1的分析，写出一个算法，判定所给的操作序列是否合法。若合法，返回true，
      否则返回false（假定被判定的操作序列已存放入一维数组中）。
*/
