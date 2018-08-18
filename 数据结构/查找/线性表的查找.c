#include <stdio.h>
#include <malloc.h>
#define MAXSIZE 100

typedef struct
{
    int key;                                       //�ؼ�����
    char otherinfo[20];                            //������
}ElemType;

typedef struct
{
    ElemType *R;
    int length;
}SSTable;

/*˳�����*/
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

/*���ü����ڵ�˳�����*/
int Search_Seq(SSTable *ST, int key)
{
    ST->R[0].key=key;
    int i;
    for(i=ST->length;ST->R[i].key!=key;--i);
    return i;
}

/*�۰���ң��ǵݹ��㷨��*/
int Search_Bin(SSTable *ST, int key)
{
    int low=1;
    int high=ST->length;
    int mid=(low+high)/2;
    while(low<=high)                                //��low=highʱ���������仹�����һ����㣬��Ҫ��һ���Ƚ�
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

/*�۰���ң��ݹ��㷨��*/
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
    printf("���������ѯ�����Ա�\n");
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
    printf("������Ĵ���ѯ�����Ա�Ϊ��\n");
    for(i=1; i<=S->length;i++)
        printf("%d ",S->R[i].key);
    printf("\n");
    printf("����ѯ�����Ա�ĳ���Ϊ��%d\n",S->length);
    printf("���������ѯ��ֵ��");
    scanf("%d",&key);
    printf("˳����ҵĽ��Ϊ��%d\n",Search(S, key));
    printf("���ü����ڵ�˳����ҵĽ��Ϊ��%d\n", Search_Seq(S, key));
    printf("\n");

    SSTable *S_1;
    S_1=(SSTable *)malloc(sizeof(SSTable));
    S_1->R=(ElemType *)malloc(sizeof(ElemType)*MAXSIZE);
    S_1->length=0;
    printf("���������ѯ�����Ա��������У���\n");
    i=1;
    scanf("%d",&key);
    while(key!=-1)
    {
        S_1->R[i].key=key;
        S_1->length++;
        i++;
        scanf("%d",&key);
    }
    printf("������Ĵ���ѯ�����Ա�Ϊ���������У���\n");
    for(i=1;i<=S_1->length;i++)
        printf("%d ",S_1->R[i].key);
    printf("\n");
    printf("����ѯ�����Ա�ĳ���Ϊ��%d\n",S->length);
    printf("���������ѯ��ֵ��");
    scanf("%d",&key);
    printf("�۰���ң��ǵݹ��㷨���Ľ��Ϊ��%d\n",Search_Bin(S_1, key));
    printf("�۰���ң��ݹ��㷨���Ľ��Ϊ��%d\n",Search_Bin_Re(S_1, key, 1, S_1->length));

}
