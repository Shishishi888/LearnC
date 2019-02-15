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

int LocateVex(ALGraph G, VerTexType vex)	 //�����ڽӱ��ʾ����������ͼ
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

bool visited[MVNum];												 //���ʱ������
bool flag=false;													 //��������յ�֮���Ƿ���ͨ·

void PathDFS(ALGraph G, int i, int j)								 //�ж����vi���յ�vj֮���Ƿ���·��
{
    visited[i]=true;
    ArcNode *p=G.vertices[i].firstarc;                   			 //pָ��v�ı�����ĵ�һ���߽��
    while(p!=NULL)                                         			 //�߽��ǿ�
    {
        int w=p->adjvex;                                  			 //��ʾw��v���ڽӵ�
        if(w==j)
		{
			flag=true;
			return;
		}

        if(!visited[w])                                   			 //���wδ���ʣ���ݹ����PathDFS
            PathDFS(G, w, j);
        p=p->nextarc;                                    		     //pָ����һ���߽��
    }
}

/*
int visited[MVNum];													 //���ʱ�����飬���ֵΪfalse
int level=1;														 //�ݹ���еĲ���
int PathDFS(ALGraph G, int i, int j)								 //����������������ж�����ͼG�ж���i������j�Ƿ���·�������򷵻�1�����򷵻�0
{
	if(i==j)
		return 1;													 //�ݹ������������β�����������·��
	else
	{
		visited[i]=true;											 //����i���ʱ�־Ϊtrue
		for(ArcNode *p=G.vertices[i].firstarc; p; p=p->nextarc, level--)
		{
			level++;												 //�ݹ�����1
			int k=p->adjvex;
			if(!visited[k]&&PathDFS(G, k, j))
				return 1;											 //i���εĶ��㵽j��·��
		}
	}
	if(level==1)
		return 0;													 //i��jû��·��
}
*/

void main()
{
	printf("�봴��һ������ͼ��\n");
	ALGraph G;
	CreateUDG(&G);
	printf("�����ɹ���\n");
	printf("����������������±꣬���жϸ���������֮���Ƿ���ͨ·�����A, �յ�B����");
	int v, w;
	scanf("%d, %d", &v, &w);
	PathDFS(G, v, w);
	if(flag)
	//if(PathDFS(G, v, w))
		printf("���%c���յ�%c֮����ͨ·", G.vertices[v].data, G.vertices[w].data);
	else
		printf("���%c���յ�%c֮����ͨ·", G.vertices[v].data, G.vertices[w].data);
}

/*
	�Ի���ͼ�����������������дһ�㷨���б����ڽӱ�ʽ���������ͼ�Ƿ�����ɶ���vi������vj��·����i��=j����
*/
