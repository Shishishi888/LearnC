#include <stdio.h>
#include <malloc.h>
#define MAXSIZE 100

typedef struct
{
    int key;                                       //关键字域
    char otherinfo[20];                            //其他域
}ElemType;

typedef struct
{
    ElemType *R;
    int length;
}SSTable;

/*顺序查找*/
int Search(SSTable *ST, int key)
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
int Search_Seq(SSTable *ST, int key)
{
    ST->R[0].key=key;
    int i;
    for(i=ST->length;ST->R[i].key!=key;--i);
    return i;
}

/*折半查找（非递归算法）*/
int Search_Bin(SSTable *ST, int key)
{
    int low=1;
    int high=ST->length;
    int mid=(low+high)/2;
    while(low<=high)                                //当low=high时，查找区间还有最后一个结点，还要进一步比较
    {
        if(key==ST->R[mid].key)
            return mid;
        else if(key<ST->R[mid].key)
            mid=high-1;
        else
            mid=low+1;
    }
    return 0;
}

/*折半查找（递归算法）*/
int Search_Bin_Re(SSTable *ST, int key, int low, int high)
{
    if(low>high)
        return 0;
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
    SSTable *S;
    S=(SSTable *)malloc(sizeof(SSTable));
    S->R=(ElemType *)malloc(sizeof(ElemType)*MAXSIZE);
    S->length=0;
    printf("请输入待查询的线性表：\n");
    int i=1;
    int key;
    scanf("%d",&key);
    while(key!=-1)
    {
        S->R[i].key=key;
        S->length++;
        i++;
        scanf("%d",&key);
    }
    printf("您输入的待查询的线性表为：\n");
    for(i=1; i<=S->length;i++)
        printf("%d ",S->R[i].key);
    printf("\n");
    printf("待查询的线性表的长度为：%d\n",S->length);
    printf("请输入待查询的值：");
    scanf("%d",&key);
    printf("顺序查找的结果为：%d\n",Search(S, key));
    printf("设置监视哨的顺序查找的结果为：%d\n", Search_Seq(S, key));
    printf("\n");

    SSTable *S_1;
    S_1=(SSTable *)malloc(sizeof(SSTable));
    S_1->R=(ElemType *)malloc(sizeof(ElemType)*MAXSIZE);
    S_1->length=0;
    printf("请输入待查询的线性表（有序排列）：\n");
    i=1;
    scanf("%d",&key);
    while(key!=-1)
    {
        S_1->R[i].key=key;
        S_1->length++;
        i++;
        scanf("%d",&key);
    }
    printf("您输入的待查询的线性表为（有序排列）：\n");
    for(i=1;i<=S_1->length;i++)
        printf("%d ",S_1->R[i].key);
    printf("\n");
    printf("待查询的线性表的长度为：%d\n",S->length);
    printf("请输入待查询的值：");
    scanf("%d",&key);
    printf("折半查找（非递归算法）的结果为：%d\n",Search_Bin(S_1, key));
    printf("折半查找（递归算法）的结果为：%d\n",Search_Bin_Re(S_1, key, 1, S_1->length));

}
