#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdbool.h>
#define MVNum 100                            //��󶥵���
#define MAX 100
#define OK 1
#define ERROR 0
typedef char OtherInfo[20];					 //����������¼��������Ȩֵ
typedef char VerTexType; 					 //�������������
typedef int ArcType;                         //����ߵ�Ȩֵ����Ϊ����

typedef struct ArcNode                       //�߽��
{
    int adjvex;                              //�ñ���ָ��Ķ����λ��
    struct ArcNode *nextarc;                 //ָ����һ���ߵ�ָ��
    OtherInfo info;                          //�ͱ���ص���Ϣ
}ArcNode;

typedef struct VNode                         //������Ϣ
{
    VerTexType data;
    ArcNode *firstarc;                       //ָ���һ�������ö���ıߵ�ָ��
}VNode, AdjList[MVNum];                      //AdjList��ʾ�ڽӱ�����

typedef struct                               //�ڽӱ�
{
    AdjList vertices;
    int vexnum, arcnum;                      //ͼ�ĵ�ǰ�������ͱ���
}ALGraph;

int LocateVex(ALGraph G, VerTexType vex)
{
    int i;
    for(i=0; i<G.vexnum; i++)
        if(vex==G.vertices[i].data)
            return i;
    return -1;
}

int CreateUDG(ALGraph *G)											 //�����ڽӱ��ʾ����������ͼ
{
	printf("���������ͼ���ܶ�������");     					     //�����ܶ��������ܱ���
	scanf("%d", &(G->vexnum));
	printf("���������ͼ���ܱ�����");
    scanf("%d", &(G->arcnum));
	printf("������������������Ϣ��\n");

    for(int i=0; i<G->vexnum; i++)
    {
    	//fflush(stdin);                                             //ˢ�»�����
    	char c=getchar();											 //�Ե��������еġ��س���
		printf("�������%d���������Ϣ��", i+1);					 //���붥���ֵ
		scanf("%c", &(G->vertices[i].data));                         //�������붥�����Ϣ
        G->vertices[i].firstarc=NULL;        						 //��ʼ����ͷ����ָ����ΪNULL
    }

    VerTexType v1, v2;
    printf("����������ÿ���������Ķ��㣨���A, �յ�B����\n");
    for(int k=0; k<G->arcnum; k++)           //������ߣ������ڽӱ�
    {
    	//fflush(stdin);				     //ˢ�»�����
    	char c=getchar();                    //�Ե��������еġ��س���
    	printf("�������%d���������Ķ��㣺", k+1);
        scanf("%c, %c", &v1, &v2);           //����һ������������������
        int i=LocateVex(*G, v1);             //ȷ��v1��v2��G�е�λ�ã���������G->vertices�е����
	    int j=LocateVex(*G, v2);
        ArcNode *p1=(ArcNode *)malloc(sizeof(ArcNode));              //�����µıߵĽ��*p1
        p1->adjvex=j;                                                //�ڽӵ����Ϊj
        p1->nextarc=G->vertices[i].firstarc;                         //���½��*p1���붥��vi�ı߱�ͷ��
        G->vertices[i].firstarc=p1;
    }
}

int InsertVex(ALGraph *G, VerTexType v)								 //����һ���¶���v
{
	if(G->vexnum+1>MVNum)
		return ERROR;
	G->vertices[G->vexnum].data=v;
	G->vertices[G->vexnum].firstarc=NULL;
	G->vexnum++;
	return OK;
}


int DeleteVex(ALGraph *G, VerTexType v)								 //ɾ������v������صı�
{
	int n=LocateVex(*G, v);
	if(n<0)
		return ERROR;
	ArcNode *pointer=G->vertices[n].firstarc;
	while(pointer)
	{
		G->arcnum--;
		pointer=pointer->nextarc;
	}
	for(int i=n; i<G->vexnum; i++)
		G->vertices[i]=G->vertices[i+1];
	G->vexnum--;
	for(int i=0; i<G->vexnum; i++)									 //����ͼ��ɾ���붥��v��صı�
	{
		ArcNode *p=G->vertices[i].firstarc;						     //pָ��ǰ�Ľ��
		ArcNode *q=NULL;											 //qָ��ǰ����ǰ��
		if(!p)
			continue;
		if(p->adjvex==n)
		{
			G->vertices[i].firstarc=p->nextarc;
			G->arcnum--;
			continue;
		}
		else
		{
			p=p->nextarc;
			q=G->vertices[i].firstarc;

			while(p)
			{
				if(p->adjvex==n)
				{
					q->nextarc=p->nextarc;
					G->arcnum--;
					break;
				}
				p=p->nextarc;
				q=q->nextarc;
			}
		}
	}
}

int InsertArc(ALGraph*G, VerTexType v, VerTexType w)				 //����һ����<v, w>
{
	int i=LocateVex(*G, v);
	int j=LocateVex(*G, w);
	if(i<0)
		return ERROR;
	if(j<0)
		return ERROR;
	ArcNode *p=(ArcNode *)malloc(sizeof(ArcNode));
	p->adjvex=j;
	p->nextarc=G->vertices[i].firstarc;
	G->vertices[i].firstarc=p;
	G->arcnum++;
	return OK;
}

int DeleteArc(ALGraph *G, VerTexType v, VerTexType w)				 //ɾ��һ����<v, w>
{
	int i=LocateVex(*G, v);
	int j=LocateVex(*G, w);
	if(i<0)
		return ERROR;
	if(j<0)
		return ERROR;

	ArcNode *p=G->vertices[i].firstarc;								 //pָ��ǰ�Ľ��
	ArcNode *q=NULL;							   		 	 		 //qָ��ǰ����ǰ��
	//if(!p)														 //�������pΪ�յ����
	if(p->adjvex==j)
	{
		G->vertices[i].firstarc=p->nextarc;
		G->arcnum--;
	}
	else
	{
		p=p->nextarc;
		q=G->vertices[i].firstarc;

		while(p)
		{
			if(p->adjvex==j)
			{
				q->nextarc=p->nextarc;
				G->arcnum--;
				break;
			}
			p=p->nextarc;
			q=q->nextarc;
		}
	}
	return OK;
}

void main()
{
	printf("�봴��һ������ͼ��\n");
	ALGraph G;
	CreateUDG(&G);
	printf("�����ɹ���\n");
	printf("\n");
	printf("��ӡ������ͼ��\n");
	int i=0;
	while(i<G.vexnum)
	{
		printf("%c-->", G.vertices[i].data);
		ArcNode *p=G.vertices[i].firstarc;

		while(p)
		{
			printf("%c-->", G.vertices[p->adjvex].data);
			p=p->nextarc;
		}

		i++;
		printf("\n");
	}


	char c=getchar();
	printf("���һ���¶��㣬������Ҫ��ӵ��¶��㣺");
	VerTexType v;
	scanf("%c", &v);
	InsertVex(&G, v);
	printf("��ӳɹ�����ӡ���º������ͼ��\n");
	i=0;
	while(i<G.vexnum)
	{
		printf("%c-->", G.vertices[i].data);
		ArcNode *p=G.vertices[i].firstarc;

		while(p)
		{
			printf("%c-->", G.vertices[p->adjvex].data);
			p=p->nextarc;
		}

		i++;
		printf("\n");
	}

	c=getchar();
	printf("ɾ��һ�����㣬������Ҫɾ���Ķ��㣺");
	scanf("%c", &v);
	DeleteVex(&G, v);
	printf("ɾ���ɹ�����ӡ���º������ͼ��\n");
	i=0;
	while(i<G.vexnum)
	{
		printf("%c-->", G.vertices[i].data);
		ArcNode *p=G.vertices[i].firstarc;

		while(p)
		{
			printf("%c-->", G.vertices[p->adjvex].data);
			p=p->nextarc;
		}

		i++;
		printf("\n");
	}

	c=getchar();
	printf("���һ���ߣ�������Ҫ��ӵıߣ����A, �յ�B����");
	VerTexType v1, w1;
	scanf("%c, %c", &v1, &w1);
	InsertArc(&G, v1, w1);
	printf("��ӳɹ�����ӡ���º������ͼ��\n");
	i=0;
	while(i<G.vexnum)
	{
		printf("%c-->", G.vertices[i].data);
		ArcNode *p=G.vertices[i].firstarc;

		while(p)
		{
			printf("%c-->", G.vertices[p->adjvex].data);
			p=p->nextarc;
		}

		i++;
		printf("\n");
	}

	c=getchar();
	printf("ɾ��һ���ߣ�������Ҫɾ���ıߣ����A, �յ�B����");
	scanf("%c, %c", &v1, &w1);
	DeleteArc(&G, v1, w1);
	printf("ɾ���ɹ�����ӡ���º������ͼ��\n");
	i=0;
	while(i<G.vexnum)
	{
		printf("%c-->", G.vertices[i].data);
		ArcNode *p=G.vertices[i].firstarc;

		while(p)
		{
			printf("%c-->", G.vertices[p->adjvex].data);
			p=p->nextarc;
		}

		i++;
		printf("\n");
	}

}

/*
	���ڽӱ���Ϊ����ṹ��ʵ������ͼ�Ļ���������
	1 ����һ���¶���v��InsertVex(G, v)��
	2 ɾ������v������صıߣ�DeleteVex(G, v)��
	3 ����һ����<v, w>��InsertArc(G, v, w)��
	4 ɾ��һ����<v, w>��DeleteArc(G, v, w)��
*/
