#include <stdio.h>
#include <malloc.h>
#define MAXSIZE 20                                          //顺序表成员的最大数量
#define OK 1
#define ERROR 0

typedef int ElemType;

typedef struct{
    ElemType *elem;
    int length;                                         //顺序表的成员个数
    int list_size;                                      //顺序表占的内存空间大小
}SqList;

int InitList(SqList *L){//初始化顺序表
    L->elem=(ElemType *)malloc(MAXSIZE*sizeof(ElemType));             //为顺序表分配一个内存空间，顺序表的成员类型为整型
    if(!L->elem)
        exit(0);
    L->length=0;
    L->list_size=MAXSIZE;
    return OK;
}

void CreateList(SqList *L){//创建顺序表
    if(!L->elem)
        exit(0);
    for(int i=0; i<L->list_size; i++){
        int e;
        scanf("%d", &e);

        if(e==-1)
            break;

        L->elem[i]=e;
        L->length++;
    }
}

void ListTraverse(SqList L){//遍历顺序表
    if(!L.elem) exit(0);

    for(int i=0; i<L.length; i++)
        printf("%3d", L.elem[i]);

    /*
    for(int i=0; i<L.length; i++){
        printf("%3d", *L.elem);
        L.elem++;
    }
    */
}

void DeleteItem(SqList *L, ElemType item){//删除顺序表中指定的元素
    int k=0;
    for(int i=0; i<L->length; i++){
        if(L->elem[i]!=item){
            L->elem[k]=L->elem[i];
            k++;
        }
    }
    L->length=k;
}

void main(){

    printf("请先创建一个顺序表L：\n");
    SqList L;
    InitList(&L);
    CreateList(&L);
    printf("创建成功！顺序L的遍历结果为：");
    ListTraverse(L);
    printf("\n");

    printf("请输入要删除的元素：");
    int item;
    scanf("%d", &item);
    DeleteItem(&L, item);
    printf("删除成功！删除后的结果为：");
    ListTraverse(L);
}

/*
    已知长度为n的线性表A采用顺序储存结构，请写一个时间复杂度为o(n)、空间复杂度为o(1)的
    算法，该算法可删除线性表中所有值为item的数据元素。
*/
