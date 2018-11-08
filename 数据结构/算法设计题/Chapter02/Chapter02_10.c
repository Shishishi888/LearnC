#include <stdio.h>
#include <malloc.h>
#define MAXSIZE 20                                          //˳����Ա���������
#define OK 1
#define ERROR 0

typedef int ElemType;

typedef struct{
    ElemType *elem;
    int length;                                         //˳���ĳ�Ա����
    int list_size;                                      //˳���ռ���ڴ�ռ��С
}SqList;

int InitList(SqList *L){//��ʼ��˳���
    L->elem=(ElemType *)malloc(MAXSIZE*sizeof(ElemType));             //Ϊ˳������һ���ڴ�ռ䣬˳���ĳ�Ա����Ϊ����
    if(!L->elem)
        exit(0);
    L->length=0;
    L->list_size=MAXSIZE;
    return OK;
}

void CreateList(SqList *L){//����˳���
    if(!L->elem)
        exit(0);
    for(int i=0; i<L->list_size; i++){
        int e;
        scanf("%d", &e);

        if(e==-1)
            break;

        L->elem[i]=e;
        L->length++;
    }
}

void ListTraverse(SqList L){//����˳���
    if(!L.elem) exit(0);

    for(int i=0; i<L.length; i++)
        printf("%3d", L.elem[i]);

    /*
    for(int i=0; i<L.length; i++){
        printf("%3d", *L.elem);
        L.elem++;
    }
    */
}

void DeleteItem(SqList *L, ElemType item){//ɾ��˳�����ָ����Ԫ��
    int k=0;
    for(int i=0; i<L->length; i++){
        if(L->elem[i]!=item){
            L->elem[k]=L->elem[i];
            k++;
        }
    }
    L->length=k;
}

void main(){

    printf("���ȴ���һ��˳���L��\n");
    SqList L;
    InitList(&L);
    CreateList(&L);
    printf("�����ɹ���˳��L�ı������Ϊ��");
    ListTraverse(L);
    printf("\n");

    printf("������Ҫɾ����Ԫ�أ�");
    int item;
    scanf("%d", &item);
    DeleteItem(&L, item);
    printf("ɾ���ɹ���ɾ����Ľ��Ϊ��");
    ListTraverse(L);
}

/*
    ��֪����Ϊn�����Ա�A����˳�򴢴�ṹ����дһ��ʱ�临�Ӷ�Ϊo(n)���ռ临�Ӷ�Ϊo(1)��
    �㷨�����㷨��ɾ�����Ա�������ֵΪitem������Ԫ�ء�
*/
