#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdbool.h>
#define MVNum 100                            //��󶥵���
#define MAXSIZE 100
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


/*�����ڽӱ��ʾ����������ͼ*/
int LocateVex(ALGraph G, VerTexType vex)
{
    int i;
    for(i=0; i<G.vexnum; i++)
        if(vex==G.vertices[i].data)
            return i;
    return -1;
}

int CreateUDG(ALGraph *G)
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

/*��������*/
typedef int SElemType;
typedef struct
{
    SElemType *base;    						    //ջ��ָ��
    SElemType *top;    								//ջ��ָ��
    int stacksize; 		 							//ջ���õ��������
}SqStack;

int InitStack(SqStack *S)							//��ʼ��˳��ջ
{
    S->base=(SElemType *)malloc(sizeof(SElemType)*MAXSIZE);
    if(!(S->base))
        exit(0);
    S->top=S->base;
    S->stacksize=MAXSIZE;
    return OK;
}

int Push(SqStack *S, SElemType e)					//˳��ջ����ջ
{
    if(S->top-S->base==S->stacksize)
        return ERROR;
    *(S->top++)=e;
    return OK;
}

int Pop(SqStack *S, SElemType *e)					//˳��ջ�ĳ�ջ
{
    if(S->top==S->base)
        return ERROR;
    *e=*(--S->top);
    return OK;
}

bool StackEmpty(SqStack S)							//�ж�˳��ջ�Ƿ�Ϊ��
{
    if(S.top==S.base)
        return true;
    else
        return false;
}

int indegree[MVNum];								//��Ÿ���������
SqStack S;											//�ݴ��������Ϊ0�Ķ���
int topo[MVNum];									//��¼�������еĶ������

void FindInDegree(ALGraph G, int indegree[])		//ͳ�Ƹ��������ȵĺ���
{
	ArcNode *p;
	for(int i=0; i<G.vexnum; i++)
		indegree[i]=0;								//��������ȳ�ʼ��Ϊ0

	for(int j=0; j<G.vexnum; j++)
	{
		p=G.vertices[j].firstarc;
		while(p!=NULL)
		{
			indegree[p->adjvex]++;					//��Ӧ������ȼ�1
			p=p->nextarc;
		}
	}
}

int TopologicalSort(ALGraph G, int topo[])
{ //����ͼG�����ڽӱ���ṹ
  //��G�޻�·��������G��һ����������topo[]������OK�����򷵻�ERROR

	FindInDegree(G, indegree);                  //������������ȴ�������indegree��
	InitStack(&S);								//ջS��ʼ��Ϊ��
	for(int i=0; i<G.vexnum; ++i)
		if(!indegree[i])
			Push(&S, i);						//���Ϊ0�Ķ����ջ
	int m=0;									//����������������ʼΪ0
	while(!StackEmpty(S))						//ջS�ǿ�
	{
		int i;
		Pop(&S, &i);						  	//��ջ������vi��ջ
		topo[m]=i;								//��vi������������������topo��
		++m;									//������������
		ArcNode *p=G.vertices[i].firstarc;		//pָ��vi�ĵ�һ���ڽӵ�
		while(p!=NULL)
		{
			int k=p->adjvex;					//vkΪvi���ڽӵ�
			--indegree[k];						//vi��ÿ���ڽӵ����ȼ�1
			if(indegree[k]==0)
				Push(&S, k);					//�����Ϊ0����ջ
			p=p->nextarc;						//pָ����һ���ڽӵ�
		}
	}

	if(m<G.vexnum)
		return ERROR;							//������ͼ�л�·
	else
		return OK;
}

void main()
{
	printf("�봴��һ������ͼ��\n");
	ALGraph G;
	CreateUDG(&G);
	printf("�����ɹ���\n");
	if(TopologicalSort(G, topo))
	{
		printf("������ͼ������������Ϊ��\n");
		for(int i=0; i<G.vexnum; i++)
			printf("%c ", G.vertices[topo[i]]);
	}
	else
		printf("���棺�����������ͼ���л���");


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
}
