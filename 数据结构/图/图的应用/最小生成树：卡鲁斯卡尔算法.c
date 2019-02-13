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
    int vexnum, arcnum;                                             //图的当前顶点数和边数
}AMGraph;

typedef struct
{
    VerTexType Head;                                         	    //边的始点
    VerTexType Tail;                                          	    //边的终点
    ArcType lowcost;                                         	    //边上的权值
}Edge[MVNum];													 	//数组长度为arcnum

Edge edge;

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
        G->arcs[i][j]=w;                                             //边<v1,v2>的权值置为w
        G->arcs[j][i]=G->arcs[i][j];                                 //置<v1,v2>的对称边<v2,v1>的权值为w

		edge[k].Head=v1;
		edge[k].Tail=v2;
		edge[k].lowcost;
    }
    return OK;
}

/*克鲁斯卡尔算法*/
void Sort(Edge egde, int arcnum)
{
    int temp;
    for(int i=0; i<arcnum-1; i++)
        for(int j=arcnum-1; j>=i+1; j--)
            if(edge[j].lowcost<edge[j-1].lowcost)
            {
                temp=edge[j].lowcost;
                edge[j].lowcost=edge[j-1].lowcost;
                edge[j-1].lowcost=temp;
            }
}

int Vexset[MVNum];                                             //辅助数组

void MiniSpanTree_Kruskal(AMGraph G)              			   //无向图G以邻接矩阵形式储存，构造G的最小生成树T，输出T的各条边
{
    Sort(edge, G.arcnum);									   //将数组Edge中的元素按权值从小到大排序
    for(int i=0;i<G.vexnum;++i)                                //辅助数组，表示各顶点自成一个连通分量
        Vexset[i]=i;
    for(int i=0;i<G.arcnum;++i)                                //依次查看数组中Edge中的边
    {
        int v1=LocateVex(G, edge[i].Head);                     //v1为边的始点Head的下标
        int v2=LocateVex(G, edge[i].Tail);                     //v2为边的终点Tail的下标
        int vs1=Vexset[v1];                                    //获取边Edge[i]的始点所在的连通分量vs1
        int vs2=Vexset[v2];                                    //获取边Edge[i]的终点所在的连通分量vs2
        if(vs1!=vs2)
        {
            printf("%c %c  ", edge[i].Head, edge[i].Tail);     //输出此边
            for(int j=0;j<G.vexnum;++j)                        //合并vs1和vs2两个分量，即两个集合统一编号
                if(Vexset[j]==vs2)                             //集合编号为vs2的都改为vs1
                    Vexset[j]=vs1;
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
	MiniSpanTree_Kruskal(G);
}
