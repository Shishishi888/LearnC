#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>
#define MVNum 100                            //��󶥵���
#define MAX 100
#define OK 1
#define ERROR 0

typedef struct ArcNode                       //�߽��
{
    int adjvex;                              //�ñ���ָ��Ķ����λ��
    struct ArcNode *nextarc;                 //ָ����һ���ߵ�ָ��
    char info[20];                           //�ͱ���ص���Ϣ
}ArcNode;

typedef struct VNode                         //������Ϣ
{
    char data;
    ArcNode *firstarc;                       //ָ���һ�������ö���ıߵ�ָ��
}VNode, AdjList[MVNum];                      //AdjList��ʾ�ڽӱ�����

typedef struct                               //�ڽӱ�
{
    AdjList vertices;
    int vexnum, arcnum;                      //ͼ�ĵ�ǰ�������ͱ���
}ALGraph;

int LocateVex(ALGraph *G, char vex)
{
    int i;
    for(i=0;i<G->vexnum;i++)
        if(vex==G->vertices[i].data)
            return i;
    return -1;
}
/*�����ڽӱ��ʾ����������ͼ*/
int CreateUDG(ALGraph *G)
{
    scanf("%d,%d",&G->vexnum,&G->arcnum);    //�����ܶ��������ܱ���
    int i;
    for(i=0;i<G->vexnum;i++)
    {
        scanf("%c",&(G->vertices[i].data));  //���붨����Ϣ
        G->vertices[i].firstarc=NULL;        //��ʼ����ͷ����ָ����ΪNULL
    }
    int k, m, n;
    char v1, v2;
    for(k=0;k<G->arcnum;k++)                 //������ߣ������ڽӱ�
    {
        scanf("%d,%d",&v1,&v2);              //����һ������������������
        m=LocateVex(G, v1);                  //ȷ��v1��v2��G�е�λ�ã���������G->vertices�е����
        n=LocateVex(G, v2);
        ArcNode *p1=(ArcNode *)malloc(sizeof(ArcNode));              //�����µıߵĽ��*p1
        p1->adjvex=n;                                                //�ڽӵ����Ϊn
        p1->nextarc=G->vertices[m].firstarc;                         //���½��*p1���붥��vi�ı߱�ͷ��
        G->vertices[m].firstarc=p1;
        ArcNode *p2=(ArcNode *)malloc(sizeof(ArcNode));              //������һ���ԳƵ��µı߽��*p2
        p2->adjvex=m;                                                //�ڽӵ����Ϊm
        p2->nextarc=G->vertices[n].firstarc;                         //���½��*p2���붥��vi�ı߱�ͷ��
        G->vertices[n].firstarc=p2;
    }
}

bool visited[MVNum];

/*�����ڽӱ��ʾͼ�����������������*/
void DFS_AL(ALGraph *G, int v)
{
    printf("%c ",G->vertices[v].data);                     //���ʵ�v�����㣬���÷��ʱ�־������Ӧ����ֵΪtrue
    visited[v]=true;
    ArcNode *p=G->vertices[i].firstarc;                    //pָ��v�ı�����ĵ�һ���߽��
    while(p!=NULL)                                         //�߽��ǿ�
    {
        int w=p->agjvex;                                   //��ʾw��v���ڽӵ�
        if(!visited[w])                                    //���wδ���ʣ���ݹ����DFS_AL
            DFS_AL(G, w);
        p=p->nextarc;                                      //pָ����һ���߽��
    }
}

typedef struct
{
    int *base;
    int front;
    int rear;
}SqQueue;

/*ѭ�����еĳ�ʼ��*/
int InitQueue(SqQueue *Q)
{
    Q->base=(int *)malloc(sizeof(int)*MAX);
    if(!Q->base)
        exit(0);
    Q->front=Q->rear=0;
    return OK;
}

/*ѭ�����е����*/
int EnQueue(SqQueue *Q, int e)
{
    if((Q->rear+1)%MAX==Q->front)
        return ERROR;
    Q->base[Q->rear]=e;
    Q->rear=(Q->rear+1)%MAX;
    return OK;
}

/*ѭ�����еĳ���*/
int DeQueue(SqQueue *Q, int *e)
{
    if(Q->front==Q->rear)
        return ERROR;
    e=&Q->base[Q->front];
    Q->front=(Q->front+1)%MAX;
    return OK;
}

/*�ж�ѭ�������Ƿ�Ϊ��*/
bool QueueEmpty(SqQueue *Q)
{
    if(Q->front==Q->rear)
        return true;
    else
        return false;
}

/*�����ڽӱ��ʾͼ�Ĺ��������������*/
void BFS_AM(AMGraph *G, int v)
{
    printf("%c ",G->vertices[v].data);                                   //���ʵ�v�����㣬���÷��ʱ�־������Ӧ����ֵΪtrue
    visited[v]=true;
    SqQueue *Q=(SqQueue *)malloc(sizeof(SqQueue));
    InitQueue(Q);                                                        //��������Q��ʼ�����ÿ�
    EnQueue(Q, v);                                                       //v����
    int *u;
    int w;
    while(!QueueEmpty(Q))
    {
        DeQueue(Q,u);                                                    //��ͷԪ�س��ӣ�����Ϊu
        for(w=FirstAdjVex(G,*u);w>=0;w=NextAdjVex(G,*u,w))               //���μ��u�������ڽӵ�w��FirstAdjVex(G,u)��ʾu�ĵ�һ���ڽӵ�
                                                                         //NextAdjVex(G,u,w)��ʾu�����w����һ���ڽӵ㣬w>=0��ʾ�����ڽӵ�
            if(!visited[w])                                              //wΪu����δ���ʵ��ڽӶ���
            {
                printf("%c ",vertices[w].data);                          //����w�����÷��ʱ�־������Ӧ����ֵΪtrue
                visited[w]=true;
                EnQueue(Q, w);                                           //w����
            }
    }
}

