#include <stdio.h>
#include <malloc.h>
#define MAXSIZE 20                                          //˳����Ա���������
#define OK 1
#define ERROR 0
typedef int ElemType;

typedef struct
{
    ElemType *elem;
    int length;                                         //˳���ĳ�Ա����
    int list_size;                                      //˳���ռ���ڴ�ռ��С
}SqList;

/*˳���ĳ�ʼ��*/
int InitList(SqList *L)
{
    L->elem=(ElemType *)malloc(MAXSIZE*sizeof(ElemType));             //Ϊ˳������һ���ڴ�ռ䣬˳���ĳ�Ա����Ϊ����
    if(!L->elem)
        exit(0);
    L->length=0;
    L->list_size=MAXSIZE;
    return OK;
}

/*����˳���*/
void CreateList(SqList *L)
{
    if(!L->elem)
        exit(0);
    for(int i=0; i<L->list_size; i++)
    {
        int e;
        scanf("%d", &e);

        if(e==-1)
            break;

        L->elem[i]=e;
        L->length++;
    }
}

/*˳���ı���*/
void ListTraverse(SqList L)
{
    if(!L.elem) exit(0);

    for(int i=0; i<L.length; i++)
        printf("%3d", L.elem[i]);

    /*
    for(int i=0; i<L.length; i++)
    {
        printf("%3d", *L.elem);
        L.elem++;
    }
    */
}

/*˳����ȡֵ*/
int GetElem(SqList L, int i, ElemType *e)                   //�����������������OK��ʾȡֵ�ɹ�����ָ��eָ��ȡ����ֵ
{
    if(i<1||i>L.length)
        return ERROR;
    *e=L.elem[i-1];
    return OK;
}

/*˳���Ĳ���*/
int LocateElem(SqList L, ElemType e)
{
    for(int i=0;i<L.length;i++)
    {
        if(L.elem[i]==e)
            return i+1;
    }
    return 0;
}

/*˳���Ĳ���*/
int ListInsert(SqList *L, int i, ElemType e)
{
    if((i<1)||(i>L->length+1))
        return ERROR;
    if(L->length=MAXSIZE)
        return ERROR;
    for(int j=L->length-1;j>=i-1;j--)
        L->elem[j+1]=L->elem[j];
    L->elem[i-1]=e;
    ++L->length;
    return OK;
}

/*˳����ɾ��*/
int ListDelete(SqList *L, int i)
{
    if((i<1)||(i>L->length))
        return ERROR;
    for(int j=i;j<L->length-1;j++)
        L->elem[j-1]=L->elem[j];
    --L->length;
    return OK;
}

/*����˳���*/
void DestroyList(SqList *L)
{
    if(L->elem)
        free(L->elem);
}

/*���˳���*/
void ClearList(SqList *L)
{
    L->length=0;
}

/*��˳���ĳ���*/
int GetLength(SqList L)
{
    return L.length;
}

/*�ж�˳����Ƿ�Ϊ��*/
int IsEmpty(SqList L)
{
    if(L.length==0)
        return 1;
    else
        return 0;
}

/*�ϲ�˳���*/
void MergeList(SqList *LA, SqList LB)
{//�����������Ա�LB�е�����LA�е�����Ԫ�ز��뵽LA��
    int m=GetLength(*LA);
    int n=GetLength(LB);

    for(int i=0; i<n; i++)
    {
        ElemType e;
        GetElem(LB, i, &e);
        if(!LocateElem(*LA, e))
            ListInsert(LA, ++m, e);
    }
}

/*�ϲ�˳�������*/
void MergeList_Sq(SqList LA, SqList LB, SqList *LC)
{//��֪˳�������LA��LB��Ԫ�ذ�ֵ�ǵݼ�����
 //�鲢LA��LB�õ��µĵ�˳�������LC��LC��Ԫ��Ҳ��ֵ�ǵݼ�����

    LC->length=LA.length+LB.length;//�±���Ϊ���ϲ�������֮��
    LC->elem=(ElemType *)malloc(sizeof(ElemType)*LC->length);//Ϊ�ϲ�����±����һ������ռ�

    ElemType *pa=LA.elem;//ָ��paָ��LA�ĵ�һ��Ԫ��
    ElemType *pb=LA.elem;//ָ��pbָ��LB�ĵ�һ��Ԫ��
    ElemType *pa_last=LA.elem+LA.length-1;//ָ��pa_lastָ��LA�����һ��Ԫ��
    ElemType *pb_last=LB.elem+LB.length-1;//ָ��pb_lastָ��LB�����һ��Ԫ��

    ElemType *pc=LA.elem;//ָ��pcָ���±�ĵ�һ��Ԫ��

    while(pa<=pa_last&&pb<=pb_last)
    {
        if(*pa<=*pb)    *pc++=*pa++;//����ժȡ�����н�С�Ľ����뵽LC�����
        else            *pc++=*pb++;
    }

    while(pa<=pa_last)  *pc++=*pa++;//LB�ѵ���ĩβ�����ν�LA��ʣ��Ԫ�ز��뵽LC�����
    while(pb<pb_last)   *pc++=*pb++;//LA�ѵ���ĩβ�����ν�LB��ʣ��Ԫ�ز��뵽LC�����
}

