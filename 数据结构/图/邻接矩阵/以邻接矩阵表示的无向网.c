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
    int vexnum, arcnum;                                             //ͼ�ĵ�ǰ�������ͱ���
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
        G->arcs[j][i]=G->arcs[i][j];                                 //��<v1,v2>�ĶԳƱ�<v2,v1>��ȨֵΪw

    }
    return OK;
}

/*�����������������ͨ��*/
bool visited[MVNum];                                                 //���ʱ�����飬�����ڱ�������������ĳ�������Ƿ��Ѿ������ʣ����ֵΪfalse��һ�������ʣ�����Ӧ�ķ���ֵ��Ϊtrue
void DFS_AM(AMGraph G, int v)                                        //ͼGΪ�ڽӾ������ͣ��ӵ�v������������������������ͼG
{
    printf("%c ",G.vexs[v]);                                         //���ʵ�v�����㣬���÷��ʱ�־������Ӧ����ֵΪtrue
    visited[v]=true;
    for(int w=0; w<G.vexnum; w++)
        if((G.arcs[v][w]!=MaxInt)&&(!visited[w]))                    //w��v���ڽӵ㣬���wΪ���ʣ���ݹ����DFS_AL
            DFS_AM(G, w);
}


/*�������������������ͨ��*/
void DFSTraverse_AM(AMGraph G)
{
	for(int v=0; v<G.vexnum; v++)
		visited[v]=false;                                              //���ʱ�־�����ʼ��
	for(int v=0; v<G.vexnum; v++)									   //ѭ�������㷨DFS_AM
		if(!visited[v])												   //����δ���ʵĶ������DFS_AM
			DFS_AM(G, v);
}

/*�����������������ͨ��*/
typedef struct
{
    int *base;
    int front;
    int rear;
}SqQueue;

int InitQueue(SqQueue *Q)											   //ѭ�����г�ʼ��
{
    Q->base=(int *)malloc(sizeof(int)*MAX);
    if(!Q->base)
        exit(0);
    Q->front=Q->rear=0;
    return OK;
}

int EnQueue(SqQueue *Q, int e)									       //ѭ�����е����
{
    if((Q->rear+1)%MAX==Q->front)
        return ERROR;
    Q->base[Q->rear]=e;
    Q->rear=(Q->rear+1)%MAX;
    return OK;
}

int DeQueue(SqQueue *Q, int *e)										   //ѭ�����г���
{
    if(Q->front==Q->rear)
        return ERROR;
    *e=Q->base[Q->front];
    Q->front=(Q->front+1)%MAX;
    return OK;
}

bool QueueEmpty(SqQueue Q)											   //ѭ�����г���
{
    if(Q.front==Q.rear)
        return true;
    else
        return false;
}

bool visited_1[MVNum];                                                 //���ʱ�����飬�����ڱ�������������ĳ�������Ƿ��Ѿ������ʣ����ֵΪfalse��һ�������ʣ�����Ӧ�ķ���ֵ��Ϊtrue
void BFS_AM(AMGraph G, int v)
{
    printf("%c ", G.vexs[v]);                                          //���ʵ�v�����㣬���÷��ʱ�־������Ӧ����ֵΪtrue
    visited_1[v]=true;
    SqQueue Q;
    InitQueue(&Q);                                                     //��������Q��ʼ�����ÿ�
    EnQueue(&Q, v);                                                    //v����
    int u;

    while(!QueueEmpty(Q))
    {
        DeQueue(&Q, &u);                                               //��ͷԪ�س��ӣ�����Ϊu
		for(int w=0; w<G.vexnum; w++)
            if(G.arcs[u][w]!=0&&!visited_1[w])                         //wΪu����δ���ʵ��ڽӶ���
            {
                printf("%c ",G.vexs[w]);                               //����w�����÷��ʱ�־������Ӧ����ֵΪtrue
                visited_1[w]=true;
                EnQueue(&Q, w);                                        //w����
            }
    }

}

/*�������������������ͨ��*/
void BFSTraverse_AM(AMGraph G)
{
	for(int v=0; v<G.vexnum; v++)
		visited_1[v]=false;                                              //���ʱ�־�����ʼ��
	for(int v=0; v<G.vexnum; v++)									   //ѭ�������㷨DFS_AM
		if(!visited_1[v])												   //����δ���ʵĶ������DFS_AM
			BFS_AM(G, v);
}

void main()
{
	printf("�봴��һ����������\n");
	AMGraph G;
	CreateUDN(&G);
	printf("�����ɹ���\n");

	printf("������һ��������±��Կ�ʼ��������������");
	int v;
	scanf("%d", &v);
	printf("��������������������������Ľ��Ϊ��\n");
	DFS_AM(G, v);
	printf("\n");
	printf("���������Ĺ���������������Ľ��Ϊ��\n");
	BFS_AM(G, v);

	printf("\n");
	printf("��ӡ����������\n");
	for(int i=0; i<G.vexnum; i++)
	{
		for(int j=0; j<G.vexnum; j++)
			printf("%8d", G.arcs[i][j]);
		printf("\n");
	}
}
