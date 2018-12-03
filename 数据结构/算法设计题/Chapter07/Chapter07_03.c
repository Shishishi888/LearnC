#include <stdio.h>
#include <malloc.h>

typedef struct{
    struct BSTNode *lchild;
    struct BSTNode *rchild;
    int data;
}BSTNode, *BSTree;

void InsertBST(BSTree *T, int e){//���½��������������
    if(!*T){                                                              //�ҵ�����λ�ã��ݹ����{
        BSTNode *S=(BSTNode *)malloc(sizeof(BSTNode));                    //�����½��*S
        S->lchild=NULL;                                                    //�½��*S��ΪҶ�ӽ��
        S->data=e;                                                        //�½�����������Ϊe
        S->rchild=NULL;
        *T=S;                                                     //���½��*S���ӵ����ҵ��Ĳ���λ��
    }
    else if(e<(*T)->data)                                         //��*S����������
        InsertBST(&((*T)->lchild), e);
    else if(e>(*T)->data)                                         //��*S����������
        InsertBST(&((*T)->rchild), e);
}


void CreatBST(BSTree *T){//��������������
    *T=NULL;
    int e;
    int i=1;
    printf("����������������ĵ�%d��Ԫ�أ�",i);
    scanf("%d",&e);
    while(e!=-1)
    {
        InsertBST(T, e);
        i++;
        printf("����������������ĵ�%d��Ԫ�أ�",i);
        scanf("%d",&e);
    }
}

void PrintAllX(BSTree T, int x){//��С���������������������������ֵ��x�Ľ��
    if(T){
        PrintAllX(T->lchild, x);
        if(T->data>=x) printf("%d ", T->data);
        PrintAllX(T->rchild, x);
    }
}

/*
    ���ȴӸ���㿪ʼ���ң��ҵ���ֵС��x�Ľ��󣬽�����˫�׶Ͽ������
    ������ֵС��x���������������ҵ�һ�����ڵ���x�Ľ�㣬�ҵ���������
    ͬ��������������Ķ�����������
*/
/*
void Print(BSTree T){
    if(T){
        Print(T->lchild);
        printf("%d ", T->data);
        Print(T->rchild);
    }
}

void PrintAllX(BSTree T, int x){//��С���������������������������ֵ��x�Ľ��
    BSTNode *p=T;

    if(p){
        while(p&&p->data<x)//���ҷ�֧���£��ҵ���һ��ֵ��x�Ľ��
            p=p->rchild;
        T=p;

        if(p){
            BSTNode *f=p;
            p=p->lchild;
            while(p&&p->data>=x){//�����֧���£��ҵ���һ��ֵ<x�Ľ��
                f=p;//f��p��˫�׽���ָ�룬��ָ���һ��ֵ��x�Ľ��
                p=p->lchild;
            }

            if(p)
                f->lchild=NULL;//˫�����һ��ֵ<x�Ľ��Ͽ�
            Print(T);
        }
    }
}
*/

void main(){

    printf("���ȴ���һ�ö�����������\n");
    BSTree BST;
    CreatBST(&BST);
    printf("�����ɹ���\n");

    int x;
    printf("������x��ֵ��");
    scanf("%d", &x);

    printf("��С���������������������������ֵ��x�Ľ�㣺");
    PrintAllX(BST, x);
}

/*
    ��֪�������������ö���������ṹ��������ָ��ΪT�������ĽṹΪ(lchild, data, rchild)��
    ����lchild��rchild�ֱ�ָ��ý������Һ��ӵ�ָ�룬data���Ž���������Ϣ����д���ݹ���
    ������С���������������������������ֵ��x�Ľ������ݡ�Ҫ�����ҵ���һ�����������Ľ�����
    ��������������������Ľ�㡣
*/
