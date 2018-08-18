#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>
#define MaxInt 32767                                                //表示最大值，即无限符
#define MVNum 100                                                   //最大顶点数
#define MAX 100
#define OK 1
#define ERROR 0

typedef struct
{
    char vexs[MVNum];                                               //顶点表，假设顶点的数据类型为字符型
    int arcs[MVNum][MVNum];                                         //邻接矩阵,假设边的权值类型为整形
    int vexnum, arcnum;                                             //图的当前顶点数和边数
}AMGraph;

int LocateVex(AMGraph *G, char vex)
{
    int i;
    for(i=0;i<G->vexnum;i++)
        if(vex==G->vexs[i])
            return i;
    return -1;
}

/*采用邻接矩阵表示法创建无向图*/
int CreateUDN(AMGraph *G)
{
    scanf("%d,%d",&(G->vexnum),&(G->arcnum));                        //输入总顶点数和总边数
    int i, j, k;
    for(i=0;i<G->vexnum;i++)
        scanf("%c",&(G->vexs[i]));                                   //依次输入顶点的信息
    for(i=0;i<G->vexnum;i++)                                         //初始化邻接矩阵，边的权值均置为最大值MaxInt
        for(j=0;j<G->vexnum;j++)
            G->arcs[i][j]=MaxInt;
    char v1, v2;
    int w;
    for(j=0;j<G->arcnum;j++)                                         //构造邻接矩阵
    {
        scanf("%c,%c,%d",&v1,&v2,&w);                                //输入一条边衣服的顶点及权值
        i=LocateVex(G,v1);                                           //确定v1和v2在G中的位置，即顶点数组的下标
        j=LocateVex(G,v2);
        G->arcs[i][j]=w;                                             //边<v1,v2>的权值置为w
        G->arcs[j][i]=G->arcs[i][j];                                 //置<v1,v2>的对称边<v2,v1>的权值为w
    }
    return OK;
}

bool visited[MVNum];                                                 //访问标记数组，便于在遍历过程中区分某个顶点是否已经被访问，其初值为false，一旦被访问，其相应的分量值设为true

/*采用邻接矩阵表示图的深度优先搜索遍历*/
void DFS_AM(AMGraph *G, int v)                                       //图G为邻接矩阵类型，从第v个顶点出发深度优先搜索遍历图G
{
    printf("%c ",G->vexs[v]);                                        //访问第v个顶点，并置访问标志数组相应分量值为true
    visited[v]=true;
    int w;
    for(w=0;w<G->vexnum;w++)
        if((G->arcs[v][w]!=MaxInt)&&(!visited[w]))                   //w是v的邻接点，如果w为访问，则递归调用DFS_AL
            DFS_AM(G, w);
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

/*采用邻接矩阵表示图的广度优先搜索遍历*/
void BFS_AM(AMGraph *G, int v)
{
    printf("%c ",G->vexs[v]);                                               //访问第v个顶点，并置访问标志数组相应分量值为true
    visited[v]=true;
    SqQueue *Q=(SqQueue *)malloc(sizeof(SqQueue));
    InitQueue(Q);                                                           //辅助队列Q初始化，置空
    EnQueue(Q, v);                                                          //v进队
    int *u;
    int w;
    while(!QueueEmpty(Q))
    {
        DeQueue(Q,u);                                                       //队头元素出队，并置为u
        for(w=FirstAdjVex(G,*u);w>=0;w=NextAdjVex(G,*u,w))                  //依次检查u的所有邻接点w，FirstAdjVex(G,u)表示u的第一个邻接点
                                                                            //NextAdjVex(G,u,w)表示u相对于w的下一个邻接点，w>=0表示存在邻接点
            if(!visited[w])                                                 //w为u的尚未访问的邻接顶点
            {
                printf("%c ",G->vexs[w]);                                   //访问w，并置访问标志数组相应分量值为true
                visited[w]=true;
                EnQueue(Q, w);                                              //w进队
            }
    }
}

/*最小生成树（普里姆算法）*/
struct
{
    char adjvex;                                                             //最小边在U中的顶点
    int lowcost;                                                             //最小边上的权值
}Closedge;                                                                   //在主函数中声明Closedge closedge[MVNum]

int Min(Closedge *closedge, int vexnum)
{
    int i, j;
    int min;
    min=closedge[0].lowcost;
    for(i=0;i<vexnum;i++)
    {
        if(min>closedge[i].lowcost)
        {
            min=closedge[i].lowcost;
            j=i;
        }
    }
    return j;
}

void MiniSpanTree_Prim(AMGraph *G, char u, Closedge *closedge)                //无向图G以邻接矩阵形式储存，从顶点u出发构造G的最小生成树T，输出T的各条边
{
    int k=LocateVex(G, u);                                                    //k为顶点u的下标
    int j;
    for(j=0;j<G->vexnum;++j)                                                  //对V-U的每一个顶点vj，初始化closedge[j]
        if(j!=k)
        {
            closedge[j].adjvex=u;
            closedge[j].lowcost=G->arcs[k][j];
        }
    closedge[k].lowcost=0;                                                  //初始化，U={u}
    int i;
    for(i=1;i<G->vexnum;++i)                                                  //选择其余n-1个顶点，生成n-1条边（n=G.vexnum）
    {
        k=Min(closedge, G->vexnum);                                           //求出T的下一个结点：第k个顶点，closedge[k]中存有当前最小边
        char u0=closedge[k].adjvex;                                           //u0为最小边的一个顶点，u0属于U
        char v0=G->vexs[k];                                                   //v0为最小边的另一个顶点，v0属于V-U
        printf("%d %d ",u0, v0);
        closedge[k].lowcost=0;                                              //第k个顶点并入U集
        for(j=0;j<G->vexnum;++j)
        {
            if(G->arcs[k][j]<closedge[j].lowcost)                           //新顶点并入U后重新选择最小边
            {
                closedge[j].adjvex=G->vexs[k];
                closedge[j].lowcost=G->arcs[k][j];
            }
        }
    }
}

/*最小生成树（克鲁斯卡尔算法）*/
struct
{
    char Head;                                                 //边的始点
    char Tail;                                                 //边的终点
    int lowcost;                                               //边上的权值
}Edge;                                                         //在主函数中声明Edge edge[arcnum]

int Vexset[MVNum];                                             //辅助数组

void Sort(Edge *egde, int arcnum)
{
    int i, j, temp;
    for(i=0;i<arcnum-1;i++)
        for(j=arcnum-1;j>=i+1;j--)
            if(edge[j].lowcost<edge[j-1].lowcost)
            {
                temp=edge[j].lowcost;
                edge[j].lowcost=edge[j-1].lowcost;
                edge[j-1].lowcost=temp;
            }
}

void MiniSpanTree_Kruskal(AMGraph *G, Edge *edge)              //无向图G以邻接矩阵形式储存，构造G的最小生成树T，输出T的各条边
{
    Sort(edge, G->arcnum);
    int i;                                                     //将数组Edge中的元素按权值从小到大排序
    for(i=0;i<G->arcnum;++i)                                   //辅助数组，表示各顶点自成一个连通分量
        Vexset[i]=i;
    for(i=0;i<G->arcnum;++i)                                   //依次查看数组中Edge中的边
    {
        int v1=LocateVex(G, edge[i].Head);                     //v1为边的始点Head的下标
        int v2=LocateVex(G, edge[i].Tail);                     //v2为边的终点T(closedge+j)->ail的下标
        int vs1=Vexset[v1];                                    //获取边Edge[i]的始点所在的连通分量vs1
        int vs2=Vexset[v2];                                    //获取边Edge[i]的终点所在的连通分量vs2
        if(vs1!=vs2)
        {
            printf("%d %d ", edge[i].Head, edge[i].Tail);      //输出此边
            int j;
            for(j=0;j<G->vexnum;++j)                           //合并vs1和vs2两个分量，即两个集合统一编号
                if(Vexset[j]==vs2)                             //集合编号为vs2的都改为vs1
                    Vexset[j]=vs1;
        }
    }
}

bool S[MVNum];                                                  //记录源点v0到终点vi是否已被确定最短路径长度，true表示确定，false表示尚未确定
char Path[MVNum];                                               //记录源点v0到终点vi的当前最短路径上vi的直接前驱顶点序号，其初值为：如果v0到vi有弧，则Path[i]为v0，否则为-1
int D[MVNum];                                                   //记录从源点v0到终点vi的当前最短路径长度，其初值为：如果从v0到vi有弧，则D[i]为弧上的权值，否则为∞

/*最短路径（迪杰斯特拉算法）*/
void ShortestPath_DIJ(AMGraph *G, int v0)                       //用Dijkstra算法求有向图G的v0顶点到其余顶点的最短路径
{
    int n=G->vexnum;                                            //n为G中顶点的个数
    int v;
    for(v=0;v<n;++v)                                            //n个顶点依次初始化
    {
        S[v]=false;                                             //S初始为空集
        D[v]=G->arcs[v0][v];                                    //将v0到各个终点的最短路径长度初始化为狐上的权值
        if(D[v]<MaxInt)                                         //如果v0到v之间有弧，则将v的前驱置为v0
            Path[v]=v0;
        else
            Path[v]=-1;                                         //如果v0到v之间无弧，则将v的前驱置为-1
    }
    S[v0]=true;                                                 //将v0加入S
    D[v0]=0;                                                    //源点到源点的距离为0

    int i;                                                      //初始化结束，开始主循环，每次求得v0到某个顶点v的最短路径，将v加入S集
    for(i=1;i<n;++i)                                            //对其余n-1个顶点，依次进行计算
    {
        int min=MaxInt;
        int w;
        for(w=0;w<n;++w)
        if(!S[w]&&D[w]<min)                                     //选择一条当前的最短路径，终点为v
        {
            v=w;                                                //将v加入S
            min=D[w];
        }
        S[v]=true;                                              //更新从v0出发到集合V-S上所有顶点的最短路径长度
        for(w=0;w<n;++w)
            if(!S[w]&&(D[v]+G->arcs[v][w]<D[w]))
            {
                D[w]=D[v]+G->arcs[v][w];                        //更新D[w]
                Path[w]=v;                                      //更新w的前驱为v
            }
    }
}








