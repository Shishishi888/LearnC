#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdbool.h>
#define MVNum 100                            //��󶥵���
#define MAXSIZE 100
#define OK 1
#define ERROR 0
typedef int OtherInfo;						 //����������¼��������Ȩֵ
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
    int vexnum, arcnum;                      //���ĵ�ǰ�������ͱ���
}ALGraph;

/*�����ڽӱ��ʾ������������*/
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
	printf("��������������ܶ�������");     					     //�����ܶ��������ܱ���
	scanf("%d", &(G->vexnum));
	printf("��������������ܱ�����");
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
    ArcType w;
    printf("����������ÿ���������Ķ��㼰Ȩֵ�����A, �յ�B��Ȩֵ����\n");
    for(int k=0; k<G->arcnum; k++)           //������ߣ������ڽӱ�
    {
    	//fflush(stdin);				     //ˢ�»�����
    	char c=getchar();                    //�Ե��������еġ��س���
    	printf("�������%d���������Ķ��㣺", k+1);
        scanf("%c, %c, %d", &v1, &v2, &w);   //����һ������������������
        int i=LocateVex(*G, v1);             //ȷ��v1��v2��G�е�λ�ã���������G->vertices�е����
        int j=LocateVex(*G, v2);
        ArcNode *p1=(ArcNode *)malloc(sizeof(ArcNode));              //�����µıߵĽ��*p1
        p1->adjvex=j;                                                //�ڽӵ����Ϊj
        p1->info=w;
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
{ //������G�����ڽӱ���ṹ
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
		return ERROR;							//���������л�·
	else
		return OK;
}

/*�ؼ�·���㷨*/
ArcType ve[MVNum];								//��¼�¼�vi�����緢��ʱ��
ArcType vl[MVNum];								//��¼�¼�vl�����緢��ʱ��

int CriticalPath(ALGraph G)
{ //GΪ�ڽӱ���������������G�ĸ���ؼ��
	if(!TopologicalSort(G, topo))				//�������������㷨��ʹ�������б�����topo�У�������ʧ�ܣ������
		return ERROR;							//���򻷣�����ERROR
	int n=G.vexnum;								//nΪ�������
	for(int i=0; i<n; i++)
		ve[i]=0;								//��ÿ��ʱ������緢��ʱ���ʼ��Ϊ0

	//�����˴�����ÿ���¼������緢��ʱ��
	for(int i=0; i<n; i++)
	{
		int k=topo[i];							//ȡ�����������еĶ������k
		ArcNode *p=G.vertices[k].firstarc; 		//pָ��k�ĵ�һ���ڽӶ���
		while(p!=NULL)							//���θ���k�������ٽ綥������緢��ʱ��
		{
			int j=p->adjvex;					//jΪ�ڽӶ�������
			if(ve[j]<ve[k]+p->info)
				ve[j]=ve[k]+p->info;			//���¶���j�����緢��ʱ��
			p=p->nextarc;						//pָ��k����һ���ڽӶ���
		}
	}

	for(int i=0; i<n; i++)
		vl[i]=ve[n-1];							//��ÿ��ʱ�����ٷ���ʱ���ó�ֵve[n-1]

	//�������˴�����ÿ���¼�����ٷ���ʱ��
	for(int i=n-1; i>=0; i--)
	{
		int k=topo[i];							//ȡ�����������еĶ������k
		ArcNode *p=G.vertices[k].firstarc;		//pָ��k�ĵ�һ���ڽӶ���
		while(p!=NULL)							//����k���ڽӵ㣬����k����ٷ���ʱ��
		{
			int j=p->adjvex;					//jΪ�ڽӶ�������
			if(vl[k]>vl[j]-p->info)
				vl[k]=vl[j]-p->info;			//���¶���k����ٷ���ʱ��
			p=p->nextarc;						//pָ��k����һ���ڽӵ�
		}
	}

	//�ж�ÿһ����Ƿ�Ϊ�ؼ��
	for(int i=0; i<n; i++)						//ÿ��ѭ�����viΪ��ʼ������л
	{
		ArcNode *p=G.vertices[i].firstarc;		//pָ��i�ĵ�һ���ڽӶ���
		while(p!=NULL)
		{
			int j=p->adjvex;					//jΪi�ڽӶ�������
			int e=ve[i];						//����<vi, vj>�����翪ʼʱ��
			int l=vl[j]-p->info;				//����<vi, vj>����ٿ�ʼʱ��
			if(e==l)							//��Ϊ�ؼ���������<vi, vj>
				printf("%c %c  ", G.vertices[i].data, G.vertices[j].data);
			p=p->nextarc;						//pָ��i����һ���ڽӶ���
		}
	}
}

void main()
{
	printf("�봴��һ����������\n");
	ALGraph G;
	CreateUDG(&G);
	printf("�����ɹ���\n");
	printf("������������Ĺؼ�·����\n");
	if(!CriticalPath(G))
		printf("���棺����������������л���");

	printf("\n");
	printf("��ӡ����������\n");
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
