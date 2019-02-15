#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdbool.h>
#define MVNum 100                            //��󶥵���
#define MAX 100
#define OK 1
#define ERROR 0
typedef char OtherInfo[20]; 			     //����������¼��������Ȩֵ
typedef char VerTexType; 					 //�������������
typedef int ArcType;

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

int CreateUDG(ALGraph *G)	 									     //�����ڽӱ��ʾ����������ͼ
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
    printf("����������ÿ���������Ķ��㣨����A, ����B����\n");
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
        ArcNode *p2=(ArcNode *)malloc(sizeof(ArcNode));              //������һ���ԳƵ��µı߽��*p2
        p2->adjvex=i;                                                //�ڽӵ����Ϊi
        p2->nextarc=G->vertices[j].firstarc;                         //���½��*p2���붥��vi�ı߱�ͷ��
        G->vertices[j].firstarc=p2;
    }
}

int visited[MVNum];													 //���ʱ�����飬���ֵΪfalse

int PathLenK(ALGraph G, int i, int j, int k)						 //���ж��ڽӱ�ʽ���������ͼG�Ķ���i��j�Ƿ���ڳ���Ϊk�ļ�·��
{
	if(i==j&&k==0)
		return 1;													 //�ҵ���һ��·�����ҳ��ȷ���Ҫ��
	else if(k>0)
	{
		visited[i]=true;
		for(ArcNode *p=G.vertices[i].firstarc; p; p=p->nextarc)		 //�ӽ��i��ʼ������pΪi�ı�����ĵ�һ���߽��
		{
			int v=p->adjvex;
			if(!visited[v])											 //vδ�����ʹ�
				if(PathLenK(G, v, j, k-1))
					return 1;										 //�ݹ�����ж�i��j����ʣ��·�����ȼ�1
		}
		visited[i]=false;											 //�������������ʹ��Ľ���������һ��·����
	}
	return 0;														 //δ�ҵ�����Ҫ���·��
}

void main()
{
	printf("�봴��һ������ͼ��\n");
	ALGraph G;
	CreateUDG(&G);
	printf("�����ɹ���\n");
	printf("�����붥��v1�Ͷ���v2���±��Լ�������֮��ľ���k�����ж��ڶ���v1�Ͷ���v2֮���Ƿ����һ������Ϊk�ļ�·����");
	int v1, v2, k;
	scanf("%d, %d, %d", &v1, &v2, &k);
	if(PathLenK(G, v1, v2, k))
		printf("����%c�Ͷ���%c֮����ڳ���Ϊ%d�ļ�·��", G.vertices[v1].data, G.vertices[v2].data, k);
	else
		printf("����%c�Ͷ���%c֮�䲻���ڳ���Ϊ%d�ļ�·��", G.vertices[v1].data, G.vertices[v2].data, k);
}

/*
	�����ڽӱ���ṹ����дһ���㷨���б�����ͼ�������������������֮���Ƿ����һ������Ϊk�ļ�·����
*/
