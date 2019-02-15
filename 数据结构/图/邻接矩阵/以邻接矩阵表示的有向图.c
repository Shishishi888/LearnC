#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>
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
    int vexnum, arcnum;                                             //ͼ�ĵ�ǰ�������ͱ���
}AMGraph;

/*�����ڽӾ����ʾ����������ͼ*/
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

    for(int i=0; i<G->vexnum; i++)                                   //��ʼ���ڽӾ��󣬱ߵ�Ȩֵ����Ϊ0
        for(int j=0; j<G->vexnum; j++)
            G->arcs[i][j]=0;

    VerTexType v1, v2;
	printf("����������ÿ���������Ķ��㣨���A, �յ�B����\n");
    for(int k=0; k<G->arcnum; k++)                                   //�����ڽӾ���
    {
		char c=getchar();											 //�Ե��������еġ��س���
    	printf("�������%d���������Ķ���: ", k+1);
        scanf("%c, %c", &v1, &v2);                       		     //����һ���������Ķ��㼰Ȩֵ
        int i=LocateVex(*G, v1);                                     //ȷ��v1��v2��G�е�λ�ã�������������±�
        int j=LocateVex(*G, v2);
        G->arcs[i][j]=1;                                             //��<v1,v2>��Ȩֵ��Ϊ1
        G->arcs[j][i]=0;                                			 //��<v1,v2>�ĶԳƱ�<v2,v1>��ȨֵΪ1

    }
    return OK;
}

/*�����������������ͨͼ*/
bool visited[MVNum];                                                 //���ʱ�����飬�����ڱ�������������ĳ�������Ƿ��Ѿ������ʣ����ֵΪfalse��һ�������ʣ�����Ӧ�ķ���ֵ��Ϊtrue
void DFS_AM(AMGraph G, int v)                                        //ͼGΪ�ڽӾ������ͣ��ӵ�v������������������������ͼG
{
    printf("%c ",G.vexs[v]);                                         //���ʵ�v�����㣬���÷��ʱ�־������Ӧ����ֵΪtrue
    visited[v]=true;
    for(int w=0; w<G.vexnum; w++)
        if((G.arcs[v][w]!=0)&&(!visited[w]))                  	     //w��v���ڽӵ㣬���wΪ���ʣ���ݹ����DFS_AL
            DFS_AM(G, w);
}

/*�������������������ͨͼ*/
void DFSTraverse_AM(AMGraph G)
{
	for(int v=0; v<G.vexnum; v++)
		visited[v]=false;                                             //���ʱ�־�����ʼ��
	for(int v=0; v<G.vexnum; v++)									  //ѭ�������㷨DFS_AM
		if(!visited[v])												  //����δ���ʵĶ������DFS_AM
			DFS_AM(G, v);
}

/*�����������������ͨͼ*/
typedef struct
{
    int *base;
    int front;
    int rear;
}SqQueue;

int InitQueue(SqQueue *Q)											  //ѭ�����г�ʼ��
{
    Q->base=(int *)malloc(sizeof(int)*MAX);
    if(!Q->base)
        exit(0);
    Q->front=Q->rear=0;
    return OK;
}

int EnQueue(SqQueue *Q, int e)									      //ѭ�����е����
{
    if((Q->rear+1)%MAX==Q->front)
        return ERROR;
    Q->base[Q->rear]=e;
    Q->rear=(Q->rear+1)%MAX;
    return OK;
}

int DeQueue(SqQueue *Q, int *e)										  //ѭ�����г���
{
    if(Q->front==Q->rear)
        return ERROR;
    *e=Q->base[Q->front];
    Q->front=(Q->front+1)%MAX;
    return OK;
}

bool QueueEmpty(SqQueue Q)											  //ѭ�����г���
{
    if(Q.front==Q.rear)
        return true;
    else
        return false;
}

bool visited_1[MVNum];                                                //���ʱ�����飬�����ڱ�������������ĳ�������Ƿ��Ѿ������ʣ����ֵΪfalse��һ�������ʣ�����Ӧ�ķ���ֵ��Ϊtrue
void BFS_AM(AMGraph G, int v)
{
    printf("%c ", G.vexs[v]);                                         //���ʵ�v�����㣬���÷��ʱ�־������Ӧ����ֵΪtrue
    visited_1[v]=true;
    SqQueue Q;
    InitQueue(&Q);                                                    //��������Q��ʼ�����ÿ�
    EnQueue(&Q, v);                                                   //v����
    int u;

    while(!QueueEmpty(Q))
    {
        DeQueue(&Q, &u);                                              //��ͷԪ�س��ӣ�����Ϊu
		for(int w=0; w<G.vexnum; w++)
            if(G.arcs[u][w]!=0&&!visited_1[w])                        //wΪu����δ���ʵ��ڽӶ���
            {
                printf("%c ",G.vexs[w]);                              //����w�����÷��ʱ�־������Ӧ����ֵΪtrue
                visited_1[w]=true;
                EnQueue(&Q, w);                                       //w����
            }
    }

}

/*�������������������ͨͼ*/
void BFSTraverse_AM(AMGraph G)
{
	for(int v=0; v<G.vexnum; v++)
		visited_1[v]=false;                                            //���ʱ�־�����ʼ��
	for(int v=0; v<G.vexnum; v++)									   //ѭ�������㷨DFS_AM
		if(!visited_1[v])											   //����δ���ʵĶ������DFS_AM
			BFS_AM(G, v);
}

void main()
{
	printf("�봴��һ������ͼ��\n");
	AMGraph G;
	CreateUDN(&G);
	printf("�����ɹ���\n");

	printf("������ͼ������������������Ľ��Ϊ��\n");
	DFSTraverse_AM(G);
	printf("\n");
	printf("������ͼ�Ĺ���������������Ľ��Ϊ��\n");
	BFSTraverse_AM(G);

	printf("\n");
	printf("��ӡ������ͼ��\n");
	for(int i=0; i<G.vexnum; i++)
	{
		for(int j=0; j<G.vexnum; j++)
			printf("%3d", G.arcs[i][j]);
		printf("\n");
	}
}
