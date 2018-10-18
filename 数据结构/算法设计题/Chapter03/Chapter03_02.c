#include <stdio.h>
#include <malloc.h>
#define OK 1
#define ERROR 0
#define MAXSIZE 100
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
    if(S->top-S->base==S->stacksize)
        return ERROR;
    *(S->top++)=e;
    return OK;
}

int Pop(SqStack *S, SElemType *e){           //出栈
    if(S->top==S->base)
        return ERROR;
    *e=*(--S->top);
    return OK;
}

int IsEmpty(SqStack *S){                     //栈空
    return S->top==S->base;
}

int strlen(char str[]){                      //计算字符串的长度
    int count=0;
    while(*str!='\0'){
        count++;
        str++;
    }
    return count;
}

int IsHuiWen(char str[]){                    //判断是否为回文序列
    SqStack S;
    InitStack(&S);

    int i;
    for(i=0; i<strlen(str)/2; i++)
        Push(&S, str[i]);

    if(strlen(str)%2!=0)                     //如果回文序列的长度为奇数
        i++;

    while(!IsEmpty(&S)){
        char e;
        Pop(&S, &e);
        if(e!=str[i])
            return ERROR;
        i++;
    }
    return OK;
}

void main(){
    char str1[]="abba";
    if(IsHuiWen(str1))
       printf("%s：该字符序列是回文序列\n",str1);
    else
       printf("%s：该字符序列不是回文序列\n",str1);

    char str2[]="abdba";
    if(IsHuiWen(str2))
       printf("%s：该字符序列是回文序列\n",str2);
    else
       printf("%s：该字符序列不是回文序列\n",str2);

    char str3[]="good";
    if(IsHuiWen(str3))
       printf("%s：该字符序列是回文序列\n",str3);
    else
       printf("%s：该字符序列不是回文序列\n",str3);
}

/*
  回文是指正读反读均相同的字符序列，如“abba”和“abdba”均是回文。但“good”不是回文。
  试写一个算法判定给定的字符序列是否为回文。（提示：将一半字符入栈）
*/
