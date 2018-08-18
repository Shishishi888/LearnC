#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>
#define MaxInt 32767                                                //��ʾ���ֵ�������޷�
#define MVNum 100                                                   //��󶥵���
#define MAX 100
#define OK 1
#define ERROR 0

typedef struct
{
    char vexs[MVNum];                                               //��������趥�����������Ϊ�ַ���
    int arcs[MVNum][MVNum];                                         //�ڽӾ���,����ߵ�Ȩֵ����Ϊ����
    int vexnum, arcnum;                                             //ͼ�ĵ�ǰ�������ͱ���
}AMGraph;

int LocateVex(AMGraph *G, char vex)
{
    int i;
    for(i=0;i<G->vexnum;i++)
        if(vex==G->vexs[i])
            return i;
    return -1;
}

/*�����ڽӾ����ʾ����������ͼ*/
int CreateUDN(AMGraph *G)
{
    scanf("%d,%d",&(G->vexnum),&(G->arcnum));                        //�����ܶ��������ܱ���
    int i, j, k;
    for(i=0;i<G->vexnum;i++)
        scanf("%c",&(G->vexs[i]));                                   //�������붥�����Ϣ
    for(i=0;i<G->vexnum;i++)                                         //��ʼ���ڽӾ��󣬱ߵ�Ȩֵ����Ϊ���ֵMaxInt
        for(j=0;j<G->vexnum;j++)
            G->arcs[i][j]=MaxInt;
    char v1, v2;
    int w;
    for(j=0;j<G->arcnum;j++)                                         //�����ڽӾ���
    {
        scanf("%c,%c,%d",&v1,&v2,&w);                                //����һ�����·��Ķ��㼰Ȩֵ
        i=LocateVex(G,v1);                                           //ȷ��v1��v2��G�е�λ�ã�������������±�
        j=LocateVex(G,v2);
        G->arcs[i][j]=w;                                             //��<v1,v2>��Ȩֵ��Ϊw
        G->arcs[j][i]=G->arcs[i][j];                                 //��<v1,v2>�ĶԳƱ�<v2,v1>��ȨֵΪw
    }
    return OK;
}

bool visited[MVNum];                                                 //���ʱ�����飬�����ڱ�������������ĳ�������Ƿ��Ѿ������ʣ����ֵΪfalse��һ�������ʣ�����Ӧ�ķ���ֵ��Ϊtrue

/*�����ڽӾ����ʾͼ�����������������*/
void DFS_AM(AMGraph *G, int v)                                       //ͼGΪ�ڽӾ������ͣ��ӵ�v������������������������ͼG
{
    printf("%c ",G->vexs[v]);                                        //���ʵ�v�����㣬���÷��ʱ�־������Ӧ����ֵΪtrue
    visited[v]=true;
    int w;
    for(w=0;w<G->vexnum;w++)
        if((G->arcs[v][w]!=MaxInt)&&(!visited[w]))                   //w��v���ڽӵ㣬���wΪ���ʣ���ݹ����DFS_AL
            DFS_AM(G, w);
}

typedef struct
{
    int *base;
    int front;
    int rear;
}SqQueue;

/*ѭ�����еĳ�ʼ��*/
int InitQueue(SqQueue *Q)
{
    Q->base=(int *)malloc(sizeof(int)*MAX);
    if(!Q->base)
        exit(0);
    Q->front=Q->rear=0;
    return OK;
}

/*ѭ�����е����*/
int EnQueue(SqQueue *Q, int e)
{
    if((Q->rear+1)%MAX==Q->front)
        return ERROR;
    Q->base[Q->rear]=e;
    Q->rear=(Q->rear+1)%MAX;
    return OK;
}

/*ѭ�����еĳ���*/
int DeQueue(SqQueue *Q, int *e)
{
    if(Q->front==Q->rear)
        return ERROR;
    e=&Q->base[Q->front];
    Q->front=(Q->front+1)%MAX;
    return OK;
}

/*�ж�ѭ�������Ƿ�Ϊ��*/
bool QueueEmpty(SqQueue *Q)
{
    if(Q->front==Q->rear)
        return true;
    else
        return false;
}

/*�����ڽӾ����ʾͼ�Ĺ��������������*/
void BFS_AM(AMGraph *G, int v)
{
    printf("%c ",G->vexs[v]);                                               //���ʵ�v�����㣬���÷��ʱ�־������Ӧ����ֵΪtrue
    visited[v]=true;
    SqQueue *Q=(SqQueue *)malloc(sizeof(SqQueue));
    InitQueue(Q);                                                           //��������Q��ʼ�����ÿ�
    EnQueue(Q, v);                                                          //v����
    int *u;
    int w;
    while(!QueueEmpty(Q))
    {
        DeQueue(Q,u);                                                       //��ͷԪ�س��ӣ�����Ϊu
        for(w=FirstAdjVex(G,*u);w>=0;w=NextAdjVex(G,*u,w))                  //���μ��u�������ڽӵ�w��FirstAdjVex(G,u)��ʾu�ĵ�һ���ڽӵ�
                                                                            //NextAdjVex(G,u,w)��ʾu�����w����һ���ڽӵ㣬w>=0��ʾ�����ڽӵ�
            if(!visited[w])                                                 //wΪu����δ���ʵ��ڽӶ���
            {
                printf("%c ",G->vexs[w]);                                   //����w�����÷��ʱ�־������Ӧ����ֵΪtrue
                visited[w]=true;
                EnQueue(Q, w);                                              //w����
            }
    }
}

/*��С������������ķ�㷨��*/
struct
{
    char adjvex;                                                             //��С����U�еĶ���
    int lowcost;                                                             //��С���ϵ�Ȩֵ
}Closedge;                                                                   //��������������Closedge closedge[MVNum]

int Min(Closedge *closedge, int vexnum)
{
    int i, j;
    int min;
    min=closedge[0].lowcost;
    for(i=0;i<vexnum;i++)
    {
        if(min>closedge[i].lowcost)
        {
            min=closedge[i].lowcost;
            j=i;
        }
    }
    return j;
}

void MiniSpanTree_Prim(AMGraph *G, char u, Closedge *closedge)                //����ͼG���ڽӾ�����ʽ���棬�Ӷ���u��������G����С������T�����T�ĸ�����
{
    int k=LocateVex(G, u);                                                    //kΪ����u���±�
    int j;
    for(j=0;j<G->vexnum;++j)                                                  //��V-U��ÿһ������vj����ʼ��closedge[j]
        if(j!=k)
        {
            closedge[j].adjvex=u;
            closedge[j].lowcost=G->arcs[k][j];
        }
    closedge[k].lowcost=0;                                                  //��ʼ����U={u}
    int i;
    for(i=1;i<G->vexnum;++i)                                                  //ѡ������n-1�����㣬����n-1���ߣ�n=G.vexnum��
    {
        k=Min(closedge, G->vexnum);                                           //���T����һ����㣺��k�����㣬closedge[k]�д��е�ǰ��С��
        char u0=closedge[k].adjvex;                                           //u0Ϊ��С�ߵ�һ�����㣬u0����U
        char v0=G->vexs[k];                                                   //v0Ϊ��С�ߵ���һ�����㣬v0����V-U
        printf("%d %d ",u0, v0);
        closedge[k].lowcost=0;                                              //��k�����㲢��U��
        for(j=0;j<G->vexnum;++j)
        {
            if(G->arcs[k][j]<closedge[j].lowcost)                           //�¶��㲢��U������ѡ����С��
            {
                closedge[j].adjvex=G->vexs[k];
                closedge[j].lowcost=G->arcs[k][j];
            }
        }
    }
}

/*��С����������³˹�����㷨��*/
struct
{
    char Head;                                                 //�ߵ�ʼ��
    char Tail;                                                 //�ߵ��յ�
    int lowcost;                                               //���ϵ�Ȩֵ
}Edge;                                                         //��������������Edge edge[arcnum]

int Vexset[MVNum];                                             //��������

void Sort(Edge *egde, int arcnum)
{
    int i, j, temp;
    for(i=0;i<arcnum-1;i++)
        for(j=arcnum-1;j>=i+1;j--)
            if(edge[j].lowcost<edge[j-1].lowcost)
            {
                temp=edge[j].lowcost;
                edge[j].lowcost=edge[j-1].lowcost;
                edge[j-1].lowcost=temp;
            }
}

void MiniSpanTree_Kruskal(AMGraph *G, Edge *edge)              //����ͼG���ڽӾ�����ʽ���棬����G����С������T�����T�ĸ�����
{
    Sort(edge, G->arcnum);
    int i;                                                     //������Edge�е�Ԫ�ذ�Ȩֵ��С��������
    for(i=0;i<G->arcnum;++i)                                   //�������飬��ʾ�������Գ�һ����ͨ����
        Vexset[i]=i;
    for(i=0;i<G->arcnum;++i)                                   //���β鿴������Edge�еı�
    {
        int v1=LocateVex(G, edge[i].Head);                     //v1Ϊ�ߵ�ʼ��Head���±�
        int v2=LocateVex(G, edge[i].Tail);                     //v2Ϊ�ߵ��յ�T(closedge+j)->ail���±�
        int vs1=Vexset[v1];                                    //��ȡ��Edge[i]��ʼ�����ڵ���ͨ����vs1
        int vs2=Vexset[v2];                                    //��ȡ��Edge[i]���յ����ڵ���ͨ����vs2
        if(vs1!=vs2)
        {
            printf("%d %d ", edge[i].Head, edge[i].Tail);      //����˱�
            int j;
            for(j=0;j<G->vexnum;++j)                           //�ϲ�vs1��vs2��������������������ͳһ���
                if(Vexset[j]==vs2)                             //���ϱ��Ϊvs2�Ķ���Ϊvs1
                    Vexset[j]=vs1;
        }
    }
}

bool S[MVNum];                                                  //��¼Դ��v0���յ�vi�Ƿ��ѱ�ȷ�����·�����ȣ�true��ʾȷ����false��ʾ��δȷ��
char Path[MVNum];                                               //��¼Դ��v0���յ�vi�ĵ�ǰ���·����vi��ֱ��ǰ��������ţ����ֵΪ�����v0��vi�л�����Path[i]Ϊv0������Ϊ-1
int D[MVNum];                                                   //��¼��Դ��v0���յ�vi�ĵ�ǰ���·�����ȣ����ֵΪ�������v0��vi�л�����D[i]Ϊ���ϵ�Ȩֵ������Ϊ��

/*���·�����Ͻ�˹�����㷨��*/
void ShortestPath_DIJ(AMGraph *G, int v0)                       //��Dijkstra�㷨������ͼG��v0���㵽���ඥ������·��
{
    int n=G->vexnum;                                            //nΪG�ж���ĸ���
    int v;
    for(v=0;v<n;++v)                                            //n���������γ�ʼ��
    {
        S[v]=false;                                             //S��ʼΪ�ռ�
        D[v]=G->arcs[v0][v];                                    //��v0�������յ�����·�����ȳ�ʼ��Ϊ���ϵ�Ȩֵ
        if(D[v]<MaxInt)                                         //���v0��v֮���л�����v��ǰ����Ϊv0
            Path[v]=v0;
        else
            Path[v]=-1;                                         //���v0��v֮���޻�����v��ǰ����Ϊ-1
    }
    S[v0]=true;                                                 //��v0����S
    D[v0]=0;                                                    //Դ�㵽Դ��ľ���Ϊ0

    int i;                                                      //��ʼ����������ʼ��ѭ����ÿ�����v0��ĳ������v�����·������v����S��
    for(i=1;i<n;++i)                                            //������n-1�����㣬���ν��м���
    {
        int min=MaxInt;
        int w;
        for(w=0;w<n;++w)
        if(!S[w]&&D[w]<min)                                     //ѡ��һ����ǰ�����·�����յ�Ϊv
        {
            v=w;                                                //��v����S
            min=D[w];
        }
        S[v]=true;                                              //���´�v0����������V-S�����ж�������·������
        for(w=0;w<n;++w)
            if(!S[w]&&(D[v]+G->arcs[v][w]<D[w]))
            {
                D[w]=D[v]+G->arcs[v][w];                        //����D[w]
                Path[w]=v;                                      //����w��ǰ��Ϊv
            }
    }
}








