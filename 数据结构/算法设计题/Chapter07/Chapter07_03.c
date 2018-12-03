#include <stdio.h>
#include <malloc.h>

typedef struct{
    struct BSTNode *lchild;
    struct BSTNode *rchild;
    int data;
}BSTNode, *BSTree;

void InsertBST(BSTree *T, int e){//将新结点插入二叉排序树
    if(!*T){                                                              //找到插入位置，递归结束{
        BSTNode *S=(BSTNode *)malloc(sizeof(BSTNode));                    //生成新结点*S
        S->lchild=NULL;                                                    //新结点*S作为叶子结点
        S->data=e;                                                        //新结点的数据域置为e
        S->rchild=NULL;
        *T=S;                                                     //把新结点*S连接到已找到的插入位置
    }
    else if(e<(*T)->data)                                         //将*S插入左子树
        InsertBST(&((*T)->lchild), e);
    else if(e>(*T)->data)                                         //将*S插入右子树
        InsertBST(&((*T)->rchild), e);
}


void CreatBST(BSTree *T){//创建二叉排序树
    *T=NULL;
    int e;
    int i=1;
    printf("请输入排序二叉树的第%d个元素：",i);
    scanf("%d",&e);
    while(e!=-1)
    {
        InsertBST(T, e);
        i++;
        printf("请输入排序二叉树的第%d个元素：",i);
        scanf("%d",&e);
    }
}

void PrintAllX(BSTree T, int x){//从小到大输出二叉排序树中所有数据值≥x的结点
    if(T){
        PrintAllX(T->lchild, x);
        if(T->data>=x) printf("%d ", T->data);
        PrintAllX(T->rchild, x);
    }
}

/*
    首先从根结点开始查找，找到数值小于x的结点后，将其与双亲断开；如果
    根结点的值小于x，则沿右子树查找第一个大于等于x的结点，找到后与上面
    同样处理，输出处理后的二叉排序树。
*/
/*
void Print(BSTree T){
    if(T){
        Print(T->lchild);
        printf("%d ", T->data);
        Print(T->rchild);
    }
}

void PrintAllX(BSTree T, int x){//从小到大输出二叉排序树中所有数据值≥x的结点
    BSTNode *p=T;

    if(p){
        while(p&&p->data<x)//沿右分支向下，找到第一个值≥x的结点
            p=p->rchild;
        T=p;

        if(p){
            BSTNode *f=p;
            p=p->lchild;
            while(p&&p->data>=x){//沿左分支向下，找到第一个值<x的结点
                f=p;//f是p的双亲结点的指针，且指向第一个值≥x的结点
                p=p->lchild;
            }

            if(p)
                f->lchild=NULL;//双亲与第一个值<x的结点断开
            Print(T);
        }
    }
}
*/

void main(){

    printf("请先创建一棵二叉排序树：\n");
    BSTree BST;
    CreatBST(&BST);
    printf("创建成功！\n");

    int x;
    printf("请输入x的值：");
    scanf("%d", &x);

    printf("从小到大输出二叉排序树中所有数据值≥x的结点：");
    PrintAllX(BST, x);
}

/*
    已知二叉排序树采用二叉链表储存结构，根结点的指针为T，链结点的结构为(lchild, data, rchild)，
    其中lchild、rchild分别指向该结点的左、右孩子的指针，data域存放结点的数据信息。请写出递归算
    法，从小到大输出二叉排序树中所有数据值≥x的结点的数据。要求先找到第一个满足条件的结点后，再
    依次输出其他满足条件的结点。
*/
