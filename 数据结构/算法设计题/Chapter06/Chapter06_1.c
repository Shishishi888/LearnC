#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>
#define MVNum 100                                                    //��󶥵���
#define MAX 100
#define OK 1
#define ERROR 0
typedef char VerTexType;                                             //���趥�����������Ϊ�ַ���
typedef int ArcType;                                                 //����ߵ�Ȩֵ����Ϊ����

typedef struct
{
    VerTexType vexs[MVNum];                                          //��������趥�����������Ϊ�ַ���
    ArcType arcs[MVNum][MVNum];                                      //�ڽӾ���,����ߵ�Ȩֵ����Ϊ����
    int vexnum, arcnum;                                              //ͼ�ĵ�ǰ�������ͱ���
}AMGraph;


int LocateVex(AMGraph G, VerTexType vex)                             //ȷ��vex��G�е�λ�ã�������������±�
{
    int i;
    for(i=0; i<G.vexnum; i++)
        if(vex==G.vexs[i])
            return i;
    return -1;
}

int CreateUDN(AMGraph *G)											 //�����ڽӾ����ʾ����������ͼ
{
	printf("���������ͼ���ܶ�������");
	scanf("%d", &(G->vexnum));
	printf("���������ͼ���ܱ�����");
    scanf("%d", &(G->arcnum));

    printf("������������������Ϣ��\n");
    for(int i=0; i<G->vexnum; i++)
	{
		char c=getchar();											 //�Ե��������еġ��س���
		printf("�������%d���������Ϣ��", i+1);
		scanf("%c", &(G->vexs[i]));                                  //�������붥�����Ϣ
	}

    for(int i=0; i<G->vexnum; i++)                                   //��ʼ���ڽӾ���
        for(int j=0; j<G->vexnum; j++)
            G->arcs[i][j]=0;

    VerTexType v1, v2;
	printf("����������ÿ���������Ķ��㣨���A, �յ�B����\n");
    for(int k=0; k<G->arcnum; k++)                                   //�����ڽӾ���
    {
		char c=getchar();											 //�Ե��������еġ��س���
    	printf("�������%d���������Ķ���: ", k+1);
        scanf("%c, %c", &v1, &v2);                       		     //����һ���������Ķ���
        int i=LocateVex(*G, v1);                                     //ȷ��v1��v2��G�е�λ�ã�������������±�
        int j=LocateVex(*G, v2);
        G->arcs[i][j]=1;                                             //��<v1,v2>��Ȩֵ��Ϊ1
        G->arcs[j][i]=0;                                			 //��<v1,v2>�ĶԳƱ�<v2,v1>��ȨֵΪ1

    }
    return OK;
}

int InsertVex(AMGraph *G, VerTexType v)								 //����һ���¶���v
{
	if(G->vexnum+1>MVNum)
		return ERROR;
	G->vexs[G->vexnum]=v;
	for(int i=0; i<G->vexnum; i++)
		G->arcs[G->vexnum][i]=G->arcs[i][G->vexnum]=0;
	G->vexnum++;
	return OK;
}

int DeleteVex(AMGraph *G, VerTexType v)								 //ɾ������v������صı�
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

int InsertArc(AMGraph*G, VerTexType v, VerTexType w)				 //����һ����<v, w>
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

int DeleteArc(AMGraph*G, VerTexType v, VerTexType w)				 //ɾ��һ����<v, w>
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
	printf("�봴��һ������ͼ��\n");
	AMGraph G;
	CreateUDN(&G);
	printf("�����ɹ���\n");
	printf("\n");
	printf("��ӡ������ͼ��\n");
	for(int i=0; i<G.vexnum; i++)
	{
		for(int j=0; j<G.vexnum; j++)
			printf("%3d", G.arcs[i][j]);
		printf("\n");
	}

	char c=getchar();
	printf("���һ���¶��㣬������Ҫ��ӵ��¶��㣺");
	VerTexType v;
	scanf("%c", &v);
	InsertVex(&G, v);
	printf("��ӳɹ�����ӡ���º������ͼ��\n");
	for(int i=0; i<G.vexnum; i++)
	{
		for(int j=0; j<G.vexnum; j++)
			printf("%3d", G.arcs[i][j]);
		printf("\n");
	}

	c=getchar();
	printf("ɾ��һ�����㣬������Ҫɾ���Ķ��㣺");
	scanf("%c", &v);
	DeleteVex(&G, v);
	printf("ɾ���ɹ�����ӡ���º������ͼ��\n");
	for(int i=0; i<G.vexnum; i++)
	{
		for(int j=0; j<G.vexnum; j++)
			printf("%3d", G.arcs[i][j]);
		printf("\n");
	}

	c=getchar();
	printf("���һ���ߣ�������Ҫ��ӵıߣ����A, �յ�B����");
	VerTexType v1, w1;
	scanf("%c, %c", &v1, &w1);
	InsertArc(&G, v1, w1);
	printf("��ӳɹ�����ӡ���º������ͼ��\n");
	for(int i=0; i<G.vexnum; i++)
	{
		for(int j=0; j<G.vexnum; j++)
			printf("%3d", G.arcs[i][j]);
		printf("\n");
	}

	c=getchar();
	printf("ɾ��һ���ߣ�������Ҫɾ���ıߣ����A, �յ�B����");
	scanf("%c, %c", &v1, &w1);
	DeleteArc(&G, v1, w1);
	printf("ɾ���ɹ�����ӡ���º������ͼ��\n");
	for(int i=0; i<G.vexnum; i++)
	{
		for(int j=0; j<G.vexnum; j++)
			printf("%3d", G.arcs[i][j]);
		printf("\n");
	}
}

/*
	���ڽӾ�����Ϊ����ṹ��ʵ������ͼ�Ļ���������
	1 ����һ���¶���v��InsertVex(G, v)��
	2 ɾ������v������صıߣ�DeleteVex(G, v)��
	3 ����һ����<v, w>��InsertArc(G, v, w)��
	4 ɾ��һ����<v, w>��DeleteArc(G, v, w)��
*/
