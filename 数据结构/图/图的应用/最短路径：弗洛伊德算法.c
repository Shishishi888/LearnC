#include <stdio.h>

/*���������㷨*/
void ShortestPath_Floyd(AMGraph G)
{ //��Floyd�㷨��������G�и��Զ���i��j֮������·��
	for(int i=0; i<G.vexnum; ++i)					//���Խ��֮���ʼ��֪·��������
		for(int j=0; j<G.vexnum; ++j)
		{
			D[i][j]=G.arc[i][j];
			if(D[i][j]<MaxInt&&!i=j)
				Path[i][j]=i;						//���i��j֮���л�����j��ǰ����Ϊi
			else
				Path[i][j]=-1;						//���i��j֮���޻�����j��ǰ����Ϊ-1
		}

	for(int k=0; k<G.vexnum; ++k)
		for(int i=0; i<G.vexnum; ++i)
			for(int j=0; j<G.vexnum; ++j)
				if(D[i][k]+D[k][j]<D[i][j])			//��i��k��j��һ��·������
				{
					D[i][j]=D[i][k]+D[k][j];		//����D[i][j]
					Path[i][j]=Path[k][j];			//����j��ǰ��Ϊk
				}
}

void main(){}
