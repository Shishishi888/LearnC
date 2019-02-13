#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdbool.h>
#define MVNum 100                            //最大顶点数
#define MAX 100
#define OK 1
#define ERROR 0
typedef int OtherInfo;						 //可以用来记录两顶点间的权值
typedef char VerTexType; 					 //顶点的数据类型
typedef int ArcType;                         //假设边的权值类型为整形

typedef struct ArcNode                       //边结点
{
    int adjvex;                              //该边所指向的顶点的位置
    struct ArcNode *nextarc;                 //指向下一条边的指针
    OtherInfo info;                          //和边相关的信息
}ArcNode;

typedef struct VNode                         //顶点信息
{
    VerTexType data;
    ArcNode *firstarc;                       //指向第一条依附该顶点的边的指针
}VNode, AdjList[MVNum];                      //AdjList表示邻接表类型

typedef struct                               //邻接表
{
    AdjList vertices;
    int vexnum, arcnum;                      //图的当前顶点数和边数
}ALGraph;

/*采用邻接表表示法创建有向网*/
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
	printf("请输出有向图的总顶点数：");     					     //输入总顶点数，总边数
	scanf("%d", &(G->vexnum));
	printf("请输出有向图的总边数：");
    scanf("%d", &(G->arcnum));
	printf("请依次输入各顶点的信息：\n");

    for(int i=0; i<G->vexnum; i++)
    {
    	//fflush(stdin);                                             //刷新缓冲区
    	char c=getchar();											 //吃掉缓冲区中的“回车”
		printf("请输入第%d个顶点的信息：", i+1);					 //输入顶点的值
		scanf("%c", &(G->vertices[i].data));                         //依次输入顶点的信息
        G->vertices[i].firstarc=NULL;        						 //初始化表头结点的指针域为NULL
    }

    VerTexType v1, v2;
    ArcType w;
    printf("请依次输入每条边依附的顶点及权值（起点A, 终点B，权值）：\n");
    for(int k=0; k<G->arcnum; k++)           //输入各边，构造邻接表
    {
    	//fflush(stdin);				     //刷新缓冲区
    	char c=getchar();                    //吃掉缓冲区中的“回车”
    	printf("请输入第%d条边依附的顶点：", k+1);
        scanf("%c, %c, %d", &v1, &v2, &w);   //输入一条边依附的两个顶点
        int i=LocateVex(*G, v1);             //确定v1和v2在G中的位置，即顶点在G->vertices中的序号
        int j=LocateVex(*G, v2);
        ArcNode *p1=(ArcNode *)malloc(sizeof(ArcNode));              //生成新的边的结点*p1
        p1->adjvex=j;                                                //邻接点序号为j
        p1->info=w;
        p1->nextarc=G->vertices[i].firstarc;                         //将新结点*p1插入顶点vi的边表头部
        G->vertices[i].firstarc=p1;
    }
}

/*深度优先搜索遍历连通网*/
bool visited[MVNum];
void DFS_AL(ALGraph G, int v)
{
    printf("%c ", G.vertices[v].data);                     //访问第v个顶点，并置访问标志数组相应分量值为true
    visited[v]=true;
    ArcNode *p=G.vertices[v].firstarc;                     //p指向v的边链表的第一个边结点
    while(p!=NULL)                                         //边结点非空
    {
        int w=p->adjvex;                                   //表示w是v的邻接点
        if(!visited[w])                                    //如果w未访问，则递归调用DFS_AL
            DFS_AL(G, w);
        p=p->nextarc;                                      //p指向下一个边结点
    }
}

/*深度优先遍历非连通网*/
void DFSTraverse_AL(ALGraph G)
{
	for(int v=0; v<G.vexnum; v++)
		visited[v]=false;                                              //访问标志数组初始化
	for(int v=0; v<G.vexnum; v++)									   //循环调用算法DFS_AL
		if(!visited[v])												   //对尚未访问的顶点调用DFS_AL
			DFS_AL(G, v);
}

/*广度优先搜索遍历连通网*/
typedef struct
{
    int *base;
    int front;
    int rear;
}SqQueue;

int InitQueue(SqQueue *Q)											   //循环队列初始化
{
    Q->base=(int *)malloc(sizeof(int)*MAX);
    if(!Q->base)
        exit(0);
    Q->front=Q->rear=0;
    return OK;
}

int EnQueue(SqQueue *Q, int e)									       //循环队列的入队
{
    if((Q->rear+1)%MAX==Q->front)
        return ERROR;
    Q->base[Q->rear]=e;
    Q->rear=(Q->rear+1)%MAX;
    return OK;
}

int DeQueue(SqQueue *Q, int *e)										   //循环队列出队
{
    if(Q->front==Q->rear)
        return ERROR;
    *e=Q->base[Q->front];
    Q->front=(Q->front+1)%MAX;
    return OK;
}

bool QueueEmpty(SqQueue Q)											   //循环队列出队
{
    if(Q.front==Q.rear)
        return true;
    else
        return false;
}

bool visited_1[MVNum];                                                 //访问标记数组，便于在遍历过程中区分某个顶点是否已经被访问，其初值为false，一旦被访问，其相应的分量值设为true
void BFS_AL(ALGraph G, int v)
{
    printf("%c ", G.vertices[v].data);                                 //访问第v个顶点，并置访问标志数组相应分量值为true
    visited_1[v]=true;
    SqQueue Q;
    InitQueue(&Q);                                                     //辅助队列Q初始化，置空
    EnQueue(&Q, v);                                                    //v进队
    int u;

    while(!QueueEmpty(Q))
    {
        DeQueue(&Q, &u);                                               //队头元素出队，并置为u
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

/*广度优先搜索遍历非连通网*/
void BFSTraverse_AL(ALGraph G)
{
	for(int v=0; v<G.vexnum; v++)
		visited_1[v]=false;                                              //访问标志数组初始化
	for(int v=0; v<G.vexnum; v++)									     //循环调用算法DFS_AM
		if(!visited_1[v])												 //对尚未访问的顶点调用DFS_AM
			BFS_AL(G, v);
}

void main()
{
	printf("请创建一个有向网：\n");
	ALGraph G;
	CreateUDG(&G);
	printf("创建成功！\n");
	printf("请输入一个顶点的下标以开始遍历该有向网：");
	int v;
	scanf("%d", &v);
	printf("该有向网的的深度优先搜索遍历的结果为：\n");
	DFSTraverse_AL(G);
	printf("\n");
	printf("该有向网的的广度优先搜索遍历的结果为：\n");
	BFSTraverse_AL(G);
	printf("\n");

	printf("打印该有向网：\n");
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
