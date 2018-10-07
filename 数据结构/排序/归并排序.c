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

/*归并排序*/
void Merge(RedType R[], RedType T[], int low, int mid, int high){
    int i=low;
    int j=mid+1;
    int k=low;
    while(i<=mid&&j<=high){       //将R[]中的记录由小到大地并入T[]中
        if(R[i].key<=R[j].key)
            T[k++]=R[i++];
        else
            T[k++]=R[j++];
    }
    while(i<=mid)                 //将剩余的R[]复制到T[]中
        T[k++]=R[i++];
    while(j<=high)                //将剩余的R[]复制到T[]中
        T[k++]=R[j++];
}

void MSort(RedType R[], RedType T[], int low, int high){
    RedType S[MAXSIZE+1];
    if(low==high)
        T[low]=R[low];
    else{
        int mid=(low+high)/2;
        MSort(R, S, low, mid);
        MSort(R, S, mid+1, high);
        Merge(S, T, low, mid, high);
    }
}

void MergrSort(SqList *L){
    MSort(L->r, L->r, 1, L->length);
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

    printf("          原始序列为：");
    for(int i=1; i<=L->length; i++)
        printf("%3d",L->r[i].key);
    printf("\n");

    for(int i=1; i<=temp->length; i++)
        temp->r[i]=L->r[i];
    MergrSort(temp);
    printf("归并排序，排序结果为：");
    for(int i=1; i<=temp->length; i++)
        printf("%3d",temp->r[i].key);
    printf("\n");
}
