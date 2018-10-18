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

int InitStack(SqStack *S){             //栈的初始化
    S->base=(int *)malloc(sizeof(int)*MAXSIZE);
    if(!S->base)
        exit(0);
    S->top=S->base;
    S->stacksize=MAXSIZE;
    return OK;
}

int Push(SqStack *S, int e){           //进栈
    if(IsFull(S))
        return ERROR;
    *(S->top++)=e;
    return OK;
}

int Pop(SqStack *S, int *e){           //出栈
                                       //出栈
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

void main(){
    SqStack stack;
    InitStack(&stack);

    while(1){
        int num;
        printf("请输入即将入栈的整数：");
        scanf("%d",&num);

        if(num!=-1){
            if(IsFull(&stack))
                printf("该栈已满！\n");
            else{
                Push(&stack, num);
                printf("入栈成功！\n");
            }
        }
        else{
            if(IsEmpty(&stack))
                printf("该栈为空栈！\n");
            else{
                int e;
                Pop(&stack, &e);
                printf("出栈成功！出栈元素为：%d\n", e);
            }
        }
    }
}

/*
    设从键盘输入一整数的序列：a1,a2,a3, ... ,an，试编写算法实现：用栈结构储存输入的整数，
    当ai!=-1时，将ai进栈；当ai=-1时，输出栈顶整数并出栈。算法应对异常情况（入栈满等）给出
    相应的信息。
*/
