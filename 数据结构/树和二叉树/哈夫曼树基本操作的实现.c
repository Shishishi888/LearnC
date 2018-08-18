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
void CreateHuffmanTree(HuffmanTree *HT, int n)
{
    if(n<=1)
        return;
    int m=2*n-1;
    *HT=(HTNode *)malloc(sizeof(HTNode)*(m+1));
    int i;
    for(i=1;i<=m;i++)
    {
        (*HT)[i].parent=0;
        (*HT)[i].lchild=0;
        (*HT)[i].rchild=0;
    }
    for(i=1;i<=n;i++)
        scanf("%d",&((*HT)[i].weight));
    int *s1, *s2;
    for(i=n+1;i<=m;i++)
    {
        Select(*HT, i-1, s1, s2);
        (*HT)[*s1].parent=i;
        (*HT)[*s2].parent=i;
        (*HT)[i].lchild=*s1;
        (*HT)[i].rchild=*s2;
        (*HT)[i].weight=(*HT)[*s1].weight+(*HT)[*s2].weight;
    }
}

/*根据哈夫曼树求哈夫曼编码*/
typedef char **HuffmanCode;                                                   //动态分配数组储存哈夫曼编码表
                                                                              //因为每个哈夫曼编码是变长编码，所以使用一个指针数组来存放每个字符编码串的首地址

void CreatHuffmanCode(HuffmanTree HT, HuffmanCode *HC, int n)
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

