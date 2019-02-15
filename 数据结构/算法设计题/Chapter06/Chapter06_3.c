#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdbool.h>
#define MVNum 100                            //最大顶点数
#define MAXSIZE 100
#define OK 1
#define ERROR 0
typedef char OtherInfo[20]; 			     //可以用来记录两顶点间的权值
typedef char VerTexType; 					 //顶点的数据类型

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

int CreateUDG(ALGraph *G)										     //采用邻接表表示法创建无向图
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

typedef int SElemType;
typedef struct
{
    SElemType *base;    						    //栈底指针
    SElemType *top;    								//栈顶指针
    int stacksize; 		 							//栈可用的最大容量
}SqStack;

int InitStack(SqStack *S)							//初始化顺序栈
{
    S->base=(SElemType *)malloc(sizeof(SElemType)*MAXSIZE);
    if(!(S->base))
        exit(0);
    S->top=S->base;
    S->stacksize=MAXSIZE;
    return OK;
}

int Push(SqStack *S, SElemType e)					//顺序栈的入栈
{
    if(S->top-S->base==S->stacksize)
        return ERROR;
    *(S->top++)=e;
    return OK;
}

int Pop(SqStack *S, SElemType *e)					//顺序栈的出栈
{
    if(S->top==S->base)
        return ERROR;
    *e=*(--S->top);
    return OK;
}

bool StackEmpty(SqStack S)							//判断顺序栈是否为空
{
    if(S.top==S.base)
        return true;
    else
        return false;
}

bool visited[MVNum];

void DFS(ALGraph G, int v)							//邻接表的深度优先遍历，非递归算法
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
	printf("请创建一个无向图：\n");
	ALGraph G;
	CreateUDG(&G);
	printf("创建成功！\n");
	printf("请输入一个顶点的下标以开始遍历该无向网：");
	int v;
	scanf("%d", &v);
	printf("该无向网的的深度优先搜索遍历（非递归）的结果为：\n");
	DFS(G, v);
}

/*
	一个连通图采用邻接表作为储存结构，设计一个算法，实现从顶点v出发的深度优先遍历
	的非递归算法
*/
