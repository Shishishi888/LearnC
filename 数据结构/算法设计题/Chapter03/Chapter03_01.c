#include <stdio.h>
#include <malloc.h>
#define OK 1
#define ERROR 0
typedef int SElemType;

typedef struct{
    int top[2], bot[2];     //ջ����ջ��ָ��
    SElemType *v;           //ջ����
    int m;                  //ջ��������Ԫ�ظ���
}DblStack;

int InitDblStack(DblStack *S, int m){                        //��ʼ��
    S->top[0]=S->bot[0]=-1;                                  //��ջ��ջ����ջ��ָ��
    S->top[1]=S->bot[1]=m;                                   //��ջ��ջ����ջ��ָ��

    S->v=(SElemType *)malloc(sizeof(SElemType)*m);
}

int DblPush(DblStack *S, int i, SElemType x){                //��ջ
    if(IsFull(S))
        return ERROR;
    if(i==0)
        S->v[++S->top[i]]=x;
    else
        S->v[--S->top[i]]=x;
    return OK;
}

int DblPop(DblStack *S, int i, SElemType *x){                //��ջ
                                                             //����Ҫ�޸�һ��ָ���ʱ��,��Ҫʹ�����Ķ���ָ��
    if(IsEmpty(S))
        return ERROR;
    if(i==0)
        *x=S->v[S->top[i]--];
    else
        *x=S->v[S->top[i]++];
}

int IsEmpty(DblStack *S, int i){                             //ջ��
    return S->top[i]==S->bot[i];
}

int IsFull(DblStack *S){                                     //ջ��
    if(S->top[1]-S->top[0]==1)
        return 1;
    else
        return 0;
}

void main(){
    DblStack dblStack;
    InitDblStack(&dblStack , 10);

    if(IsEmpty(&dblStack, 0)) printf("��ջΪ��\n");
    else                      printf("��ջ��Ϊ��\n");
    if(IsEmpty(&dblStack, 1)) printf("��ջΪ��\n");
    else                      printf("��ջ��Ϊ��\n");
    if(IsFull(&dblStack))     printf("˫ջ����\n");
    else                      printf("˫ջδ��\n");
    printf("\n");

    DblPush(&dblStack, 0, 11);
    DblPush(&dblStack, 0, 12);
    DblPush(&dblStack, 0, 13);
    DblPush(&dblStack, 0, 14);

    if(IsEmpty(&dblStack, 0)) printf("��ջΪ��\n");
    else                      printf("��ջ��Ϊ��\n");
    if(IsEmpty(&dblStack, 1)) printf("��ջΪ��\n");
    else                      printf("��ջ��Ϊ��\n");
    if(IsFull(&dblStack))     printf("˫ջ����\n");
    else                      printf("˫ջδ��\n");
    printf("\n");

    DblPush(&dblStack, 1, 20);
    DblPush(&dblStack, 1, 19);
    DblPush(&dblStack, 1, 18);
    DblPush(&dblStack, 1, 17);
    DblPush(&dblStack, 1, 16);
    DblPush(&dblStack, 1, 15);

    if(IsEmpty(&dblStack, 0)) printf("��ջΪ��\n");
    else                      printf("��ջ��Ϊ��\n");
    if(IsEmpty(&dblStack, 1)) printf("��ջΪ��\n");
    else                      printf("��ջ��Ϊ��\n");
    if(IsFull(&dblStack))     printf("˫ջ����\n");
    else                      printf("˫ջδ��\n");
    printf("\n");

    int x;
    DblPop(&dblStack, 0, &x);                                //����Ҫ�޸�һ��ָ���ʱ��,��Ҫʹ�����Ķ���ָ��
    printf("��ջԪ��Ϊ��%d\n", x);
    if(IsEmpty(&dblStack, 0)) printf("��ջΪ��\n");
    else                      printf("��ջ��Ϊ��\n");
    if(IsEmpty(&dblStack, 1)) printf("��ջΪ��\n");
    else                      printf("��ջ��Ϊ��\n");
    if(IsFull(&dblStack))     printf("˫ջ����\n");
    else                      printf("˫ջδ��\n");
    printf("\n");

    DblPop(&dblStack, 1, &x);
    printf("��ջԪ��Ϊ��%d\n", x);
    if(IsEmpty(&dblStack, 0)) printf("��ջΪ��\n");
    else                      printf("��ջ��Ϊ��\n");
    if(IsEmpty(&dblStack, 1)) printf("��ջΪ��\n");
    else                      printf("��ջ��Ϊ��\n");
    if(IsFull(&dblStack))     printf("˫ջ����\n");
    else                      printf("˫ջδ��\n");
    printf("\n");
}

/*
    �����Ϊ0��1������ջ�����һ������ռ�v[m]�У�ջ�׷ֱ�����������ˡ�����0��ջ��ջ��ָ��top[0]����-1ʱ��ջΪ�գ�
    ����1��ջ��ջ��ָ��top[1]����mʱ����վΪ�ա�����ջ�����������м��������Ա�д˫ջ��ʼ�����ж�ջ�ա�ջ������ջ�ͳ�ջ���㷨�ĺ�����
    ˫ջ���ݽṹ�Ķ������£�
    typedef struct{
        int top[2], bot[2];     //ջ����ջ��ָ��
        SElemType *v;           //ջ����
        int m;                  //ջ��������Ԫ�ظ���
    }DblStack;
*/
