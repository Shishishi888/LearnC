#include <stdio.h>
#include <malloc.h>
#define OK 1
#define ERROR 0
typedef int SElemType;

typedef struct{
    int top[2], bot[2];     //栈顶和栈底指针
    SElemType *v;           //栈数组
    int m;                  //栈最大可容纳元素个数
}DblStack;

int InitDblStack(DblStack *S, int m){                        //初始化
    S->top[0]=S->bot[0]=-1;                                  //左栈的栈顶和栈底指针
    S->top[1]=S->bot[1]=m;                                   //右栈的栈顶和栈底指针

    S->v=(SElemType *)malloc(sizeof(SElemType)*m);
}

int DblPush(DblStack *S, int i, SElemType x){                //进栈
    if(IsFull(S))
        return ERROR;
    if(i==0)
        S->v[++S->top[i]]=x;
    else
        S->v[--S->top[i]]=x;
    return OK;
}

int DblPop(DblStack *S, int i, SElemType *x){                //出栈
                                                             //当需要修改一个指针的时候,需要使用它的二级指针
    if(IsEmpty(S))
        return ERROR;
    if(i==0)
        *x=S->v[S->top[i]--];
    else
        *x=S->v[S->top[i]++];
}

int IsEmpty(DblStack *S, int i){                             //栈空
    return S->top[i]==S->bot[i];
}

int IsFull(DblStack *S){                                     //栈满
    if(S->top[1]-S->top[0]==1)
        return 1;
    else
        return 0;
}

void main(){
    DblStack dblStack;
    InitDblStack(&dblStack , 10);

    if(IsEmpty(&dblStack, 0)) printf("左栈为空\n");
    else                      printf("左栈不为空\n");
    if(IsEmpty(&dblStack, 1)) printf("右栈为空\n");
    else                      printf("右栈不为空\n");
    if(IsFull(&dblStack))     printf("双栈已满\n");
    else                      printf("双栈未满\n");
    printf("\n");

    DblPush(&dblStack, 0, 11);
    DblPush(&dblStack, 0, 12);
    DblPush(&dblStack, 0, 13);
    DblPush(&dblStack, 0, 14);

    if(IsEmpty(&dblStack, 0)) printf("左栈为空\n");
    else                      printf("左栈不为空\n");
    if(IsEmpty(&dblStack, 1)) printf("右栈为空\n");
    else                      printf("右栈不为空\n");
    if(IsFull(&dblStack))     printf("双栈已满\n");
    else                      printf("双栈未满\n");
    printf("\n");

    DblPush(&dblStack, 1, 20);
    DblPush(&dblStack, 1, 19);
    DblPush(&dblStack, 1, 18);
    DblPush(&dblStack, 1, 17);
    DblPush(&dblStack, 1, 16);
    DblPush(&dblStack, 1, 15);

    if(IsEmpty(&dblStack, 0)) printf("左栈为空\n");
    else                      printf("左栈不为空\n");
    if(IsEmpty(&dblStack, 1)) printf("右栈为空\n");
    else                      printf("右栈不为空\n");
    if(IsFull(&dblStack))     printf("双栈已满\n");
    else                      printf("双栈未满\n");
    printf("\n");

    int x;
    DblPop(&dblStack, 0, &x);                                //当需要修改一个指针的时候,需要使用它的二级指针
    printf("出栈元素为：%d\n", x);
    if(IsEmpty(&dblStack, 0)) printf("左栈为空\n");
    else                      printf("左栈不为空\n");
    if(IsEmpty(&dblStack, 1)) printf("右栈为空\n");
    else                      printf("右栈不为空\n");
    if(IsFull(&dblStack))     printf("双栈已满\n");
    else                      printf("双栈未满\n");
    printf("\n");

    DblPop(&dblStack, 1, &x);
    printf("出栈元素为：%d\n", x);
    if(IsEmpty(&dblStack, 0)) printf("左栈为空\n");
    else                      printf("左栈不为空\n");
    if(IsEmpty(&dblStack, 1)) printf("右栈为空\n");
    else                      printf("右栈不为空\n");
    if(IsFull(&dblStack))     printf("双栈已满\n");
    else                      printf("双栈未满\n");
    printf("\n");
}

/*
    将编号为0和1的两个栈存放于一个数组空间v[m]中，栈底分别处于数组的两端。当第0号栈的栈顶指针top[0]等于-1时该栈为空；
    当第1号栈的栈顶指针top[1]等于m时，该站为空。两个栈均从两端向中间增长。试编写双栈初始化，判断栈空、栈满、进栈和出栈等算法的函数。
    双栈数据结构的定义如下：
    typedef struct{
        int top[2], bot[2];     //栈顶和栈底指针
        SElemType *v;           //栈数组
        int m;                  //栈最大可容纳元素个数
    }DblStack;
*/
