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

int InitStack(SqStack *S){                   //ջ�ĳ�ʼ��
    S->base=(SElemType *)malloc(sizeof(SElemType)*MAXSIZE);
    if(!S->base)
        exit(0);
    S->top=S->base;
    S->stacksize=MAXSIZE;
    return OK;
}

int Push(SqStack *S, SElemType e){           //��ջ
    if(IsFull(S))
        return ERROR;
    *(S->top++)=e;
    return OK;
}

int Pop(SqStack *S, SElemType *e){          //��ջ
    if(IsEmpty(S))
        return ERROR;
    *e=*(--S->top);
    return OK;
}

int IsEmpty(SqStack *S){              //ջ��
    return S->top==S->base;
}

int IsFull(SqStack *S){               //ջ��
    return S->top-S->base==S->stacksize;
}

//����1
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

//����2
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
    if(IsLegal(str1)) printf("�ַ�����%s�Ϸ���\n",str1);
    else              printf("���ַ�����%s���Ϸ���\n",str1);

    char str2[]="IOOIOIIO";
    if(IsLegal(str2)) printf("���ַ�����%s�Ϸ���\n",str2);
    else              printf("���ַ�����%s���Ϸ���\n",str2);

    char str3[]="IIIOIOIO";
    if(IsLegal(str3)) printf("���ַ�����%s�Ϸ���\n",str3);
    else              printf("���ַ�����%s���Ϸ���\n",str3);

    char str4[]="IIIOOIOO";
    if(IsLegal(str4)) printf("���ַ�����%s�Ϸ���\n",str4);
    else              printf("���ַ�����%s���Ϸ���\n",str4);
}
/*
    ������I��O�ֱ��ʾ��ջ�ͳ�ջ������ջ�ĳ�̬����̬��Ϊ�գ���վ�ͳ�ջ�Ĳ������пɱ�ʾΪ
    ����I��O��ɵ����У��ƿ��Բ���������Ϊ�Ϸ����У������Ϊ�Ƿ����С�
    1.������ʾ����������Щ�ǺϷ��ģ�
    A.IOIIOIOO B.IOOIOIIO C.IIIOIOIO D.IIIOOIOO

    2.ͨ����1�ķ�����д��һ���㷨���ж������Ĳ��������Ƿ�Ϸ������Ϸ�������true��
      ���򷵻�false���ٶ����ж��Ĳ��������Ѵ����һά�����У���
*/
