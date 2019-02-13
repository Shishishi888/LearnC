#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>
#define MaxInt 32767                                                //��ʾ���ֵ�������޷�
#define MVNum 100                                                   //��󶥵���
#define OK 1
#define ERROR 0
typedef char VerTexType;                                            //���趥�����������Ϊ�ַ���
typedef int ArcType;                                                //����ߵ�Ȩֵ����Ϊ����

typedef struct
{
    VerTexType vexs[MVNum];                                         //��������趥�����������Ϊ�ַ���
    ArcType arcs[MVNum][MVNum];                                     //�ڽӾ���,����ߵ�Ȩֵ����Ϊ����
    int vexnum, arcnum;                                             //ͼ�ĵ�ǰ�������ͱ���
}AMGraph;

typedef struct
{
    VerTexType Head;                                         	    //�ߵ�ʼ��
    VerTexType Tail;                                          	    //�ߵ��յ�
    ArcType lowcost;                                         	    //���ϵ�Ȩֵ
}Edge[MVNum];													 	//���鳤��Ϊarcnum

Edge edge;

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
        G->arcs[j][i]=G->arcs[i][j];                                 //��<v1,v2>�ĶԳƱ�<v2,v1>��ȨֵΪw

		edge[k].Head=v1;
		edge[k].Tail=v2;
		edge[k].lowcost;
    }
    return OK;
}

/*��³˹�����㷨*/
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

int Vexset[MVNum];                                             //��������

void MiniSpanTree_Kruskal(AMGraph G)              			   //����ͼG���ڽӾ�����ʽ���棬����G����С������T�����T�ĸ�����
{
    Sort(edge, G.arcnum);									   //������Edge�е�Ԫ�ذ�Ȩֵ��С��������
    for(int i=0;i<G.vexnum;++i)                                //�������飬��ʾ�������Գ�һ����ͨ����
        Vexset[i]=i;
    for(int i=0;i<G.arcnum;++i)                                //���β鿴������Edge�еı�
    {
        int v1=LocateVex(G, edge[i].Head);                     //v1Ϊ�ߵ�ʼ��Head���±�
        int v2=LocateVex(G, edge[i].Tail);                     //v2Ϊ�ߵ��յ�Tail���±�
        int vs1=Vexset[v1];                                    //��ȡ��Edge[i]��ʼ�����ڵ���ͨ����vs1
        int vs2=Vexset[v2];                                    //��ȡ��Edge[i]���յ����ڵ���ͨ����vs2
        if(vs1!=vs2)
        {
            printf("%c %c  ", edge[i].Head, edge[i].Tail);     //����˱�
            for(int j=0;j<G.vexnum;++j)                        //�ϲ�vs1��vs2��������������������ͳһ���
                if(Vexset[j]==vs2)                             //���ϱ��Ϊvs2�Ķ���Ϊvs1
                    Vexset[j]=vs1;
        }
    }
}

void main()
{
	printf("�봴��һ����������\n");
	AMGraph G;
	CreateUDN(&G);
	printf("�����ɹ���\n");
	getchar();

	printf("������һ�������Կ�ʼ������С��������");
	VerTexType v;
	scanf("%c", &v);
	printf("��ӡ����С��������\n");
	MiniSpanTree_Kruskal(G);
}
