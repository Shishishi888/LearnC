#include <stdio.h>
#include <malloc.h>

typedef struct{
    struct BSTNode *llink;
    struct BSTNode *rlink;
    int data;
    int count;
}BSTNode, *BSTree;

void InsertBST(BSTree *T, int e){//将新结点插入二叉排序树
    if(!*T){                                                               //找到插入位置，递归结束{
        BSTNode *S=(BSTNode *)malloc(sizeof(BSTNode));                     //生成新结点*S
        S->llink=NULL;                                                     //新结点*S作为叶子结点
        S->data=e;                                                         //新结点的数据域置为e
        S->count=0;
        S->rlink=NULL;
        *T=S;                                                     //把新结点*S连接到已找到的插入位置
    }
    else if(e<(*T)->data)                                         //将*S插入左子树
        InsertBST(&((*T)->llink), e);
    else if(e>(*T)->data)                                         //将*S插入右子树
        InsertBST(&((*T)->rlink), e);
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


void InOrderTraverse(BSTree T){//中序遍历二叉排序树
    if(T){
        InOrderTraverse(T->llink);
        printf("%d，%d  ",T->data, T->count);
        InOrderTraverse(T->rlink);
    }
}

int Search_Insert_BST(BSTree T, int data){//查找或插入结点
    if(!T) exit(0);
    BSTNode *p=T;//工作指针p初始化为二叉排序树的根结点
    BSTNode *q=NULL;

    while(p&&data!=p->data){//查找结点
        if(data<p->data){
            q=p;
            p=p->llink;
        }
        else if(data>p->data){
            q=p;
            p=p->rlink;
        }
    }

    if(p){//查找到该结点
        (p->count)++;
        return 1;
        }

    else{//该结点不存在
        p=(BSTNode *)malloc(sizeof(BSTNode));
        p->llink=NULL;
        p->rlink=NULL;
        p->data=data;
        p->count=0;

        if(data<q->data)
            q->llink=p;
        else if(data>q->data)
            q->rlink=p;

        return 0;
    }
}

/*
int Search_Insert_BST(BSTree T, int X){
    BSTNode *s=(BSTNode *)malloc(sizeof(BSTNode));
    s->data=X;
    s->count=0;
    s->llink=s->rlink=NULL;

    if(!T){
        T=s;
        return 0;
    }

    BSTNode *f=NULL;
    BSTNode *q=T;

    while(q){
        if(q->data==X){
            q->count++;
            return 1;
        }

        f=q;

        if(X<q->data)
            q=q->llink;
        else
            q=q->rlink;
    }

    if(f->data>X)
        f->llink=s;
    else
        f->rlink=s;

    return 0;
}
*/

void main(){
    printf("请先创建一棵二叉排序树：\n");
    BSTree BST;
    CreatBST(&BST);
    printf("创建成功！\n");
    printf("该二叉排序树的中序遍历结果（data，count）为：");
    InOrderTraverse(BST);
    printf("\n");

    int data;
    printf("请输入您想要查找结点的值：");
    scanf("%d", &data);
    int result=Search_Insert_BST(BST, data);
    printf("查找成功！\n");
    if(result)
        printf("存在您要查找的结点！\n");
    else{
        printf("不存在您要查找的结点！\n");
        printf("正在将该结点插入到二叉排序树中 ...\n");
        printf("插入成功！\n");
    }

    printf("该二叉排序树的中序遍历结果（data，count）为：");
    InOrderTraverse(BST);
}

/*
    已知二叉树T的结点形式为(llink, data, count, rlink)，在树中查找值为X的结点，
    若找到，则记数（count）加1；否则，作为一个新结点插入树中，插入后仍为二叉排
    序树，写出其非递归算法。
*/
