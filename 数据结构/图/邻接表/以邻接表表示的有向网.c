#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdbool.h>
#define MVNum 100                            //��󶥵���
#define MAX 100
#define OK 1
#define ERROR 0
typedef int OtherInfo;						 //����������¼��������Ȩֵ
typedef char VerTexType; 					 //�������������
typedef int ArcType;                         //����ߵ�Ȩֵ����Ϊ����

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

/*�����ڽӱ��ʾ������������*/
int LocateVex(ALGraph G, VerTexType vex)
{
    int i;
    for(i=0; i<G.vexnum; i++)
        if(vex==G.vertices[i].data)
            return i;
    return -1;
}

int CreateUDG(ALGraph *G)
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
    ArcType w;
    printf("����������ÿ���������Ķ��㼰Ȩֵ�����A, �յ�B��Ȩֵ����\n");
    for(int k=0; k<G->arcnum; k++)           //������ߣ������ڽӱ�
    {
    	//fflush(stdin);				     //ˢ�»�����
    	char c=getchar();                    //�Ե��������еġ��س���
    	printf("�������%d���������Ķ��㣺", k+1);
        scanf("%c, %c, %d", &v1, &v2, &w);   //����һ������������������
        int i=LocateVex(*G, v1);             //ȷ��v1��v2��G�е�λ�ã���������G->vertices�е����
        int j=LocateVex(*G, v2);
        ArcNode *p1=(ArcNode *)malloc(sizeof(ArcNode));              //�����µıߵĽ��*p1
        p1->adjvex=j;                                                //�ڽӵ����Ϊj
        p1->info=w;
        p1->nextarc=G->vertices[i].firstarc;                         //���½��*p1���붥��vi�ı߱�ͷ��
        G->vertices[i].firstarc=p1;
    }
}

/*�����������������ͨ��*/
bool visited[MVNum];
void DFS_AL(ALGraph G, int v)
{
    printf("%c ", G.vertices[v].data);                     //���ʵ�v�����㣬���÷��ʱ�־������Ӧ����ֵΪtrue
    visited[v]=true;
    ArcNode *p=G.vertices[v].firstarc;                     //pָ��v�ı�����ĵ�һ���߽��
    while(p!=NULL)                                         //�߽��ǿ�
    {
        int w=p->adjvex;                                   //��ʾw��v���ڽӵ�
        if(!visited[w])                                    //���wδ���ʣ���ݹ����DFS_AL
            DFS_AL(G, w);
        p=p->nextarc;                                      //pָ����һ���߽��
    }
}

/*������ȱ�������ͨ��*/
void DFSTraverse_AL(ALGraph G)
{
	for(int v=0; v<G.vexnum; v++)
		visited[v]=false;                                              //���ʱ�־�����ʼ��
	for(int v=0; v<G.vexnum; v++)									   //ѭ�������㷨DFS_AL
		if(!visited[v])												   //����δ���ʵĶ������DFS_AL
			DFS_AL(G, v);
}

/*�����������������ͨ��*/
typedef struct
{
    int *base;
    int front;
    int rear;
}SqQueue;

int InitQueue(SqQueue *Q)											   //ѭ�����г�ʼ��
{
    Q->base=(int *)malloc(sizeof(int)*MAX);
    if(!Q->base)
        exit(0);
    Q->front=Q->rear=0;
    return OK;
}

int EnQueue(SqQueue *Q, int e)									       //ѭ�����е����
{
    if((Q->rear+1)%MAX==Q->front)
        return ERROR;
    Q->base[Q->rear]=e;
    Q->rear=(Q->rear+1)%MAX;
    return OK;
}

int DeQueue(SqQueue *Q, int *e)										   //ѭ�����г���
{
    if(Q->front==Q->rear)
        return ERROR;
    *e=Q->base[Q->front];
    Q->front=(Q->front+1)%MAX;
    return OK;
}

bool QueueEmpty(SqQueue Q)											   //ѭ�����г���
{
    if(Q.front==Q.rear)
        return true;
    else
        return false;
}

bool visited_1[MVNum];                                                 //���ʱ�����飬�����ڱ�������������ĳ�������Ƿ��Ѿ������ʣ����ֵΪfalse��һ�������ʣ�����Ӧ�ķ���ֵ��Ϊtrue
void BFS_AL(ALGraph G, int v)
{
    printf("%c ", G.vertices[v].data);                                 //���ʵ�v�����㣬���÷��ʱ�־������Ӧ����ֵΪtrue
    visited_1[v]=true;
    SqQueue Q;
    InitQueue(&Q);                                                     //��������Q��ʼ�����ÿ�
    EnQueue(&Q, v);                                                    //v����
    int u;

    while(!QueueEmpty(Q))
    {
        DeQueue(&Q, &u);                                               //��ͷԪ�س��ӣ�����Ϊu
        ArcNode *p=G.vertices[u].firstarc;
        while(p)
		{
			if(!visited_1[p->adjvex])
			{
				printf("%c ", G.vertices[p->adjvex]);
				visited_1[p->adjvex]=true;
				EnQueue(&Q, p->adjvex);
			}
			p=p->nextarc;
        }
    }
}

/*�������������������ͨ��*/
void BFSTraverse_AL(ALGraph G)
{
	for(int v=0; v<G.vexnum; v++)
		visited_1[v]=false;                                              //���ʱ�־�����ʼ��
	for(int v=0; v<G.vexnum; v++)									     //ѭ�������㷨DFS_AM
		if(!visited_1[v])												 //����δ���ʵĶ������DFS_AM
			BFS_AL(G, v);
}

void main()
{
	printf("�봴��һ����������\n");
	ALGraph G;
	CreateUDG(&G);
	printf("�����ɹ���\n");
	printf("������һ��������±��Կ�ʼ��������������");
	int v;
	scanf("%d", &v);
	printf("���������ĵ�����������������Ľ��Ϊ��\n");
	DFSTraverse_AL(G);
	printf("\n");
	printf("���������ĵĹ���������������Ľ��Ϊ��\n");
	BFSTraverse_AL(G);
	printf("\n");

	printf("��ӡ����������\n");
	int i=0;
	while(i<G.vexnum)
	{
		printf("%c-->", G.vertices[i].data);
		ArcNode *p=G.vertices[i].firstarc;

		while(p)
		{
			printf("%c(%d)-->", G.vertices[p->adjvex].data, p->info);
			p=p->nextarc;
		}

		i++;
		printf("\n");
	}
}
