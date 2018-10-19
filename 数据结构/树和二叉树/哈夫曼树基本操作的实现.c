#include <stdio.h>
#include <malloc.h>

typedef struct{
    int weight;
    int parent, lchild, rchild;
}HTNode, *HuffmanTree;

/*选择权值最小的两个结点*/
void Select(HuffmanTree HT, int n, int *s1, int *s2)
{
    int i;
    int min=HT[1].weight;
    for(i=1;i<n;i++)
    {
        if(HT[i].weight<min&&HT[i].parent==0)
        {
            min=HT[i].weight;
            *s1=i;
        }
    }
    min=HT[1].weight;
    for(i=1;i<n;i++)
    {
        if(HT[i].weight<min&&HT[i].parent==0&&i!=*s1)
        {
            min=HT[i].weight;
            *s2=i;
        }
    }
}

/*构造哈夫曼树*/
void CreateHuffmanTree(HuffmanTree *HT, int n)//构造哈夫曼树HT
{
    if(n<=1)
        return;
    int m=2*n-1;
    *HT=(HTNode *)malloc(sizeof(HTNode)*(m+1));//0号单元未用，所以需要动态分配m+1个单元，HT[m]表示根节点
    int i;
    for(i=1;i<=m;i++)//将1～m号单元中的双亲、左孩子，右孩子的下标都初始化为0
    {
        (*HT)[i].parent=0;
        (*HT)[i].lchild=0;
        (*HT)[i].rchild=0;
    }
    for(i=1;i<=n;i++)//输入前n个单元中叶子结点的权值
        scanf("%d",&((*HT)[i].weight));

    /*----------初始化工作结束，下面开始创建哈夫曼树----------*/
    int *s1, *s2;
    for(i=n+1;i<=m;i++)//通过n-1次的选择、删除、合并来创建哈夫曼树
    {
        Select(*HT, i-1, s1, s2);//在HT[k]（1≤k≤i-1）中选择两个其双亲域为0且权值最小的结点，并返回它们在HT中的序号s1和s2
        //得到新结点i，从森林中删除s1和s2，将s1和s2的双亲域由0改为i
        (*HT)[*s1].parent=i;
        (*HT)[*s2].parent=i;
        //s1，s2分别作为i的左右孩子
        (*HT)[i].lchild=*s1;
        (*HT)[i].rchild=*s2;
        (*HT)[i].weight=(*HT)[*s1].weight+(*HT)[*s2].weight;//i的权值为左右孩子的权值之和
    }
}

/*根据哈夫曼树求哈夫曼编码*/
typedef char **HuffmanCode;                                                   //动态分配数组储存哈夫曼编码表
                                                                              //因为每个哈夫曼编码是变长编码，所以使用一个指针数组来存放每个字符编码串的首地址

void CreatHuffmanCode(HuffmanTree HT, HuffmanCode *HC, int n)                 //从叶子到根逆向求每个字符的哈夫曼编码，储存在编码表HC中
{
    *HC=(char **)malloc(sizeof(char *)*(n+1));                                //分配储存n个字符编码的编码表空间
    char *cd=(char *)malloc(sizeof(char)*n);                                  //分配临时存放每个字符编码的动态数组空间
    cd[n-1]='\0';                                                             //编码结束符
    int i;
    for(i=1;i<=n;i++)                                                         //逐个字符求哈夫曼编码
    {
        int start=n-1;                                                        //start开始时指向最后，即编码结束符位置
        int c=i;
        int f=HT[i].parent;                                                   //f指向c的双亲结点
        while(f!=0)                                                           //从叶子结点开始向上回溯，直到根结点
        {
            --start;
            if(HT[f].lchild==c)                                               //结点c是f的左孩子，则生成代码0
                cd[start]='0';
            else                                                              //结点c是f的右孩子，则生成代码1
                cd[start]='1';
            c=f;                                                              //继续向上回溯
            f=HT[f].parent;
        }
        (*HC)[i]=(char *)malloc(sizeof(char)*(n-start));                      //为第i个字符编码分配空间
        int j;
        for(j=0;j<n-start;j++)
            (*HC)[i][j]=cd[start+j];                                          //将求得的编码从临时空间cd复制到HC的当前行中
    }
    free(cd);                                                                 //释放临时空间
}

