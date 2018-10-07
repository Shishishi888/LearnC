#include <stdio.h>
#include <malloc.h>
#define MAXSIZE 20                //顺序表的最大长度

typedef struct{
    int key;                      //关键字
    char otherinfo[20];           //其他信息
}RedType;                         //记录类型

typedef struct{
    RedType r[MAXSIZE+1];         //r[0]闲置或用作哨兵
    int length;                   //顺序表长度
}SqList;                          //顺序表类型

/*简单选择排序*/
void SelectSort(SqList *L){
    int i;
    for(i=1; i<L->length; i++){
        int k=i;
        int j;
        for(j=i+1; j<=L->length; j++){
            if(L->r[j].key<L->r[k].key)
                k=j;                            //k指向此趟排序中关键字最小的记录
        }
        if(k!=i){
            RedType t=L->r[i];
            L->r[i]=L->r[k];
            L->r[k]=t;
        }
    }
}

/*堆排序*/
void HeapAdjust(SqList *L, int s, int m){       //筛选法调整堆
                                                //假设r[s+1...m]已经是堆，将r[s...m]调整为以r[s]为根的大根堆
    RedType rc=L->r[s];
    int j;
    for(j=2*s; j<=m; j*=2){
        if(j<m&&L->r[j].key<L->r[j+1].key)
            j++;                                //j为k较大记录的下标
        if(rc.key>=L->r[j].key)                 //判断以r[s]为根的二叉树是否为堆：如果根结点r[s]的记录大于或等于较大子结点r[j]的记录，则以r[s]为根的二叉树为堆,无需调整，跳出循环
            break;
        L->r[s]=L->r[j];                        //将根结点r[s]替换为较大子结点r[j]
        s=j;                                    //s指向j，继续for循环，调整以新的r[s]为根的堆
    }
    L->r[s]=rc;
}

void CreatHeap(SqList *L){                      //初建堆
    int n=L->length;
    int i;
    for(i=n/2; i>0; i--)
        HeapAdjust(L, i, n);
}

void HeapSort(SqList *L){                       //堆排序
    CreatHeap(L);
    int i;
    for(i=L->length; i>1; i--){
        RedType x=L->r[1];
        L->r[1]=L->r[i];
        L->r[i]=x;
        HeapAdjust(L, 1, i-1);
    }
}

void main(){
SqList *L=(SqList *)malloc(sizeof(SqList));
    L->r[1].key=5;
    L->r[2].key=6;
    L->r[3].key=7;
    L->r[4].key=4;
    L->r[5].key=9;
    L->r[6].key=9;
    L->r[7].key=44;
    L->r[8].key=32;
    L->r[9].key=12;
    L->length=9;

    SqList *temp=(SqList *)malloc(sizeof(SqList));
    temp->length=L->length;

    printf("              原始序列为：");
    for(int i=1; i<=L->length; i++)
        printf("%3d",L->r[i].key);
    printf("\n");

    for(int i=1; i<=temp->length; i++)
        temp->r[i]=L->r[i];
    SelectSort(temp);
    printf("简单选择排序，排序结果为：");
    for(int i=1; i<=temp->length; i++)
        printf("%3d",temp->r[i].key);
    printf("\n");

    for(int i=1; i<=temp->length; i++)
        temp->r[i]=L->r[i];
    HeapSort(temp);
    printf("      堆排序，排序结果为：");
    for(int i=1; i<=temp->length; i++)
        printf("%3d",temp->r[i].key);
     printf("\n");
}
