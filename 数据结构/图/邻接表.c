#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>
#define MVNum 100                            //最大顶点数
#define MAX 100
#define OK 1
#define ERROR 0

typedef struct ArcNode                       //边结点
{
    int adjvex;                              //该边所指向的顶点的位置
    struct ArcNode *nextarc;                 //指向下一条边的指针
    char info[20];                           //和边相关的信息
}ArcNode;

typedef struct VNode                         //顶点信息
{
    char data;
    ArcNode *firstarc;                       //指向第一条依附该顶点的边的指针
}VNode, AdjList[MVNum];                      //AdjList表示邻接表类型

typedef struct                               //邻接表
{
    AdjList vertices;
    int vexnum, arcnum;                      //图的当前顶点数和边数
}ALGraph;

int LocateVex(ALGraph *G, char vex)
{
    int i;
    for(i=0;i<G->vexnum;i++)
        if(vex==G->vertices[i].data)
            return i;
    return -1;
}
/*采用邻接表表示法创建无向图*/
int CreateUDG(ALGraph *G)
{
    scanf("%d,%d",&G->vexnum,&G->arcnum);    //输入总顶点数，总边数
    int i;
    for(i=0;i<G->vexnum;i++)
    {
        scanf("%c",&(G->vertices[i].data));  //输入定点信息
        G->vertices[i].firstarc=NULL;        //初始化表头结点的指针域为NULL
    }
    int k, m, n;
    char v1, v2;
    for(k=0;k<G->arcnum;k++)                 //输入各边，构造邻接表
    {
        scanf("%d,%d",&v1,&v2);              //输入一条边依附的两个顶点
        m=LocateVex(G, v1);                  //确定v1和v2在G中的位置，即顶点在G->vertices中的序号
        n=LocateVex(G, v2);
        ArcNode *p1=(ArcNode *)malloc(sizeof(ArcNode));              //生成新的边的结点*p1
        p1->adjvex=n;                                                //邻接点序号为n
        p1->nextarc=G->vertices[m].firstarc;                         //将新结点*p1插入顶点vi的边表头部
        G->vertices[m].firstarc=p1;
        ArcNode *p2=(ArcNode *)malloc(sizeof(ArcNode));              //生成另一个对称的新的边结点*p2
        p2->adjvex=m;                                                //邻接点序号为m
        p2->nextarc=G->vertices[n].firstarc;                         //将新结点*p2插入顶点vi的边表头部
        G->vertices[n].firstarc=p2;
    }
}

bool visited[MVNum];

/*采用邻接表表示图的深度优先搜索遍历*/
void DFS_AL(ALGraph *G, int v)
{
    printf("%c ",G->vertices[v].data);                     //访问第v个顶点，并置访问标志数组相应分量值为true
    visited[v]=true;
    ArcNode *p=G->vertices[i].firstarc;                    //p指向v的边链表的第一个边结点
    while(p!=NULL)                                         //边结点非空
    {
        int w=p->agjvex;                                   //表示w是v的邻接点
        if(!visited[w])                                    //如果w未访问，则递归调用DFS_AL
            DFS_AL(G, w);
        p=p->nextarc;                                      //p指向下一个边结点
    }
}

typedef struct
{
    int *base;
    int front;
    int rear;
}SqQueue;

/*循环队列的初始化*/
int InitQueue(SqQueue *Q)
{
    Q->base=(int *)malloc(sizeof(int)*MAX);
    if(!Q->base)
        exit(0);
    Q->front=Q->rear=0;
    return OK;
}

/*循环队列的入队*/
int EnQueue(SqQueue *Q, int e)
{
    if((Q->rear+1)%MAX==Q->front)
        return ERROR;
    Q->base[Q->rear]=e;
    Q->rear=(Q->rear+1)%MAX;
    return OK;
}

/*循环队列的出队*/
int DeQueue(SqQueue *Q, int *e)
{
    if(Q->front==Q->rear)
        return ERROR;
    e=&Q->base[Q->front];
    Q->front=(Q->front+1)%MAX;
    return OK;
}

/*判断循环队列是否为空*/
bool QueueEmpty(SqQueue *Q)
{
    if(Q->front==Q->rear)
        return true;
    else
        return false;
}

/*采用邻接表表示图的广度优先搜索遍历*/
void BFS_AM(AMGraph *G, int v)
{
    printf("%c ",G->vertices[v].data);                                   //访问第v个顶点，并置访问标志数组相应分量值为true
    visited[v]=true;
    SqQueue *Q=(SqQueue *)malloc(sizeof(SqQueue));
    InitQueue(Q);                                                        //辅助队列Q初始化，置空
    EnQueue(Q, v);                                                       //v进队
    int *u;
    int w;
    while(!QueueEmpty(Q))
    {
        DeQueue(Q,u);                                                    //队头元素出队，并置为u
        for(w=FirstAdjVex(G,*u);w>=0;w=NextAdjVex(G,*u,w))               //依次检查u的所有邻接点w，FirstAdjVex(G,u)表示u的第一个邻接点
                                                                         //NextAdjVex(G,u,w)表示u相对于w的下一个邻接点，w>=0表示存在邻接点
            if(!visited[w])                                              //w为u的尚未访问的邻接顶点
            {
                printf("%c ",vertices[w].data);                          //访问w，并置访问标志数组相应分量值为true
                visited[w]=true;
                EnQueue(Q, w);                                           //w进队
            }
    }
}

