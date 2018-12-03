#include <stdio.h>
#include <string.h>
#include <malloc.h>
#define MAXSIZE 100

typedef int KeyType;
typedef char InfoType[20];

typedef struct{
    KeyType key;
    InfoType otherinfo;
}ElemType;

typedef struct{
    ElemType *R;
    int length;
}SSTable;

void InitSSTable(SSTable *ST){//初始化线性表
    if(!ST) exit(0);
    ST->R=(ElemType *)malloc(sizeof(ElemType)*MAXSIZE);
    ST->length=0;
}

void CreatSSTable(SSTable *ST){//创建线性表
    printf("请向线性表中插入元素（关键字，信息），当插入的元素的关键字为-1时，停止插入\n");

    int i=1;
    printf("请插入第%d个元素：", i);
    KeyType key;
    InfoType otherinfo;
    scanf("%d，%s", &key, &otherinfo);
    while(key!=-1){
        ST->R[i].key=key;
        strcpy(ST->R[i].otherinfo, otherinfo);
        ST->length++;
        i++;
        printf("请插入第%d个元素：", i);
        scanf("%d，%s", &key, &otherinfo);
    }
}

int Search_Bin_Re(SSTable *ST, KeyType key, int low, int high){//折半查找（递归算法）
    int mid=(low+high)/2;
    if(key==ST->R[mid].key)
        return mid;
    else if(key<ST->R[mid].key)
        Search_Bin_Re(ST, key, low, mid-1);
    else
        Search_Bin_Re(ST, key, mid+1, high);
}

void main()
{
    SSTable ST;
    InitSSTable(&ST);
    printf("创建有序线性表：\n");
    CreatSSTable(&ST);

    printf("线性表的遍历结果为：\n");
    for(int i=1;i<=ST.length;i++)
        printf("%d，%s  ", ST.R[i].key, ST.R[i].otherinfo);
    printf("\n");

    KeyType key;
    printf("请输入待查询的元素的关键字：");
    scanf("%d", &key);
    printf("折半查找（递归算法）的结果（线性表中的位置，关键字，信息）为：%d，%d，%s\n", Search_Bin_Re(&ST, key, 1, ST.length), key, ST.R[Search_Bin_Re(&ST, key, 1, ST.length)].otherinfo);
}

/*
    写出折半查找的递归算法
*/

