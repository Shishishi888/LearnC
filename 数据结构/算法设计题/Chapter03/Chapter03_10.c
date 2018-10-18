#include <stdio.h>
#include <malloc.h>
#define OK 1
#define ERROR 0

typedef struct LNode{
    int data;
    struct LNode *next;
}LNode, *LinkList;

int InitList(LinkList *L){//��ʼ��������
    *L=(LNode *)malloc(sizeof(LNode));
    if(!(*L))
        exit(0);
    (*L)->next=NULL;
    return OK;
}

int ListInsert(LinkList L, int e){//�������׶˲���
    LNode *s=(LNode *)malloc(sizeof(LNode));
    s->data=e;
    s->next=L->next;
    L->next=s;
    return OK;
}

int GetMax(LinkList L){//�������е��������
    if(!L->next)
        return L->data;
    else{
        int max=GetMax(L->next);
        return max>=L->data?max:L->data;
    }
}

int GetLength(LinkList L){//������Ľ�����
    if(!L->next)
        return 1;
    else
        return GetLength(L->next)+1;
}

double GetAverage(LinkList L, int n){//������������ƽ��ֵ
    if(!L->next)
        return L->data;
    else{
        double average=GetAverage(L->next, n-1);
        return (average*(n-1)+L->data)/n;
    }
}
/*
int InitList(LinkList L){
    //L=(LNode *)malloc(sizeof(LNode));
    L->next=NULL;
    return OK;
}

int ListInsert(LinkList L, int e){//�������׶˲���
    LNode *s=(LNode *)malloc(sizeof(LNode));
    s->data=e;
    s->next=L->next;
    L->next=s;
    return OK;
}
*/
void main(){
    LinkList f;
    InitList(&f);

    ListInsert(f, 5);
    ListInsert(f, 19);
    ListInsert(f, 15);
    ListInsert(f, 7);
    ListInsert(f, 12);

    printf("�����е��������Ϊ��%d\n", GetMax(f->next));
    printf("����Ľ�����Ϊ��%d\n", GetLength(f->next));
    printf("�����������������ƽ��ֵ��%2f\n", GetAverage(f->next, GetLength(f->next)));
}

/*
    ��֪fΪ������ı�ͷָ�룬�����д���Ķ����������ݣ���д��ʵ����������ĵݹ��㷨��
    1.�������е��������
    2.������Ľڵ����
    3.������������ƽ��ֵ
*/

/*
#include <stdio.h>
#include <malloc.h>
#define OK 1
#define ERROR 0

typedef struct LNode{
    int data;
    struct LNode *next;
}LNode;

int InitList(LNode *L){
                       //��Ϊ���������У�ϵͳ�Ѿ�Ϊͷ���node�������ڴ�ռ�
                       //����ڳ�ʼ�������У�����Ҫ�ֶ����루������Ҫmalloc��
                       //��˲����漰����һ��ָ����޸�
                       //��˲���Ҫ���ʼ������������Ӧ�Ķ���ָ��
    L->next=NULL;
    return OK;
}

int ListInsert(LNode *L, int e){
    LNode *s=(LNode *)malloc(sizeof(LNode));
    s->data=e;
    s->next=L->next;
    L->next=s;
    return OK;
}

int GetLength(LNode *L){
    if(!L->next)
        return 1;
    else
        return GetLength(L->next)+1;
}

void main(){
    LNode node;//����һ����ͨ����node����Ϊͷ���
               //ϵͳ���Զ�Ϊnode�����ڴ�ռ䣬����Ҫ�ֶ����루������Ҫmalloc��

    InitList(&node);//����ͷ���node�ĵ�ַ��������ָ��node��һ��ָ��
    ListInsert(&node, 1);
    ListInsert(&node, 2);
    ListInsert(&node, 2);
    printf("������Ľ�����Ϊ��%d", GetLength((&node)->next));
}

------------------------------------------------------------------------------------------------------------------

typedef struct LNode{
    int data;
    struct LNode *next;
}LNode, *LinkList;

int InitList(LinkList *L){//��Ϊ���������У�ϵͳδ�Զ�Ϊָ��node������ָ����ڴ�ռ䣨�����ͷ�����ڴ�ռ䣩
                          //����ڳ�ʼ�������У���Ҫ�ֶ����루����Ҫmalloc��
                          //����漰���˶�һ��ָ��node���޸�
                          //�����Ҫ���ʼ������������Ӧ�Ķ���ָ��
    *L=(LNode *)malloc(sizeof(LNode));
    if(!L)
        exit(0);
    (*L)->next=NULL;
    return OK;
}

int ListInsert(LinkList L, int e){
    LinkList s=(LNode *)malloc(sizeof(LNode));
    s->data=e;
    s->next=L->next;
    L->next=s;
    return OK;
}

int GetLength(LinkList L){
    if(!L->next)
        return 1;
    else
        return GetLength(L->next)+1;
}

void main(){
    LinkList node;//����һ��ָ�����node��ָ��ͷ���
                  //ϵͳ����Ϊnode������ָ����ڴ�ռ䣬��Ҫ�ֶ����루����Ҫmalloc����mallocһ����ڳ�ʼ�������У�

    InitList(&node);//����ָ��node�ĵ�ַ����������Ӧ�Ķ���ָ��
    ListInsert(node, 1);
    ListInsert(node, 2);
    ListInsert(node, 2);
    printf("������Ľ�����Ϊ��%d", GetLength(node->next));
}
*/
