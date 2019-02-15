#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>
#define MaxInt 32767                                                //表示最大值，即无限符
#define MVNum 100                                                   //最大顶点数
#define MAX 100
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

/*采用邻接矩阵表示法创建有向网*/
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
	printf("请输出有向网的总顶点数：");
	scanf("%d", &(G->vexnum));
	printf("请输出有向网的总边数：");
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
        G->arcs[j][i]=MaxInt;                                        //置<v1,v2>的对称边<v2,v1>的权值为w

    }
    return OK;
}

bool S[MVNum];                                            	         //记录源点v0到终点vi是否已被确定最短路径长度，true表示确定，false表示尚未确定
VerTexType Path[MVNum];                                     	     //记录源点v0到终点vi的当前最短路径上vi的直接前驱顶点序号，其初值为：如果v0到vi有弧，则Path[i]为v0，否则为-1
ArcType D[MVNum];                                          		     //记录从源点v0到终点vi的当前最短路径长度，其初值为：如果从v0到vi有弧，则D[i]为弧上的权值，否则为∞

/*迪杰斯特拉算法*/
void ShortestPath_DIJ(AMGraph G, int v0)                       		 //用Dijkstra算法求有向网G的v0顶点到其余顶点的最短路径
{
    int n=G.vexnum;                                           		 //n为G中顶点的个数
    for(int v=0;v<n;++v)                                     		 //n个顶点依次初始化
    {
        S[v]=false;                                            		 //S初始为空集
        D[v]=G.arcs[v0][v];                                    		 //将v0到各个终点的最短路径长度初始化为狐上的权值
        if(D[v]<MaxInt)                                        		 //如果v0到v之间有弧，则将v的前驱置为v0
            Path[v]=v0;
        else
            Path[v]=-1;                                        		 //如果v0到v之间无弧，则将v的前驱置为-1
    }
    S[v0]=true;                                                		 //将v0加入S
    D[v0]=0;                                                   		 //源点到源点的距离为0

    for(int i=1;i<n;++i)                            				 //初始化结束，开始主循环，每次求得v0到某个顶点v的最短路径，将v加入S集
    { 																 //对其余n-1个顶点，依次进行计算
    	int v;
        ArcType min=MaxInt;
        for(int w=0;w<n;++w)
			if(!S[w]&&D[w]<=min)                                	 //选择一条当前的最短路径，终点为v
			{
				v=w;                                       			 //将v加入S
				min=D[w];
			}

        S[v]=true;                                              	 //更新从v0出发到集合V-S上所有顶点的最短路径长度
        for(int w=0;w<n;++w)
            if(!S[w]&&(D[v]+G.arcs[v][w]<D[w]))
            {
                D[w]=D[v]+G.arcs[v][w];                         	 //更新D[w]
                Path[w]=v;                                      	 //更新w的前驱为v
            }
    }
}

void main()
{
	printf("请创建一个有向网：\n");
	AMGraph G;
	CreateUDN(&G);
	printf("创建成功！\n");

	printf("请输入一个顶点下标，计算该顶点到其他顶点的最短路径距离：");
	int v;
	scanf("%d", &v);
	ShortestPath_DIJ(G, v);
	for(int i=0; i<G.vexnum; i++)
		printf("%c顶点到%c顶点的最短距离为%d\n", G.vexs[v], G.vexs[i], D[i]);


	printf("\n");
	printf("打印该有向网：\n");
	for(int i=0; i<G.vexnum; i++)
	{
		for(int j=0; j<G.vexnum; j++)
			printf("%8d", G.arcs[i][j]);
		printf("\n");
	}
}


