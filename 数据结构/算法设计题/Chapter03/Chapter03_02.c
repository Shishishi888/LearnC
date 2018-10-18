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

int InitStack(SqStack *S){                   //ջ�ĳ�ʼ��
    S->base=(SElemType *)malloc(sizeof(SElemType)*MAXSIZE);
    if(!S->base)
        exit(0);
    S->top=S->base;
    S->stacksize=MAXSIZE;
    return OK;
}

int Push(SqStack *S, SElemType e){           //��ջ
    if(S->top-S->base==S->stacksize)
        return ERROR;
    *(S->top++)=e;
    return OK;
}

int Pop(SqStack *S, SElemType *e){           //��ջ
    if(S->top==S->base)
        return ERROR;
    *e=*(--S->top);
    return OK;
}

int IsEmpty(SqStack *S){                     //ջ��
    return S->top==S->base;
}

int strlen(char str[]){                      //�����ַ����ĳ���
    int count=0;
    while(*str!='\0'){
        count++;
        str++;
    }
    return count;
}

int IsHuiWen(char str[]){                    //�ж��Ƿ�Ϊ��������
    SqStack S;
    InitStack(&S);

    int i;
    for(i=0; i<strlen(str)/2; i++)
        Push(&S, str[i]);

    if(strlen(str)%2!=0)                     //����������еĳ���Ϊ����
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
       printf("%s�����ַ������ǻ�������\n",str1);
    else
       printf("%s�����ַ����в��ǻ�������\n",str1);

    char str2[]="abdba";
    if(IsHuiWen(str2))
       printf("%s�����ַ������ǻ�������\n",str2);
    else
       printf("%s�����ַ����в��ǻ�������\n",str2);

    char str3[]="good";
    if(IsHuiWen(str3))
       printf("%s�����ַ������ǻ�������\n",str3);
    else
       printf("%s�����ַ����в��ǻ�������\n",str3);
}

/*
  ������ָ������������ͬ���ַ����У��硰abba���͡�abdba�����ǻ��ġ�����good�����ǻ��ġ�
  ��дһ���㷨�ж��������ַ������Ƿ�Ϊ���ġ�����ʾ����һ���ַ���ջ��
*/
