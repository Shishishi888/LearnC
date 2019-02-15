#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>
#define MaxInt 32767                                                //表示最大值，即无限符
#define MVNum 100                                                   //最大顶点数
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
        G->arcs[j][i]=G->arcs[i][j];                                 //置(v1,v2)的对称边（v2,v1）的权值为w
    }
    return OK;
}

/*普里姆算法构造最小生成树*/
typedef struct
{
    VerTexType adjvex;                                                        //最小边在U中的顶点
    ArcType lowcost;                                                          //最小边上的权值
}Closedge[MVNum];                                		                      //在主函数中声明Closedge closedge[MVNum]

Closedge closedge;

int Min(Closedge closedge, int vexnum)
{
	int j;
    int min=MaxInt;
    for(int i=0;i<vexnum;i++)
    {
        if(min>closedge[i].lowcost&&closedge[i].lowcost!=0)
        {
            min=closedge[i].lowcost;
			j=i;
        }
    }
    return j;
}

void MiniSpanTree_Prim(AMGraph G, VerTexType u)              				  //无向网G以邻接矩阵形式储存，从顶点u出发构造G的最小生成树T，输出T的各条边
{
    int k=LocateVex(G, u);                                                    //k为顶点u的下标
    for(int j=0;j<G.vexnum;++j)                                               //对V-U的每一个顶点vj，初始化closedge[j]
        if(j!=k)
        {
            closedge[j].adjvex=u;
            closedge[j].lowcost=G.arcs[k][j];
        }
    closedge[k].lowcost=0;                                                    //初始化，U={u}
    for(int i=1;i<G.vexnum;++i)                                               //选择其余n-1个顶点，生成n-1条边（n=G.vexnum）
    {
        k=Min(closedge, G.vexnum);                                            //求出T的下一个结点：第k个顶点，closedge[k]中存有当前最小边
        VerTexType u0=closedge[k].adjvex;                                     //u0为最小边的一个顶点，u0属于U
        VerTexType v0=G.vexs[k];                                              //v0为最小边的另一个顶点，v0属于V-U
        printf("%c %c  ",u0, v0);
        closedge[k].lowcost=0;                                                //第k个顶点并入U集
        for(int j=0;j<G.vexnum;++j)
        {
            if(G.arcs[k][j]<closedge[j].lowcost)                              //新顶点并入U后重新选择最小边
            {
                closedge[j].adjvex=G.vexs[k];
                closedge[j].lowcost=G.arcs[k][j];
            }
        }
    }
}

void main()
{
	printf("请创建一个无向网：\n");
	AMGraph G;
	CreateUDN(&G);
	printf("创建成功！\n");
	getchar();

	printf("请输入一个顶点以开始构造最小生成树：");
	VerTexType v;
	scanf("%c", &v);
	printf("打印该最小生成树：\n");
	MiniSpanTree_Prim(G, v);
}
