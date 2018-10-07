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

/*直接插入排序*/
void InsertSort(SqList *L){
    int i;
    for(i=2; i<=L->length; ++i){
        if(L->r[i].key<L->r[i-1].key){
            L->r[0]=L->r[i];
            L->r[i]=L->r[i-1];
            int j;
            for(j=i-2; L->r[0].key<L->r[j].key; --j)
                L->r[j+1]=L->r[j];
            L->r[j+1]=L->r[0];
        }
    }
}

/*折半插入排序*/
void BInsertSort(SqList *L){
    int i;
    for(i=2; i<=L->length; i++){
        L->r[0]=L->r[i];
        int low=1;
        int high=i-1;
        while(low<=high){
            int mid=(low+high)/2;
            if(L->r[i].key<L->r[mid].key)
                high=mid-1;
            else
                low=mid+1;
        }
        int j;
        for(j=i-1; j>=high+1; j--)
            L->r[j+1]=L->r[j];
        L->r[high+1]=L->r[0];
    }
}

/*希尔排序*/
void ShellInsert(SqList *L, int dk){
    int i;
    for(i=dk+1; i<L->length; i++){
        if(L->r[i].key<L->r[i-dk].key){
            L->r[0].key=L->r[i].key;
            int j;
            for(j=i-dk; j>0&&L->r[0].key<L->r[j].key; j-=dk)
                L->r[j+dk]=L->r[j];
            L->r[j+dk]=L->r[0];
        }
    }
}

void ShellSort(SqList *L, int dt[], int t){
    int k;
    for(k=0; k<t; k++)
        ShellInsert(L, dt[k]);
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
    InsertSort(temp);
    printf("直接插入排序，排序结果为：");
    for(int i=1; i<=temp->length; i++)
        printf("%3d",temp->r[i].key);
    printf("\n");

    for(int i=1; i<=temp->length; i++)
        temp->r[i]=L->r[i];
    BInsertSort(temp);
    printf("折半插入排序，排序结果为：");
    for(int i=1; i<=temp->length; i++)
        printf("%3d",temp->r[i].key);
     printf("\n");

    for(int i=1; i<=temp->length; i++)
        temp->r[i]=L->r[i];
    int dt[]={3,2,1};
    ShellSort(L, dt, 3);
    printf("    希尔排序，排序结果为：");
    for(int i=1; i<=temp->length; i++)
        printf("%3d",temp->r[i].key);
}
