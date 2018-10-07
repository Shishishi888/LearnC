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

/*冒泡排序*/
void BubbleSort(SqList *L){
    int m=L->length-1;
    int flag=1;
    while(m>0&&flag==1){
        flag=0;
        int j;
        for(j=1; j<=m; j++){
            if(L->r[j].key>L->r[j+1].key){
                flag=1;
                RedType t=L->r[j];
                L->r[j]=L->r[j+1];
                L->r[j+1]=t;
            }
        }
        m--;
    }
}

/*快速排序*/
int Partition(SqList *L, int low, int high){
    L->r[0]=L->r[low];
    int pivotkey=L->r[low].key;
    while(low<high){
        while(low<high&&L->r[high].key>=pivotkey)
            high--;
        L->r[low]=L->r[high];
        while(low<high&&L->r[low].key<=pivotkey)
            low++;
        L->r[high]=L->r[low];
    }
    L->r[low]=L->r[0];
    return low;
}

void QSort(SqList *L, int low, int high){
    if(low<high){
        int pivotloc=Partition(L, low, high);
        QSort(L, low, pivotloc-1);
        QSort(L, pivotloc+1, high);
    }
}

void QuickSort(SqList *L){
    QSort(L, 1, L->length);
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
    BubbleSort(temp);
    printf("冒泡排序，排序结果为：");
    for(int i=1; i<=temp->length; i++)
        printf("%3d",temp->r[i].key);
    printf("\n");

    for(int i=1; i<=temp->length; i++)
        temp->r[i]=L->r[i];
    QuickSort(temp);
    printf("快速排序，排序结果为：");
    for(int i=1; i<=temp->length; i++)
        printf("%3d",temp->r[i].key);
     printf("\n");
}
