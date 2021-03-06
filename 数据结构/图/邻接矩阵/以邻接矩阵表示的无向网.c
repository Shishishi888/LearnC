#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>
#define MaxInt 32767                                                //表示最大值，即无限符
#define MVNum 100                                                   //最大顶点数
#define MAX 100
#define OK 1
#define ERROR 0
typedef char VerTexType;                                            //假设顶点的数据类型为字符型
typedef int ArcType;                                                //假设边的权值类型为整形

typedef struct
{
    VerTexType vexs[MVNum];                                         //顶点表，假设顶点的数据类型为字符型
    ArcType arcs[MVNum][MVNum];                                     //邻接矩阵,假设边的权值类型为整形
    int vexnum, arcnum;                                             //网的当前顶点数和边数
}AMGraph;

/*采用邻接矩阵表示法创建无向网*/
int LocateVex(AMGraph G, VerTexType vex)                            //确定vex在G中的位置，即顶点数组的下标
{
    int i;
    for(i=0; i<G.vexnum; i++)
        if(vex==G.vexs[i])
            return i;
    return -1;
}

int CreateUDN(AMGraph *G)
{
	printf("请输出无向网的总顶点数：");
	scanf("%d", &(G->vexnum));
	printf("请输出无向网的总边数：");
    scanf("%d", &(G->arcnum));

    printf("请依次输入各顶点的信息：\n");
    for(int i=0; i<G->vexnum; i++)
	{
		char c=getchar();											 //吃掉缓冲区中的“回车”
		printf("请输入第%d个顶点的信息：", i+1);
		scanf("%c", &(G->vexs[i]));                                  //依次输入顶点的信息
	}

    for(int i=0; i<G->vexnum; i++)                                   //初始化邻接矩阵，边的权值均置为最大值MaxInt
        for(int j=0; j<G->vexnum; j++)
            G->arcs[i][j]=MaxInt;

    VerTexType v1, v2;
    ArcType w;
	printf("请依次输入每条边依附的顶点及权值（顶点A, 顶点B, 权值）：\n");
    for(int k=0; k<G->arcnum; k++)                                   //构造邻接矩阵
    {
		char c=getchar();											 //吃掉缓冲区中的“回车”
    	printf("请输入第%d条边依附的顶点及权值：", k+1);
        scanf("%c, %c, %d", &v1, &v2, &w);                           //输入一条边依附的顶点及权值
        int i=LocateVex(*G, v1);                                     //确定v1和v2在G中的位置，即顶点数组的下标
        int j=LocateVex(*G, v2);
        G->arcs[i][j]=w;                                             //边(v1,v2)的权值置为w
        G->arcs[j][i]=G->arcs[i][j];                                 //置(v1,v2)的对称边(v2,v1)的权值为w

    }
    return OK;
}

/*深度优先搜索遍历连通网*/
bool visited[MVNum];                                                 //访问标记数组，便于在遍历过程中区分某个顶点是否已经被访问，其初值为false，一旦被访问，其相应的分量值设为true
void DFS_AM(AMGraph G, int v)                                        //网G为邻接矩阵类型，从第v个顶点出发深度优先搜索遍历图G
{
    printf("%c ",G.vexs[v]);                                         //访问第v个顶点，并置访问标志数组相应分量值为true
    visited[v]=true;
    for(int w=0; w<G.vexnum; w++)
        if((G.arcs[v][w]!=MaxInt)&&(!visited[w]))                    //w是v的邻接点，如果w为访问，则递归调用DFS_AL
            DFS_AM(G, w);
}


/*深度优先搜索遍历非连通网*/
void DFSTraverse_AM(AMGraph G)
{
	for(int v=0; v<G.vexnum; v++)
		visited[v]=false;                                             //访问标志数组初始化
	for(int v=0; v<G.vexnum; v++)									  //循环调用算法DFS_AM
		if(!visited[v])												  //对尚未访问的顶点调用DFS_AM
			DFS_AM(G, v);
}

/*广度优先搜索遍历连通网*/
typedef struct
{
    int *base;
    int front;
    int rear;
}SqQueue;

int InitQueue(SqQueue *Q)											  //循环队列初始化
{
    Q->base=(int *)malloc(sizeof(int)*MAX);
    if(!Q->base)
        exit(0);
    Q->front=Q->rear=0;
    return OK;
}

int EnQueue(SqQueue *Q, int e)									      //循环队列的入队
{
    if((Q->rear+1)%MAX==Q->front)
        return ERROR;
    Q->base[Q->rear]=e;
    Q->rear=(Q->rear+1)%MAX;
    return OK;
}

int DeQueue(SqQueue *Q, int *e)										  //循环队列出队
{
    if(Q->front==Q->rear)
        return ERROR;
    *e=Q->base[Q->front];
    Q->front=(Q->front+1)%MAX;
    return OK;
}

bool QueueEmpty(SqQueue Q)											  //循环队列出队
{
    if(Q.front==Q.rear)
        return true;
    else
        return false;
}

bool visited_1[MVNum];                                                //访问标记数组，便于在遍历过程中区分某个顶点是否已经被访问，其初值为false，一旦被访问，其相应的分量值设为true
void BFS_AM(AMGraph G, int v)
{
    printf("%c ", G.vexs[v]);                                         //访问第v个顶点，并置访问标志数组相应分量值为true
    visited_1[v]=true;
    SqQueue Q;
    InitQueue(&Q);                                                    //辅助队列Q初始化，置空
    EnQueue(&Q, v);                                                   //v进队
    int u;

    while(!QueueEmpty(Q))
    {
        DeQueue(&Q, &u);                                              //队头元素出队，并置为u
		for(int w=0; w<G.vexnum; w++)
            if(G.arcs[u][w]!=0&&!visited_1[w])                        //w为u的尚未访问的邻接顶点
            {
                printf("%c ",G.vexs[w]);                              //访问w，并置访问标志数组相应分量值为true
                visited_1[w]=true;
                EnQueue(&Q, w);                                       //w进队
            }
    }

}

/*广度优先搜索遍历非连通网*/
void BFSTraverse_AM(AMGraph G)
{
	for(int v=0; v<G.vexnum; v++)
		visited_1[v]=false;                                            //访问标志数组初始化
	for(int v=0; v<G.vexnum; v++)									   //循环调用算法DFS_AM
		if(!visited_1[v])											   //对尚未访问的顶点调用DFS_AM
			BFS_AM(G, v);
}

void main()
{
	printf("请创建一个无向网：\n");
	AMGraph G;
	CreateUDN(&G);
	printf("创建成功！\n");

	printf("请输入一个顶点的下标以开始遍历该无向网：");
	int v;
	scanf("%d", &v);
	printf("该无向网的深度优先搜索遍历的结果为：\n");
	DFS_AM(G, v);
	printf("\n");
	printf("该无向网的广度优先搜索遍历的结果为：\n");
	BFS_AM(G, v);

	printf("\n");
	printf("打印该无向网：\n");
	for(int i=0; i<G.vexnum; i++)
	{
		for(int j=0; j<G.vexnum; j++)
			printf("%8d", G.arcs[i][j]);
		printf("\n");
	}
}
