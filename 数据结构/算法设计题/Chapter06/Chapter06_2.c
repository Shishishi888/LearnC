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

int LocateVex(ALGraph G, VerTexType vex)
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

int InsertVex(ALGraph *G, VerTexType v)								 //增加一个新顶点v
{
	if(G->vexnum+1>MVNum)
		return ERROR;
	G->vertices[G->vexnum].data=v;
	G->vertices[G->vexnum].firstarc=NULL;
	G->vexnum++;
	return OK;
}


int DeleteVex(ALGraph *G, VerTexType v)								 //删除顶点v及其相关的边
{
	int n=LocateVex(*G, v);
	if(n<0)
		return ERROR;
	ArcNode *pointer=G->vertices[n].firstarc;
	while(pointer)
	{
		G->arcnum--;
		pointer=pointer->nextarc;
	}
	for(int i=n; i<G->vexnum; i++)
		G->vertices[i]=G->vertices[i+1];
	G->vexnum--;
	for(int i=0; i<G->vexnum; i++)									 //遍历图，删除与顶点v相关的边
	{
		ArcNode *p=G->vertices[i].firstarc;						     //p指向当前的结点
		ArcNode *q=NULL;											 //q指向当前结点的前驱
		if(!p)
			continue;
		if(p->adjvex==n)
		{
			G->vertices[i].firstarc=p->nextarc;
			G->arcnum--;
			continue;
		}
		else
		{
			p=p->nextarc;
			q=G->vertices[i].firstarc;

			while(p)
			{
				if(p->adjvex==n)
				{
					q->nextarc=p->nextarc;
					G->arcnum--;
					break;
				}
				p=p->nextarc;
				q=q->nextarc;
			}
		}
	}
}

int InsertArc(ALGraph*G, VerTexType v, VerTexType w)				 //增加一条边<v, w>
{
	int i=LocateVex(*G, v);
	int j=LocateVex(*G, w);
	if(i<0)
		return ERROR;
	if(j<0)
		return ERROR;
	ArcNode *p=(ArcNode *)malloc(sizeof(ArcNode));
	p->adjvex=j;
	p->nextarc=G->vertices[i].firstarc;
	G->vertices[i].firstarc=p;
	G->arcnum++;
	return OK;
}

int DeleteArc(ALGraph *G, VerTexType v, VerTexType w)				 //删除一条边<v, w>
{
	int i=LocateVex(*G, v);
	int j=LocateVex(*G, w);
	if(i<0)
		return ERROR;
	if(j<0)
		return ERROR;

	ArcNode *p=G->vertices[i].firstarc;								 //p指向当前的结点
	ArcNode *q=NULL;							   		 	 		 //q指向当前结点的前驱
	//if(!p)														 //不会出现p为空的情况
	if(p->adjvex==j)
	{
		G->vertices[i].firstarc=p->nextarc;
		G->arcnum--;
	}
	else
	{
		p=p->nextarc;
		q=G->vertices[i].firstarc;

		while(p)
		{
			if(p->adjvex==j)
			{
				q->nextarc=p->nextarc;
				G->arcnum--;
				break;
			}
			p=p->nextarc;
			q=q->nextarc;
		}
	}
	return OK;
}

void main()
{
	printf("请创建一个有向图：\n");
	ALGraph G;
	CreateUDG(&G);
	printf("创建成功！\n");
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


	char c=getchar();
	printf("添加一个新顶点，请输入要添加的新顶点：");
	VerTexType v;
	scanf("%c", &v);
	InsertVex(&G, v);
	printf("添加成功！打印更新后的有向图：\n");
	i=0;
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

	c=getchar();
	printf("删除一个顶点，请输入要删除的顶点：");
	scanf("%c", &v);
	DeleteVex(&G, v);
	printf("删除成功！打印更新后的有向图：\n");
	i=0;
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

	c=getchar();
	printf("添加一条边，请输入要添加的边（起点A, 终点B）：");
	VerTexType v1, w1;
	scanf("%c, %c", &v1, &w1);
	InsertArc(&G, v1, w1);
	printf("添加成功！打印更新后的有向图：\n");
	i=0;
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

	c=getchar();
	printf("删除一条边，请输入要删除的边（起点A, 终点B）：");
	scanf("%c, %c", &v1, &w1);
	DeleteArc(&G, v1, w1);
	printf("删除成功！打印更新后的有向图：\n");
	i=0;
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

/*
	以邻接表作为储存结构，实现以下图的基本操作：
	1 增加一个新顶点v，InsertVex(G, v)；
	2 删除顶点v及其相关的边，DeleteVex(G, v)；
	3 增加一条边<v, w>，InsertArc(G, v, w)；
	4 删除一条边<v, w>，DeleteArc(G, v, w)；
*/
