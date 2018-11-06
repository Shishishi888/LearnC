#include <stdio.h>
#include <malloc.h>
#define OK 1
#define ERROR 0
typedef int ElemType;

typedef struct LNode
{
    ElemType data;
    struct LNode *next;
}LNode, *LinkList;//LinkListΪָ��ṹ��LNode��ָ������
/*Ϊ����߳���Ŀɶ��ԣ��ڴ˶�ͬһ�ṹ��ָ�����������������ƣ�LinkList��LNode*�����߱������ǵȼ۵ġ�ͨ��ϰ������LinkList
���嵥����ǿ���������ĳ���������ͷָ�룻��LNode*����ָ���������������ָ�����*/

/*������ĳ�ʼ��*/
int InitList(LinkList *L)
{
    *L=(LNode *)malloc(sizeof(LNode));
    (*L)->next=NULL;
    return OK;
}

/*�������ȡֵ*/
int GetElem(LinkList L, int i, ElemType *e)
{
    LNode *p=L->next;
    int j=1;
    while(p&&j<i)
    {
        p=p->next;
        ++j;
    }
    if(!p||j>i)
        return ERROR;
    *e=p->data;
    return OK;
}

/*������İ�ֵ����*/
LNode *LocateElem(LinkList L, ElemType e)
{
    LNode *p=L->next;
    while(p&&p->data!=e)
        p=p->next;
    return p;//���ҳɹ�����ֵΪe�Ľ���ַp������ʧ��pΪNULL
}

/*������Ĳ���*/
int ListInsert(LinkList *L, int i, ElemType e)
{
    LNode *p=*L;
    int j=0;
    while(p&&(j<i-1))
    {
        p=p->next;
        ++j;
    }
    if(!p||j>i-1)
        return ERROR;
    LNode *s=(LNode *)malloc(sizeof(LNode));
    s->data=e;
    s->next=p->next;
    p->next=s;
    return OK;
}

/*�������ɾ��*/
int ListDelete(LinkList *L, int i)
{
    LNode *p=*L;
    int j=0;
    while((p->next)&&(j<i-1))
    {
        p=p->next;
        ++j;
    }
    if(!(p->next)||(j>i-1))
        return ERROR;
    LNode *q=p->next;
    p->next=q->next;
    free(p);
    return OK;
}


/*ǰ�巨����������*/
void CreateList_H(LinkList *L, int n)
{
    *L=(LNode *)malloc(sizeof(LNode));
    (*L)->next=NULL;
    int i;
    for(i=0;i<n;++i)
    {
        LNode *p=(LNode *)malloc(sizeof(LNode));
        scanf("%d",&(p->data));
        p->next=(*L)->next;
        (*L)->next=p;
    }
}

/*��巨����������*/
void CreateList_R(LinkList *L, int n)
{
    *L=(LNode *)malloc(sizeof(LNode));
    (*L)->next=NULL;
    LNode *r=*L;
    int i;
    for(i=0;i<n;++i)
    {
        LNode *p=(LNode *)malloc(sizeof(LNode));
        scanf("%d",&(p->data));
        p->next=NULL;
        r->next=p;
        r=p;
    }
}

/*���ٵ�����*/
int DestroyList_L(LinkList *L)
{
    LinkList p;
    while(*L)
    {
        p=*L;
        *L=(*L)->next;
        free(p);
    }
    return OK;
}

/*��յ�����*/
int ClearList(LinkList *L)
{
    LinkList p, q;
    p=(*L)->next;
    while(p)
    {
        q=p->next;
        free(p);
        p=q;
    }
    (*L)->next=NULL;
    return OK;
}

/*������ĳ���*/
int GetLength_L(LinkList L)
{
    LinkList p=L->next;
    int i=0;
    while(p)
    {
        i++;
        p=p->next;
    }
    return i;
}

/*�жϵ������Ƿ�Ϊ��*/
int IsEmpty_L(LinkList L)
{
    if(L->next)
        return 0;
    else
        return 1;
}

/*�ϲ�������*/
void MergeList(LinkList *LA, LinkList LB)
{//�����������Ա�LB�е�����LA�е�����Ԫ�ز��뵽LA��
    int m=GetLength_L(*LA);
    int n=GetLength_L(LB);

    for(int i=0; i<=n; i++){
        ElemType e;
        GetElem(LB, i, &e);
        if(!LocateElem(*LA, e))
            ListInsert(LA, ++m, e);
    }
}

/*�ϲ���ʽ�����*/
void MergeList_L(LinkList *LA, LinkList *LB, LinkList *LC)
{//��֪������LA��LB��Ԫ�ذ�ֵ�ǵݼ�����
 //�鲢LA��LB�õ��µĵ�����LC��LC��Ԫ��Ҳ��ֵ�ǵݼ�����

    LNode *pa=(*LA)->next;//pa�ĳ�ֵָ��LA����Ԫ���
    LNode *pb=(*LB)->next;//pb�ĳ�ֵָ��LB����Ԫ���

    LC=LA;//��LA��ͷ�����ΪLC��ͷ���
    LNode *pc=(*LA)->next;//pc�ĳ�ֵָ��LC��ͷ���

    while(pa&&pb)
    {
        if(pa->data<=pb->data)//�����ǰpa��dataС�ڻ����pb��data
        {
            pc->next=pa;
            pc=pa;//pcָ��ǰpa��pb�н�С�Ľ�㣬��pa
            pa=pa->next;//paָ��La�����е���һ�����
        }

        else//�����ǰpa��data����pb��data
        {
            pc->next=pb;
            pc=pb;//pcָ��ǰpa��pb�н�С�Ľ�㣬��pb
            pb=pb->next;//pbָ��Lb�����е���һ�����
        }
    }

    pc->next=pa?pa:pb;//���ǿ������ʣ����ֱ�����ӵ�Lc��������
    free(LB);
}


