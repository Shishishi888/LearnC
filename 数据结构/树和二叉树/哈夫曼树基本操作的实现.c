#include <stdio.h>
#include <malloc.h>

typedef struct{
    int weight;
    int parent, lchild, rchild;
}HTNode, *HuffmanTree;

/*ѡ��Ȩֵ��С���������*/
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

/*�����������*/
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

/*���ݹ������������������*/
typedef char **HuffmanCode;                                                   //��̬�������鴢������������
                                                                              //��Ϊÿ�������������Ǳ䳤���룬����ʹ��һ��ָ�����������ÿ���ַ����봮���׵�ַ

void CreatHuffmanCode(HuffmanTree HT, HuffmanCode *HC, int n)
{
    *HC=(char **)malloc(sizeof(char *)*(n+1));                                //���䴢��n���ַ�����ı����ռ�
    char *cd=(char *)malloc(sizeof(char)*n);                                  //������ʱ���ÿ���ַ�����Ķ�̬����ռ�
    cd[n-1]='\0';                                                             //���������
    int i;
    for(i=1;i<=n;i++)                                                         //����ַ������������
    {
        int start=n-1;                                                        //start��ʼʱָ����󣬼����������λ��
        int c=i;
        int f=HT[i].parent;                                                   //fָ��c��˫�׽��
        while(f!=0)                                                           //��Ҷ�ӽ�㿪ʼ���ϻ��ݣ�ֱ�������
        {
            --start;
            if(HT[f].lchild==c)                                               //���c��f�����ӣ������ɴ���0
                cd[start]='0';
            else                                                              //���c��f���Һ��ӣ������ɴ���1
                cd[start]='1';
            c=f;                                                              //�������ϻ���
            f=HT[f].parent;
        }
        (*HC)[i]=(char *)malloc(sizeof(char)*(n-start));                      //Ϊ��i���ַ��������ռ�
        int j;
        for(j=0;j<n-start;j++)
            (*HC)[i][j]=cd[start+j];                                          //����õı������ʱ�ռ�cd���Ƶ�HC�ĵ�ǰ����
    }
    free(cd);                                                                 //�ͷ���ʱ�ռ�
}

