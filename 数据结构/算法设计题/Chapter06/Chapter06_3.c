#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdbool.h>
#define MVNum 100                            //��󶥵���
#define MAXSIZE 100
#define OK 1
#define ERROR 0
typedef char OtherInfo[20]; 			     //����������¼��������Ȩֵ
typedef char VerTexType; 					 //�������������

typedef struct ArcNode                       //�߽��
{
    int adjvex;                              //�ñ���ָ��Ķ����λ��
    struct ArcNode *nextarc;                 //ָ����һ���ߵ�ָ��
    OtherInfo info;                          //�ͱ���ص���Ϣ
}ArcNode;

typedef struct VNode                         //������Ϣ
{
    VerTexType data;
    ArcNode *firstarc;                       //ָ���һ�������ö���ıߵ�ָ��
}VNode, AdjList[MVNum];                      //AdjList��ʾ�ڽӱ�����

typedef struct                               //�ڽӱ�
{
    AdjList vertices;
    int vexnum, arcnum;                      //ͼ�ĵ�ǰ�������ͱ���
}ALGraph;

int LocateVex(ALGraph G, VerTexType vex)
{
    int i;
    for(i=0; i<G.vexnum; i++)
        if(vex==G.vertices[i].data)
            return i;
    return -1;
}

int CreateUDG(ALGraph *G)										     //�����ڽӱ��ʾ����������ͼ
{
	printf("���������ͼ���ܶ�������");     					     //�����ܶ��������ܱ���
	scanf("%d", &(G->vexnum));
	printf("���������ͼ���ܱ�����");
    scanf("%d", &(G->arcnum));
	printf("������������������Ϣ��\n");

    for(int i=0; i<G->vexnum; i++)
    {
    	//fflush(stdin);                                             //ˢ�»�����
    	char c=getchar();											 //�Ե��������еġ��س���
		printf("�������%d���������Ϣ��", i+1);					 //���붥���ֵ
		scanf("%c", &(G->vertices[i].data));                         //�������붥�����Ϣ
        G->vertices[i].firstarc=NULL;        						 //��ʼ����ͷ����ָ����ΪNULL
    }

    VerTexType v1, v2;
    printf("����������ÿ���������Ķ��㣨����A, ����B����\n");
    for(int k=0; k<G->arcnum; k++)           //������ߣ������ڽӱ�
    {
    	//fflush(stdin);				     //ˢ�»�����
    	char c=getchar();                    //�Ե��������еġ��س���
    	printf("�������%d���������Ķ��㣺", k+1);
        scanf("%c, %c", &v1, &v2);           //����һ������������������
        int i=LocateVex(*G, v1);             //ȷ��v1��v2��G�е�λ�ã���������G->vertices�е����
        int j=LocateVex(*G, v2);
        ArcNode *p1=(ArcNode *)malloc(sizeof(ArcNode));              //�����µıߵĽ��*p1
        p1->adjvex=j;                                                //�ڽӵ����Ϊj
        p1->nextarc=G->vertices[i].firstarc;                         //���½��*p1���붥��vi�ı߱�ͷ��
        G->vertices[i].firstarc=p1;
        ArcNode *p2=(ArcNode *)malloc(sizeof(ArcNode));              //������һ���ԳƵ��µı߽��*p2
        p2->adjvex=i;                                                //�ڽӵ����Ϊi
        p2->nextarc=G->vertices[j].firstarc;                         //���½��*p2���붥��vi�ı߱�ͷ��
        G->vertices[j].firstarc=p2;
    }
}

typedef int SElemType;
typedef struct
{
    SElemType *base;    						    //ջ��ָ��
    SElemType *top;    								//ջ��ָ��
    int stacksize; 		 							//ջ���õ��������
}SqStack;

int InitStack(SqStack *S)							//��ʼ��˳��ջ
{
    S->base=(SElemType *)malloc(sizeof(SElemType)*MAXSIZE);
    if(!(S->base))
        exit(0);
    S->top=S->base;
    S->stacksize=MAXSIZE;
    return OK;
}

int Push(SqStack *S, SElemType e)					//˳��ջ����ջ
{
    if(S->top-S->base==S->stacksize)
        return ERROR;
    *(S->top++)=e;
    return OK;
}

int Pop(SqStack *S, SElemType *e)					//˳��ջ�ĳ�ջ
{
    if(S->top==S->base)
        return ERROR;
    *e=*(--S->top);
    return OK;
}

bool StackEmpty(SqStack S)							//�ж�˳��ջ�Ƿ�Ϊ��
{
    if(S.top==S.base)
        return true;
    else
        return false;
}

bool visited[MVNum];

void DFS(ALGraph G, int v)							//�ڽӱ��������ȱ������ǵݹ��㷨
{
	SqStack S;
	InitStack(&S);
	Push(&S, v);
	while(!StackEmpty(S))
	{
		int k;
		Pop(&S, &k);
		if(!visited[k])
		{
			printf("%c ", G.vertices[k].data);
			visited[k]=true;
			ArcNode *p=G.vertices[k].firstarc;
			while(p!=NULL)
			{
				int w=p->adjvex;
				if(!visited[w])
					Push(&S, w);
				p=p->nextarc;
			}
		}
	}
}

void main()
{
	printf("�봴��һ������ͼ��\n");
	ALGraph G;
	CreateUDG(&G);
	printf("�����ɹ���\n");
	printf("������һ��������±��Կ�ʼ��������������");
	int v;
	scanf("%d", &v);
	printf("���������ĵ�������������������ǵݹ飩�Ľ��Ϊ��\n");
	DFS(G, v);
}

/*
	һ����ͨͼ�����ڽӱ���Ϊ����ṹ�����һ���㷨��ʵ�ִӶ���v������������ȱ���
	�ķǵݹ��㷨
*/
