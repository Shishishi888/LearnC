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
        G->arcs[i][j]=w;                                             //��(v1,v2)��Ȩֵ��Ϊw
        G->arcs[j][i]=G->arcs[i][j];                                 //��(v1,v2)�ĶԳƱߣ�v2,v1����ȨֵΪw
    }
    return OK;
}

/*����ķ�㷨������С������*/
typedef struct
{
    VerTexType adjvex;                                                        //��С����U�еĶ���
    ArcType lowcost;                                                          //��С���ϵ�Ȩֵ
}Closedge[MVNum];                                		                      //��������������Closedge closedge[MVNum]

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

void MiniSpanTree_Prim(AMGraph G, VerTexType u)              				  //������G���ڽӾ�����ʽ���棬�Ӷ���u��������G����С������T�����T�ĸ�����
{
    int k=LocateVex(G, u);                                                    //kΪ����u���±�
    for(int j=0;j<G.vexnum;++j)                                               //��V-U��ÿһ������vj����ʼ��closedge[j]
        if(j!=k)
        {
            closedge[j].adjvex=u;
            closedge[j].lowcost=G.arcs[k][j];
        }
    closedge[k].lowcost=0;                                                    //��ʼ����U={u}
    for(int i=1;i<G.vexnum;++i)                                               //ѡ������n-1�����㣬����n-1���ߣ�n=G.vexnum��
    {
        k=Min(closedge, G.vexnum);                                            //���T����һ����㣺��k�����㣬closedge[k]�д��е�ǰ��С��
        VerTexType u0=closedge[k].adjvex;                                     //u0Ϊ��С�ߵ�һ�����㣬u0����U
        VerTexType v0=G.vexs[k];                                              //v0Ϊ��С�ߵ���һ�����㣬v0����V-U
        printf("%c %c  ",u0, v0);
        closedge[k].lowcost=0;                                                //��k�����㲢��U��
        for(int j=0;j<G.vexnum;++j)
        {
            if(G.arcs[k][j]<closedge[j].lowcost)                              //�¶��㲢��U������ѡ����С��
            {
                closedge[j].adjvex=G.vexs[k];
                closedge[j].lowcost=G.arcs[k][j];
            }
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
	MiniSpanTree_Prim(G, v);
}
