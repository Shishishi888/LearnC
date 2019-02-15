#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>
#define MVNum 100                                                    //最大顶点数
#define MAX 100
#define OK 1
#define ERROR 0
typedef char VerTexType;                                             //假设顶点的数据类型为字符型
typedef int ArcType;                                                 //假设边的权值类型为整形

typedef struct
{
    VerTexType vexs[MVNum];                                          //顶点表，假设顶点的数据类型为字符型
    ArcType arcs[MVNum][MVNum];                                      //邻接矩阵,假设边的权值类型为整形
    int vexnum, arcnum;                                              //图的当前顶点数和边数
}AMGraph;


int LocateVex(AMGraph G, VerTexType vex)                             //确定vex在G中的位置，即顶点数组的下标
{
    int i;
    for(i=0; i<G.vexnum; i++)
        if(vex==G.vexs[i])
            return i;
    return -1;
}

int CreateUDN(AMGraph *G)											 //采用邻接矩阵表示法创建有向图
{
	printf("请输出有向图的总顶点数：");
	scanf("%d", &(G->vexnum));
	printf("请输出有向图的总边数：");
    scanf("%d", &(G->arcnum));

    printf("请依次输入各顶点的信息：\n");
    for(int i=0; i<G->vexnum; i++)
	{
		char c=getchar();											 //吃掉缓冲区中的“回车”
		printf("请输入第%d个顶点的信息：", i+1);
		scanf("%c", &(G->vexs[i]));                                  //依次输入顶点的信息
	}

    for(int i=0; i<G->vexnum; i++)                                   //初始化邻接矩阵
        for(int j=0; j<G->vexnum; j++)
            G->arcs[i][j]=0;

    VerTexType v1, v2;
	printf("请依次输入每条边依附的顶点（起点A, 终点B）：\n");
    for(int k=0; k<G->arcnum; k++)                                   //构造邻接矩阵
    {
		char c=getchar();											 //吃掉缓冲区中的“回车”
    	printf("请输入第%d条边依附的顶点: ", k+1);
        scanf("%c, %c", &v1, &v2);                       		     //输入一条边依附的顶点
        int i=LocateVex(*G, v1);                                     //确定v1和v2在G中的位置，即顶点数组的下标
        int j=LocateVex(*G, v2);
        G->arcs[i][j]=1;                                             //边<v1,v2>的权值置为1
        G->arcs[j][i]=0;                                			 //置<v1,v2>的对称边<v2,v1>的权值为1

    }
    return OK;
}

int InsertVex(AMGraph *G, VerTexType v)								 //增加一个新顶点v
{
	if(G->vexnum+1>MVNum)
		return ERROR;
	G->vexs[G->vexnum]=v;
	for(int i=0; i<G->vexnum; i++)
		G->arcs[G->vexnum][i]=G->arcs[i][G->vexnum]=0;
	G->vexnum++;
	return OK;
}

int DeleteVex(AMGraph *G, VerTexType v)								 //删除顶点v及其相关的边
{
	int m=LocateVex(*G, v);
	if(m<0)
		return ERROR;
	int n=G->vexnum-1;

	VerTexType temp=G->vexs[m];
	G->vexs[m]=G->vexs[n];
	G->vexs[n]=temp;

	for(int i=0; i<G->vexnum; i++)
	{
		VerTexType temp_1=G->arcs[m][i];
		if(temp_1!=0)
			G->arcnum--;
		G->arcs[m][i]=G->arcs[n][i];
		G->arcs[n][i]=temp_1;

		VerTexType temp_2=G->arcs[i][m];
		if(temp_2!=0)
			G->arcnum--;
		G->arcs[i][m]=G->arcs[i][n];
		G->arcs[i][n]=temp_2;
	}

	G->vexnum--;
	return OK;
}

int InsertArc(AMGraph*G, VerTexType v, VerTexType w)				 //增加一条边<v, w>
{
	int m=LocateVex(*G, v);
	int n=LocateVex(*G, w);
	if(m<0||n<0)
		return ERROR;
	if(m==n)
		return ERROR;
	if(G->arcs[m][n])
		return ERROR;

	G->arcs[m][n]=1;
	G->arcs[n][m]=0;
	G->arcnum++;
	return OK;
}

int DeleteArc(AMGraph*G, VerTexType v, VerTexType w)				 //删除一条边<v, w>
{
	int m=LocateVex(*G, v);
	int n=LocateVex(*G, w);
	if(m<0||n<0)
		return ERROR;
	if(m==n)
		return ERROR;
	if(!G->arcs[m][n])
		return ERROR;

	G->arcs[m][n]=G->arcs[n][m]=0;
	G->arcnum--;
	return OK;
}

void main()
{
	printf("请创建一个有向图：\n");
	AMGraph G;
	CreateUDN(&G);
	printf("创建成功！\n");
	printf("\n");
	printf("打印该有向图：\n");
	for(int i=0; i<G.vexnum; i++)
	{
		for(int j=0; j<G.vexnum; j++)
			printf("%3d", G.arcs[i][j]);
		printf("\n");
	}

	char c=getchar();
	printf("添加一个新顶点，请输入要添加的新顶点：");
	VerTexType v;
	scanf("%c", &v);
	InsertVex(&G, v);
	printf("添加成功！打印更新后的有向图：\n");
	for(int i=0; i<G.vexnum; i++)
	{
		for(int j=0; j<G.vexnum; j++)
			printf("%3d", G.arcs[i][j]);
		printf("\n");
	}

	c=getchar();
	printf("删除一个顶点，请输入要删除的顶点：");
	scanf("%c", &v);
	DeleteVex(&G, v);
	printf("删除成功！打印更新后的有向图：\n");
	for(int i=0; i<G.vexnum; i++)
	{
		for(int j=0; j<G.vexnum; j++)
			printf("%3d", G.arcs[i][j]);
		printf("\n");
	}

	c=getchar();
	printf("添加一条边，请输入要添加的边（起点A, 终点B）：");
	VerTexType v1, w1;
	scanf("%c, %c", &v1, &w1);
	InsertArc(&G, v1, w1);
	printf("添加成功！打印更新后的有向图：\n");
	for(int i=0; i<G.vexnum; i++)
	{
		for(int j=0; j<G.vexnum; j++)
			printf("%3d", G.arcs[i][j]);
		printf("\n");
	}

	c=getchar();
	printf("删除一条边，请输入要删除的边（起点A, 终点B）：");
	scanf("%c, %c", &v1, &w1);
	DeleteArc(&G, v1, w1);
	printf("删除成功！打印更新后的有向图：\n");
	for(int i=0; i<G.vexnum; i++)
	{
		for(int j=0; j<G.vexnum; j++)
			printf("%3d", G.arcs[i][j]);
		printf("\n");
	}
}

/*
	以邻接矩阵作为储存结构，实现以下图的基本操作：
	1 增加一个新顶点v，InsertVex(G, v)；
	2 删除顶点v及其相关的边，DeleteVex(G, v)；
	3 增加一条边<v, w>，InsertArc(G, v, w)；
	4 删除一条边<v, w>，DeleteArc(G, v, w)；
*/
