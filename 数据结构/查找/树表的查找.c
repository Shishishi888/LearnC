#include <stdio.h>
#include <malloc.h>

typedef struct
{
    int key;
    char otherinfo[20];
}ElemType;

typedef struct BSTNode
{
    ElemType data;
    struct BSTNode *lchild, *rchild;
}BSTNode, *BSTree;

/*二叉排序树的递归查找*/
BSTree SearchBST(BSTree T, int key)
{
    if((!T)||key==T->data.key)
        return T;
    else if(key<T->data.key)
        return SearchBST(T->lchild, key);
    else
        return SearchBST(T->rchild, key);
}

/*二叉排序树的插入*/
void InsertBST(BSTree *T, ElemType e)
{
    if(!*T)                                                                //找到插入位置，递归结束
    {
        BSTNode *S=(BSTNode *)malloc(sizeof(BSTNode));                    //生成新结点*S
        S->data=e;                                                        //新结点的数据域置为e
        S->lchild=NULL;                                                   //新结点*S作为叶子结点
        S->rchild=NULL;
        *T=S;                                                              //把新结点*S连接到已找到的插入位置
    }
    else if(e.key<(*T)->data.key)                                            //将*S插入左子树
        InsertBST(&((*T)->lchild), e);
    else if(e.key>(*T)->data.key)                                            //将*S插入右子树
        InsertBST(&((*T)->rchild), e);
}

/*二叉排序树的创建*/
void CreatBST(BSTree *T)
{
    *T=NULL;
    ElemType e;
    int i=1;
    printf("请输入排序二叉树的第%d个元素（关键字，备注）：",i);
    scanf("%d,%s",&e.key,&e.otherinfo);
    while(e.key!=-1)
    {
        InsertBST(T, e);
        i++;
        printf("请输入排序二叉树的第%d个元素（关键字，备注）：",i);
        scanf("%d,%s",&e.key,&e.otherinfo);
    }
}

/*二叉排序树的删除*/
void DeleteBST(BSTree T, int key)
{
    BSTNode *p=T;
    BSTNode *f=NULL;
    while(p)
    {
        if(key==p->data.key)
            break;
        f=p;                                                            //*f为*p的双亲结点
        if(key<p->data.key)
            p=p->lchild;
        else
            p=p->rchild;
    }
    if(!p) return;
    BSTNode *q=p;
    BSTNode *s;
    if((p->lchild)&&(p->rchild))                                        //被删除结点*p左右子树均不为空
    {
        s=p->lchild;
        while(s->rchild)                                                //在*p的左子树中继续查找其前驱结点，即最右下结点
        {
            q=s;
            s=s->rchild;                                                //向右到尽头
        }
        p->data=s->data;                                                //s指向被删除结点的“前驱”
        if(q!=p)
            q->rchild=s->lchild;                                        //重接*q的右子树
        else
            q->lchild=s->lchild;                                        //重接*q的左子树
        free(s);
        return;
    }
    else if(!p->rchild)                                                 //被删除结点*p无右子树，只需要重接其左子树
        p=p->lchild;
    else if(!p->lchild)                                                 //被删除结点*p无左子树，只需要重接其右子树
        p=p->rchild;
    if(!f)                                                              //被删除结点为根结点
        T=p;
    else if(q==f->lchild)                                               //挂到*f的左子树位置
        f->lchild=p;
    else                                                                //挂到*f的右子树位置
        f->rchild=p;
    free(q);
}

/*二叉排序树的中序遍历*/
void InOrderTraverse(BSTree T)
{
    if(T)
    {
        InOrderTraverse(T->lchild);
        printf("%d ",T->data.key);
        InOrderTraverse(T->rchild);
    }
}

void main()
{
    BSTree BST;
    printf("请输入要创建的二叉排序树：\n");
    CreatBST(&BST);
    printf("二叉排序树创建完成!\n");
    printf("该二叉排序树的中序遍历结果为：");
    InOrderTraverse(BST);
    printf("\n");

    int key;
    BSTNode *SearchBST_Result;
    printf("请输入待查询的元素的关键字：");
    scanf("%d",&key);
    SearchBST_Result=SearchBST(BST, key);
    printf("查询成功！查询结果为（关键字，备注信息）：%d, %s",SearchBST_Result->data.key,SearchBST_Result->data.otherinfo);
    printf("\n");


    ElemType e;
    printf("请输入待插入的元素（关键字，备注信息）：");
    scanf("%d,%s",&e.key,&e.otherinfo);
    InsertBST(&BST, e);
    printf("插入成功！插入之后的二叉排序树为：");
    InOrderTraverse(BST);
    printf("\n");

    printf("请输入待删除的元素的关键字：");
    scanf("%d",&key);
    DeleteBST(BST, key);
    printf("删除成功！删除之后的二叉排序树为：");
    InOrderTraverse(BST);
    printf("\n");

}

