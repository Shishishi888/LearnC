#include <stdio.h>

/*弗洛伊德算法*/
void ShortestPath_Floyd(AMGraph G)
{ //用Floyd算法求有向网G中各对定点i和j之间的最短路径
	for(int i=0; i<G.vexnum; ++i)					//各对结点之间初始已知路径及距离
		for(int j=0; j<G.vexnum; ++j)
		{
			D[i][j]=G.arc[i][j];
			if(D[i][j]<MaxInt&&!i=j)
				Path[i][j]=i;						//如果i和j之间有弧，则将j的前驱置为i
			else
				Path[i][j]=-1;						//如果i和j之间无弧，则将j的前驱置为-1
		}

	for(int k=0; k<G.vexnum; ++k)
		for(int i=0; i<G.vexnum; ++i)
			for(int j=0; j<G.vexnum; ++j)
				if(D[i][k]+D[k][j]<D[i][j])			//从i经k到j的一条路径更短
				{
					D[i][j]=D[i][k]+D[k][j];		//更新D[i][j]
					Path[i][j]=Path[k][j];			//更新j的前驱为k
				}
}

void main(){}
