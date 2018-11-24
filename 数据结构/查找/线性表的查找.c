#include <stdio.h>
#include <string.h>
#include <malloc.h>
#define MAXSIZE 100
#define OK 1
#define ERROR 0

typedef int KeyType;
typedef char InfoType[20];

typedef struct
{
    KeyType key;                                    //�ؼ�����
    InfoType otherinfo;                             //������
}ElemType;

typedef struct
{
    ElemType *R;
    int length;
}SSTable;

/*���Ա�ĳ�ʼ��*/
void InitSSTable(SSTable *ST)
{
    if(!ST) exit(0);
    ST->R=(ElemType *)malloc(sizeof(ElemType)*MAXSIZE);
    ST->length=0;
}

/*���Ա��Ĵ���*/
void CreatSSTable(SSTable *ST)
{
    printf("�������Ա��в���Ԫ�أ��ؼ��֣���Ϣ�����������Ԫ�صĹؼ���Ϊ-1ʱ��ֹͣ����\n");

    int i=1;
    printf("������%d��Ԫ�أ�", i);
    KeyType key;
    InfoType otherinfo;
    scanf("%d��%s", &key, &otherinfo);
    while(key!=-1)
    {
        ST->R[i].key=key;
        strcpy(ST->R[i].otherinfo, otherinfo);
        ST->length++;
        i++;
        printf("������%d��Ԫ�أ�", i);
        scanf("%d��%s", &key, &otherinfo);
    }
}

/*˳�����*/
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

/*���ü����ڵ�˳�����*/
int Search_Seq(SSTable *ST, KeyType key)
{
    ST->R[0].key=key;
    int i;
    for(i=ST->length;ST->R[i].key!=key;--i);
    return i;
}

/*�۰���ң��ǵݹ��㷨��*/
int Search_Bin(SSTable *ST, KeyType key)
{
    int low=1;
    int high=ST->length;
    int mid;
    while(low<=high)                                //��low=highʱ���������仹�����һ����㣬��Ҫ��һ���Ƚ�
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

/*�۰���ң��ݹ��㷨��*/
int Search_Bin_Re(SSTable *ST, KeyType key, int low, int high)
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
    SSTable ST_1;
    InitSSTable(&ST_1);
    printf("������ͨ���Ա�\n");
    CreatSSTable(&ST_1);

    printf("���Ա�ı���������ؼ��֣���Ϣ��Ϊ��\n");
    for(int i=1; i<=ST_1.length;i++)
        printf("%d��%s  ", ST_1.R[i].key, ST_1.R[i].otherinfo);
    printf("\n");
    printf("����ѯ�����Ա�ĳ���Ϊ��%d\n", ST_1.length);

    printf("���������ѯ��Ԫ�صĹؼ��֣�");
    KeyType key;
    scanf("%d",&key);
    printf("˳����ҵĽ�������Ա��е�λ�ã��ؼ��֣���Ϣ��Ϊ��%d��%d��%s\n", Search(&ST_1, key), key, ST_1.R[Search(&ST_1, key)].otherinfo);
    printf("���ü����ڵ�˳����ҵĽ�������Ա��е�λ�ã��ؼ��֣���Ϣ��Ϊ��%d��%d��%s\n", Search_Seq(&ST_1, key), key, ST_1.R[Search_Seq(&ST_1, key)].otherinfo);
    printf("\n");

    SSTable ST_2;
    InitSSTable(&ST_2);
    printf("�����������Ա�\n");
    CreatSSTable(&ST_2);

    printf("���Ա�ı������Ϊ��\n");
    for(int i=1;i<=ST_2.length;i++)
        printf("%d��%s  ", ST_2.R[i].key, ST_2.R[i].otherinfo);
    printf("\n");
    printf("����ѯ�����Ա�ĳ���Ϊ��%d\n", ST_2.length);

    printf("���������ѯ��Ԫ�صĹؼ��֣�");
    scanf("%d", &key);
    printf("�۰���ң��ǵݹ��㷨���Ľ�������Ա��е�λ�ã��ؼ��֣���Ϣ��Ϊ��%d��%d��%s\n", Search_Bin(&ST_2, key), key, ST_2.R[Search_Bin(&ST_2, key)].otherinfo);
    printf("�۰���ң��ݹ��㷨���Ľ�������Ա��е�λ�ã��ؼ��֣���Ϣ��Ϊ��%d��%d��%s\n", Search_Bin_Re(&ST_2, key, 1, ST_2.length), key, ST_2.R[Search_Bin_Re(&ST_2, key, 1, ST_2.length)].otherinfo);
}
