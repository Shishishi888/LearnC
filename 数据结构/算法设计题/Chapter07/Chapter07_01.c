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

void InitSSTable(SSTable *ST){//��ʼ�����Ա�
    if(!ST) exit(0);
    ST->R=(ElemType *)malloc(sizeof(ElemType)*MAXSIZE);
    ST->length=0;
}

void CreatSSTable(SSTable *ST){//�������Ա�
    printf("�������Ա��в���Ԫ�أ��ؼ��֣���Ϣ�����������Ԫ�صĹؼ���Ϊ-1ʱ��ֹͣ����\n");

    int i=1;
    printf("������%d��Ԫ�أ�", i);
    KeyType key;
    InfoType otherinfo;
    scanf("%d��%s", &key, &otherinfo);
    while(key!=-1){
        ST->R[i].key=key;
        strcpy(ST->R[i].otherinfo, otherinfo);
        ST->length++;
        i++;
        printf("������%d��Ԫ�أ�", i);
        scanf("%d��%s", &key, &otherinfo);
    }
}

int Search_Bin_Re(SSTable *ST, KeyType key, int low, int high){//�۰���ң��ݹ��㷨��
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
    printf("�����������Ա�\n");
    CreatSSTable(&ST);

    printf("���Ա�ı������Ϊ��\n");
    for(int i=1;i<=ST.length;i++)
        printf("%d��%s  ", ST.R[i].key, ST.R[i].otherinfo);
    printf("\n");

    KeyType key;
    printf("���������ѯ��Ԫ�صĹؼ��֣�");
    scanf("%d", &key);
    printf("�۰���ң��ݹ��㷨���Ľ�������Ա��е�λ�ã��ؼ��֣���Ϣ��Ϊ��%d��%d��%s\n", Search_Bin_Re(&ST, key, 1, ST.length), key, ST.R[Search_Bin_Re(&ST, key, 1, ST.length)].otherinfo);
}

/*
    д���۰���ҵĵݹ��㷨
*/

