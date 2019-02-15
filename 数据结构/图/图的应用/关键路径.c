#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdbool.h>
#define MVNum 100                            //最大顶点数
#define MAXSIZE 100
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
    int vexnum, arcnum;                      //网的当前顶点数和边数
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
	printf("请输出有向网的总顶点数：");     					     //输入总顶点数，总边数
	scanf("%d", &(G->vexnum));
	printf("请输出有向网的总边数：");
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
{ //有向网G采用邻接表储存结构
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
		return ERROR;							//该有向网有回路
	else
		return OK;
}

/*关键路径算法*/
ArcType ve[MVNum];								//记录事件vi的最早发生时间
ArcType vl[MVNum];								//记录事件vl的最早发生时间

int CriticalPath(ALGraph G)
{ //G为邻接表储存的有向网，输出G的各项关键活动
	if(!TopologicalSort(G, topo))				//调用拓扑排序算法，使拓扑序列保存在topo中，若调用失败，则存在
		return ERROR;							//有向环，返回ERROR
	int n=G.vexnum;								//n为顶点个数
	for(int i=0; i<n; i++)
		ve[i]=0;								//给每个时间的最早发生时间初始化为0

	//按拓扑次序求每个事件的最早发生时间
	for(int i=0; i<n; i++)
	{
		int k=topo[i];							//取得拓扑序列中的顶点序号k
		ArcNode *p=G.vertices[k].firstarc; 		//p指向k的第一个邻接顶点
		while(p!=NULL)							//依次更新k的所有临界顶点的最早发生时间
		{
			int j=p->adjvex;					//j为邻接顶点的序号
			if(ve[j]<ve[k]+p->info)
				ve[j]=ve[k]+p->info;			//更新顶点j的最早发生时间
			p=p->nextarc;						//p指向k的下一个邻接顶点
		}
	}

	for(int i=0; i<n; i++)
		vl[i]=ve[n-1];							//给每个时间的最迟发生时间置初值ve[n-1]

	//按逆拓扑次序求每个事件的最迟发生时间
	for(int i=n-1; i>=0; i--)
	{
		int k=topo[i];							//取得拓扑序列中的顶点序号k
		ArcNode *p=G.vertices[k].firstarc;		//p指向k的第一个邻接顶点
		while(p!=NULL)							//根据k的邻接点，更新k的最迟发生时间
		{
			int j=p->adjvex;					//j为邻接顶点的序号
			if(vl[k]>vl[j]-p->info)
				vl[k]=vl[j]-p->info;			//更新顶点k的最迟发生时间
			p=p->nextarc;						//p指向k的下一个邻接点
		}
	}

	//判断每一个活动是否为关键活动
	for(int i=0; i<n; i++)						//每次循环针对vi为开始点的所有活动
	{
		ArcNode *p=G.vertices[i].firstarc;		//p指向i的第一个邻接顶点
		while(p!=NULL)
		{
			int j=p->adjvex;					//j为i邻接顶点的序号
			int e=ve[i];						//计算活动<vi, vj>的最早开始时间
			int l=vl[j]-p->info;				//计算活动<vi, vj>的最迟开始时间
			if(e==l)							//若为关键活动，则输出<vi, vj>
				printf("%c %c  ", G.vertices[i].data, G.vertices[j].data);
			p=p->nextarc;						//p指向i的下一个邻接顶点
		}
	}
}

void main()
{
	printf("请创建一个有向网：\n");
	ALGraph G;
	CreateUDG(&G);
	printf("创建成功！\n");
	printf("输出该有向网的关键路径：\n");
	if(!CriticalPath(G))
		printf("警告：您输入的有向网中有环！");

	printf("\n");
	printf("打印该有向网：\n");
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
