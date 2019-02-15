#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>
#define MaxInt 32767                                                //��ʾ���ֵ�������޷�
#define MVNum 100                                                   //��󶥵���
#define MAX 100
#define OK 1
#define ERROR 0
typedef char VerTexType;                                            //���趥�����������Ϊ�ַ���
typedef int ArcType;                                                //����ߵ�Ȩֵ����Ϊ����

typedef struct
{
    VerTexType vexs[MVNum];                                         //��������趥�����������Ϊ�ַ���
    ArcType arcs[MVNum][MVNum];                                     //�ڽӾ���,����ߵ�Ȩֵ����Ϊ����
    int vexnum, arcnum;                                             //���ĵ�ǰ�������ͱ���
}AMGraph;

/*�����ڽӾ����ʾ������������*/
int LocateVex(AMGraph G, VerTexType vex)                            //ȷ��vex��G�е�λ�ã�������������±�
{
    int i;
    for(i=0; i<G.vexnum; i++)
        if(vex==G.vexs[i])
            return i;
    return -1;
}

int CreateUDN(AMGraph *G)
{
	printf("��������������ܶ�������");
	scanf("%d", &(G->vexnum));
	printf("��������������ܱ�����");
    scanf("%d", &(G->arcnum));

    printf("������������������Ϣ��\n");
    for(int i=0; i<G->vexnum; i++)
	{
		char c=getchar();											 //�Ե��������еġ��س���
		printf("�������%d���������Ϣ��", i+1);
		scanf("%c", &(G->vexs[i]));                                  //�������붥�����Ϣ
	}

    for(int i=0; i<G->vexnum; i++)                                   //��ʼ���ڽӾ��󣬱ߵ�Ȩֵ����Ϊ���ֵMaxInt
        for(int j=0; j<G->vexnum; j++)
            G->arcs[i][j]=MaxInt;

    VerTexType v1, v2;
    ArcType w;
	printf("����������ÿ���������Ķ��㼰Ȩֵ������A, ����B, Ȩֵ����\n");
    for(int k=0; k<G->arcnum; k++)                                   //�����ڽӾ���
    {
		char c=getchar();											 //�Ե��������еġ��س���
    	printf("�������%d���������Ķ��㼰Ȩֵ��", k+1);
        scanf("%c, %c, %d", &v1, &v2, &w);                           //����һ���������Ķ��㼰Ȩֵ
        int i=LocateVex(*G, v1);                                     //ȷ��v1��v2��G�е�λ�ã�������������±�
        int j=LocateVex(*G, v2);
        G->arcs[i][j]=w;                                             //��<v1,v2>��Ȩֵ��Ϊw
        G->arcs[j][i]=MaxInt;                                        //��<v1,v2>�ĶԳƱ�<v2,v1>��ȨֵΪw

    }
    return OK;
}

bool S[MVNum];                                            	         //��¼Դ��v0���յ�vi�Ƿ��ѱ�ȷ�����·�����ȣ�true��ʾȷ����false��ʾ��δȷ��
VerTexType Path[MVNum];                                     	     //��¼Դ��v0���յ�vi�ĵ�ǰ���·����vi��ֱ��ǰ��������ţ����ֵΪ�����v0��vi�л�����Path[i]Ϊv0������Ϊ-1
ArcType D[MVNum];                                          		     //��¼��Դ��v0���յ�vi�ĵ�ǰ���·�����ȣ����ֵΪ�������v0��vi�л�����D[i]Ϊ���ϵ�Ȩֵ������Ϊ��

/*�Ͻ�˹�����㷨*/
void ShortestPath_DIJ(AMGraph G, int v0)                       		 //��Dijkstra�㷨��������G��v0���㵽���ඥ������·��
{
    int n=G.vexnum;                                           		 //nΪG�ж���ĸ���
    for(int v=0;v<n;++v)                                     		 //n���������γ�ʼ��
    {
        S[v]=false;                                            		 //S��ʼΪ�ռ�
        D[v]=G.arcs[v0][v];                                    		 //��v0�������յ�����·�����ȳ�ʼ��Ϊ���ϵ�Ȩֵ
        if(D[v]<MaxInt)                                        		 //���v0��v֮���л�����v��ǰ����Ϊv0
            Path[v]=v0;
        else
            Path[v]=-1;                                        		 //���v0��v֮���޻�����v��ǰ����Ϊ-1
    }
    S[v0]=true;                                                		 //��v0����S
    D[v0]=0;                                                   		 //Դ�㵽Դ��ľ���Ϊ0

    for(int i=1;i<n;++i)                            				 //��ʼ����������ʼ��ѭ����ÿ�����v0��ĳ������v�����·������v����S��
    { 																 //������n-1�����㣬���ν��м���
    	int v;
        ArcType min=MaxInt;
        for(int w=0;w<n;++w)
			if(!S[w]&&D[w]<=min)                                	 //ѡ��һ����ǰ�����·�����յ�Ϊv
			{
				v=w;                                       			 //��v����S
				min=D[w];
			}

        S[v]=true;                                              	 //���´�v0����������V-S�����ж�������·������
        for(int w=0;w<n;++w)
            if(!S[w]&&(D[v]+G.arcs[v][w]<D[w]))
            {
                D[w]=D[v]+G.arcs[v][w];                         	 //����D[w]
                Path[w]=v;                                      	 //����w��ǰ��Ϊv
            }
    }
}

void main()
{
	printf("�봴��һ����������\n");
	AMGraph G;
	CreateUDN(&G);
	printf("�����ɹ���\n");

	printf("������һ�������±꣬����ö��㵽������������·�����룺");
	int v;
	scanf("%d", &v);
	ShortestPath_DIJ(G, v);
	for(int i=0; i<G.vexnum; i++)
		printf("%c���㵽%c�������̾���Ϊ%d\n", G.vexs[v], G.vexs[i], D[i]);


	printf("\n");
	printf("��ӡ����������\n");
	for(int i=0; i<G.vexnum; i++)
	{
		for(int j=0; j<G.vexnum; j++)
			printf("%8d", G.arcs[i][j]);
		printf("\n");
	}
}


