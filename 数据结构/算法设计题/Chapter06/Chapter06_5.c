#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdbool.h>
#define MVNum 100                            //最大顶点数
#define MAX 100
#define OK 1
#define ERROR 0
typedef char OtherInfo[20];					 //可以用来记录两顶点间的权值
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

int LocateVex(ALGraph G, VerTexType vex)	 //采用邻接表表示法创建有向图
{
    int i;
    for(i=0; i<G.vexnum; i++)
        if(vex==G.vertices[i].data)
            return i;
    return -1;
}

int CreateUDG(ALGraph *G)											 //采用邻接表表示法创建有向图
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
    printf("请依次输入每条边依附的顶点（起点A, 终点B）：\n");
    for(int k=0; k<G->arcnum; k++)           //输入各边，构造邻接表
    {
    	//fflush(stdin);				     //刷新缓冲区
    	char c=getchar();                    //吃掉缓冲区中的“回车”
    	printf("请输入第%d条边依附的顶点：", k+1);
        scanf("%c, %c", &v1, &v2);           //输入一条边依附的两个顶点
        int i=LocateVex(*G, v1);             //确定v1和v2在G中的位置，即顶点在G->vertices中的序号
	    int j=LocateVex(*G, v2);
        ArcNode *p1=(ArcNode *)malloc(sizeof(ArcNode));              //生成新的边的结点*p1
        p1->adjvex=j;                                                //邻接点序号为j
        p1->nextarc=G->vertices[i].firstarc;                         //将新结点*p1插入顶点vi的边表头部
        G->vertices[i].firstarc=p1;
    }
}

bool visited[MVNum];												 //访问标记数组
bool flag=false;													 //标记起点和终点之间是否有通路

void PathDFS(ALGraph G, int i, int j)								 //判断起点vi到终点vj之间是否有路径
{
    visited[i]=true;
    ArcNode *p=G.vertices[i].firstarc;                   			 //p指向v的边链表的第一个边结点
    while(p!=NULL)                                         			 //边结点非空
    {
        int w=p->adjvex;                                  			 //表示w是v的邻接点
        if(w==j)
		{
			flag=true;
			return;
		}

        if(!visited[w])                                   			 //如果w未访问，则递归调用PathDFS
            PathDFS(G, w, j);
        p=p->nextarc;                                    		     //p指向下一个边结点
    }
}

/*
int visited[MVNum];													 //访问标记数组，其初值为false
int level=1;														 //递归进行的层数
int PathDFS(ALGraph G, int i, int j)								 //基于深度优先搜索判断有向图G中顶点i到顶点j是否有路径，是则返回1，否则返回0
{
	if(i==j)
		return 1;													 //递归结束条件，首尾相遇，则存在路径
	else
	{
		visited[i]=true;											 //顶点i访问标志为true
		for(ArcNode *p=G.vertices[i].firstarc; p; p=p->nextarc, level--)
		{
			level++;												 //递归层次增1
			int k=p->adjvex;
			if(!visited[k]&&PathDFS(G, k, j))
				return 1;											 //i下游的顶点到j有路径
		}
	}
	if(level==1)
		return 0;													 //i到j没有路径
}
*/

void main()
{
	printf("请创建一个有向图：\n");
	ALGraph G;
	CreateUDG(&G);
	printf("创建成功！\n");
	printf("请输入两个顶点的下标，以判断该两个顶点之间是否有通路（起点A, 终点B）：");
	int v, w;
	scanf("%d, %d", &v, &w);
	PathDFS(G, v, w);
	if(flag)
	//if(PathDFS(G, v, w))
		printf("起点%c和终点%c之间有通路", G.vertices[v].data, G.vertices[w].data);
	else
		printf("起点%c和终点%c之间无通路", G.vertices[v].data, G.vertices[w].data);
}

/*
	试基于图的深度优先搜索策略写一算法，判别以邻接表方式储存的有向图是否存在由顶点vi到顶点vj的路径（i！=j）。
*/
