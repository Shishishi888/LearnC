#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdbool.h>
#define MVNum 100                            //最大顶点数
#define MAXSIZE 100
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


/*采用邻接表表示法创建有向图*/
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

/*拓扑排序*/
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

int indegree[MVNum];								//存放各顶点的入度
SqStack S;											//暂存所有入度为0的顶点
int topo[MVNum];									//记录拓扑序列的顶点序号

void FindInDegree(ALGraph G, int indegree[])		//统计各顶点的入度的函数
{
	ArcNode *p;
	for(int i=0; i<G.vexnum; i++)
		indegree[i]=0;								//各顶点入度初始化为0

	for(int j=0; j<G.vexnum; j++)
	{
		p=G.vertices[j].firstarc;
		while(p!=NULL)
		{
			indegree[p->adjvex]++;					//相应顶点入度加1
			p=p->nextarc;
		}
	}
}

int TopologicalSort(ALGraph G, int topo[])
{ //有向图G采用邻接表储存结构
  //若G无回路，则生成G的一个拓扑序列topo[]并返回OK，否则返回ERROR

	FindInDegree(G, indegree);                  //求出各顶点的入度存入数组indegree中
	InitStack(&S);								//栈S初始化为空
	for(int i=0; i<G.vexnum; ++i)
		if(!indegree[i])
			Push(&S, i);						//入度为0的顶点进栈
	int m=0;									//对输出顶点计数，初始为0
	while(!StackEmpty(S))						//栈S非空
	{
		int i;
		Pop(&S, &i);						  	//将栈顶顶点vi出栈
		topo[m]=i;								//将vi保存在拓扑序列数组topo中
		++m;									//对输出顶点计数
		ArcNode *p=G.vertices[i].firstarc;		//p指向vi的第一个邻接点
		while(p!=NULL)
		{
			int k=p->adjvex;					//vk为vi的邻接点
			--indegree[k];						//vi的每个邻接点的入度减1
			if(indegree[k]==0)
				Push(&S, k);					//若入度为0则入栈
			p=p->nextarc;						//p指向下一个邻接点
		}
	}

	if(m<G.vexnum)
		return ERROR;							//该有向图有回路
	else
		return OK;
}

void main()
{
	printf("请创建一个有向图：\n");
	ALGraph G;
	CreateUDG(&G);
	printf("创建成功！\n");
	if(TopologicalSort(G, topo))
	{
		printf("该有向图的拓扑排序结果为：\n");
		for(int i=0; i<G.vexnum; i++)
			printf("%c ", G.vertices[topo[i]]);
	}
	else
		printf("警告：您输入的有向图中有环！");


	printf("\n");
	printf("打印该有向图：\n");
	int i=0;
	while(i<G.vexnum)
	{
		printf("%c-->", G.vertices[i].data);
		ArcNode *p=G.vertices[i].firstarc;

		while(p)
		{
			printf("%c-->", G.vertices[p->adjvex].data);
			p=p->nextarc;
		}
		i++;
		printf("\n");
	}
}
