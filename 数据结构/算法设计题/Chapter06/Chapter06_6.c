#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdbool.h>
#define MVNum 100                            //最大顶点数
#define MAX 100
#define OK 1
#define ERROR 0
typedef char OtherInfo[20]; 			     //可以用来记录两顶点间的权值
typedef char VerTexType; 					 //顶点的数据类型
typedef int ArcType;

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

int LocateVex(ALGraph G, VerTexType vex)
{
    int i;
    for(i=0; i<G.vexnum; i++)
        if(vex==G.vertices[i].data)
            return i;
    return -1;
}

int CreateUDG(ALGraph *G)	 									     //采用邻接表表示法创建无向图
{
	printf("请输出无向图的总顶点数：");     					     //输入总顶点数，总边数
	scanf("%d", &(G->vexnum));
	printf("请输出无向图的总边数：");
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
    printf("请依次输入每条边依附的顶点（顶点A, 顶点B）：\n");
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
        ArcNode *p2=(ArcNode *)malloc(sizeof(ArcNode));              //生成另一个对称的新的边结点*p2
        p2->adjvex=i;                                                //邻接点序号为i
        p2->nextarc=G->vertices[j].firstarc;                         //将新结点*p2插入顶点vi的边表头部
        G->vertices[j].firstarc=p2;
    }
}

int visited[MVNum];													 //访问标记数组，其初值为false

int PathLenK(ALGraph G, int i, int j, int k)						 //基判断邻接表方式储存的有向图G的顶点i到j是否存在长度为k的简单路径
{
	if(i==j&&k==0)
		return 1;													 //找到了一条路径，且长度符合要求
	else if(k>0)
	{
		visited[i]=true;
		for(ArcNode *p=G.vertices[i].firstarc; p; p=p->nextarc)		 //从结点i开始遍历，p为i的边链表的第一个边结点
		{
			int v=p->adjvex;
			if(!visited[v])											 //v未被访问过
				if(PathLenK(G, v, j, k-1))
					return 1;										 //递归继续判断i到j，且剩余路径长度减1
		}
		visited[i]=false;											 //允许曾经被访问过的结点出现在另一条路径中
	}
	return 0;														 //未找到符合要求的路径
}

void main()
{
	printf("请创建一个无向图：\n");
	ALGraph G;
	CreateUDG(&G);
	printf("创建成功！\n");
	printf("请输入顶点v1和顶点v2的下标以及两顶点之间的距离k，以判断在顶点v1和顶点v2之间是否存在一条长度为k的简单路径：");
	int v1, v2, k;
	scanf("%d, %d, %d", &v1, &v2, &k);
	if(PathLenK(G, v1, v2, k))
		printf("顶点%c和顶点%c之间存在长度为%d的简单路径", G.vertices[v1].data, G.vertices[v2].data, k);
	else
		printf("顶点%c和顶点%c之间不存在长度为%d的简单路径", G.vertices[v1].data, G.vertices[v2].data, k);
}

/*
	采用邻接表储存结构，编写一个算法，判别无向图中任意给定的两个顶点之间是否存在一条长度为k的简单路径。
*/
