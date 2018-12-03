#include <stdio.h>
#include <malloc.h>

typedef int ElemType;

typedef struct{
    struct BSTNode *lchild;
    struct BSTNode *rchild;
    ElemType data;
    int balance;
}BBTNode, *BBTree;

BBTree CreateBBTree(BBTree *T){//创建二叉树（先序）
    ElemType data;
    int balance;

    scanf("%d，%d ", &data, &balance);//输入：data，balance+空格
    if(data==-1)
        *T=NULL;
    else{
        *T=(BBTNode *)malloc(sizeof(BBTNode));
        if(!(*T)) exit(0);
        (*T)->lchild=CreateBBTree(&((*T)->lchild));
        (*T)->rchild=CreateBBTree(&((*T)->rchild));
        (*T)->data=data;
        (*T)->balance=balance;
    }
    return *T;
}

/*
    设根结点的层次为1，循环遍历平衡二叉树，每遍历一层，高度加1，直到遍历到层数
    最大的子树的叶子结点，所得高度值就是平衡二叉树的高度。遍历原则为当结点的平
    衡因子为0时，任选左右一分支向下遍历；若平衡因子不为0，则当平衡因子等于1时沿
    左分支向下遍历，平衡因子等于-1时沿右分支向下遍历。
*/

int Height(BBTree T){//根据平衡因子计算平衡二叉树的深度
    int count=0;//记录平衡二叉树的深度
    BBTNode *p=T;

    while(p){
        count++;
        if(p->balance>0)//左子树深度大于右子树
            p=p->lchild;
        else
            p=p->rchild;//左子树深度小于等于右子树
    }

    return count;
}

void main(){
    printf("请先创建一棵平衡二叉树（先序；输入格式：data，balance+空格；-1表示空结点）：\n");
    BBTree BBT;

    CreateBBTree(&BBT);
    printf("创建成功！\n");
    printf("该平衡二叉树的高度为：%d", Height(BBT));
}

/*
    假设一棵平衡二叉树的每个结点都标明了平衡因子b，试设计一个算法，求平衡二叉树的高度
*/
