#include <stdio.h>
#include <malloc.h>
#define OK 1
#define ERROR 0
#define MAXSIZE 20

typedef struct{
    int *base;
    int *top;
    int stacksize;
}SqStack;

int InitStack(SqStack *S){             //ջ�ĳ�ʼ��
    S->base=(int *)malloc(sizeof(int)*MAXSIZE);
    if(!S->base)
        exit(0);
    S->top=S->base;
    S->stacksize=MAXSIZE;
    return OK;
}

int Push(SqStack *S, int e){           //��ջ
    if(IsFull(S))
        return ERROR;
    *(S->top++)=e;
    return OK;
}

int Pop(SqStack *S, int *e){           //��ջ
                                       //��ջ
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

void main(){
    SqStack stack;
    InitStack(&stack);

    while(1){
        int num;
        printf("�����뼴����ջ��������");
        scanf("%d",&num);

        if(num!=-1){
            if(IsFull(&stack))
                printf("��ջ������\n");
            else{
                Push(&stack, num);
                printf("��ջ�ɹ���\n");
            }
        }
        else{
            if(IsEmpty(&stack))
                printf("��ջΪ��ջ��\n");
            else{
                int e;
                Pop(&stack, &e);
                printf("��ջ�ɹ�����ջԪ��Ϊ��%d\n", e);
            }
        }
    }
}

/*
    ��Ӽ�������һ���������У�a1,a2,a3, ... ,an���Ա�д�㷨ʵ�֣���ջ�ṹ���������������
    ��ai!=-1ʱ����ai��ջ����ai=-1ʱ�����ջ����������ջ���㷨Ӧ���쳣�������ջ���ȣ�����
    ��Ӧ����Ϣ��
*/
