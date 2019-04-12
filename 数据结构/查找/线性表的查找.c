#include <stdio.h>
#include <string.h>
#include <malloc.h>
#define MAXSIZE 100

typedef int KeyType;
typedef char InfoType[20];

typedef struct
{
    KeyType key;                                    //关键字域
    InfoType otherinfo;                             //其他域
}ElemType;

typedef struct
{
    ElemType *R;
    int length;
}SSTable;

/*线性表的初始化*/
void InitSSTable(SSTable *ST)
{
    if(!ST) exit(0);
    ST->R=(ElemType *)malloc(sizeof(ElemType)*MAXSIZE);
    ST->length=0;
}

/*线性表的创建*/
void CreatSSTable(SSTable *ST)
{
    printf("请向线性表中插入元素（关键字，信息），当插入的元素的关键字为-1时，停止插入\n");

    int i=1;
    printf("请插入第%d个元素：", i);
    KeyType key;
    InfoType otherinfo;
    scanf("%d，%s", &key, &otherinfo);
    while(key!=-1)
    {
        ST->R[i].key=key;
        strcpy(ST->R[i].otherinfo, otherinfo);
        ST->length++;
        i++;
        printf("请插入第%d个元素：", i);
        scanf("%d，%s", &key, &otherinfo);
    }
}

/*顺序查找*/
int Search(SSTable *ST, KeyType key)
{
    int i;
    for(i=ST->length;i>=1;--i)
    {
        if(ST->R[i].key==key)
            return i;
    }
    return 0;
}

/*设置监视哨的顺序查找*/
int Search_Seq(SSTable *ST, KeyType key)
{
    ST->R[0].key=key;
    int i;
    for(i=ST->length;ST->R[i].key!=key;--i);
    return i;
}

/*折半查找（非递归算法）*/
int Search_Bin(SSTable *ST, KeyType key)
{
    int low=1;
    int high=ST->length;
    int mid;
    while(low<=high)                                //当low=high时，查找区间还有最后一个结点，还要进一步比较
    {
        mid=(low+high)/2;
        if(key==ST->R[mid].key)
            return mid;
        else if(key<ST->R[mid].key)
            high=mid-1;
        else
            low=mid+1;
    }
    return 0;
}

/*折半查找（递归算法）*/
int Search_Bin_Re(SSTable *ST, KeyType key, int low, int high)
{
    if(low>high)
        return 0;
    int mid=(low+high)/2;
    if(key==ST->R[mid].key)
        return mid;
    else if(key<ST->R[mid].key)
        return Search_Bin_Re(ST, key, low, mid-1);
    else
        return Search_Bin_Re(ST, key, mid+1, high);

}

void main()
{
    SSTable ST_1;
    InitSSTable(&ST_1);
    printf("创建普通线性表：\n");
    CreatSSTable(&ST_1);

    printf("线性表的遍历结果（关键字，信息）为：\n");
    for(int i=1; i<=ST_1.length;i++)
        printf("%d，%s  ", ST_1.R[i].key, ST_1.R[i].otherinfo);
    printf("\n");
    printf("待查询的线性表的长度为：%d\n", ST_1.length);

    printf("请输入待查询的元素的关键字：");
    KeyType key;
    scanf("%d",&key);
    printf("顺序查找的结果（线性表中的位置，关键字，信息）为：%d，%d，%s\n", Search(&ST_1, key), key, ST_1.R[Search(&ST_1, key)].otherinfo);
    printf("设置监视哨的顺序查找的结果（线性表中的位置，关键字，信息）为：%d，%d，%s\n", Search_Seq(&ST_1, key), key, ST_1.R[Search_Seq(&ST_1, key)].otherinfo);
    printf("\n");

    SSTable ST_2;
    InitSSTable(&ST_2);
    printf("创建有序线性表：\n");
    CreatSSTable(&ST_2);

    printf("线性表的遍历结果为：\n");
    for(int i=1;i<=ST_2.length;i++)
        printf("%d，%s  ", ST_2.R[i].key, ST_2.R[i].otherinfo);
    printf("\n");
    printf("待查询的线性表的长度为：%d\n", ST_2.length);

    printf("请输入待查询的元素的关键字：");
    scanf("%d", &key);
    printf("折半查找（非递归算法）的结果（线性表中的位置，关键字，信息）为：%d，%d，%s\n", Search_Bin(&ST_2, key), key, ST_2.R[Search_Bin(&ST_2, key)].otherinfo);
    printf("折半查找（递归算法）的结果（线性表中的位置，关键字，信息）为：%d，%d，%s\n", Search_Bin_Re(&ST_2, key, 1, ST_2.length), key, ST_2.R[Search_Bin_Re(&ST_2, key, 1, ST_2.length)].otherinfo);
}
