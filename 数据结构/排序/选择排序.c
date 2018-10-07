#include <stdio.h>
#include <malloc.h>
#define MAXSIZE 20                //˳������󳤶�

typedef struct{
    int key;                      //�ؼ���
    char otherinfo[20];           //������Ϣ
}RedType;                         //��¼����

typedef struct{
    RedType r[MAXSIZE+1];         //r[0]���û������ڱ�
    int length;                   //˳�����
}SqList;                          //˳�������

/*��ѡ������*/
void SelectSort(SqList *L){
    int i;
    for(i=1; i<L->length; i++){
        int k=i;
        int j;
        for(j=i+1; j<=L->length; j++){
            if(L->r[j].key<L->r[k].key)
                k=j;                            //kָ����������йؼ�����С�ļ�¼
        }
        if(k!=i){
            RedType t=L->r[i];
            L->r[i]=L->r[k];
            L->r[k]=t;
        }
    }
}

/*������*/
void HeapAdjust(SqList *L, int s, int m){       //ɸѡ��������
                                                //����r[s+1...m]�Ѿ��Ƕѣ���r[s...m]����Ϊ��r[s]Ϊ���Ĵ����
    RedType rc=L->r[s];
    int j;
    for(j=2*s; j<=m; j*=2){
        if(j<m&&L->r[j].key<L->r[j+1].key)
            j++;                                //jΪk�ϴ��¼���±�
        if(rc.key>=L->r[j].key)                 //�ж���r[s]Ϊ���Ķ������Ƿ�Ϊ�ѣ���������r[s]�ļ�¼���ڻ���ڽϴ��ӽ��r[j]�ļ�¼������r[s]Ϊ���Ķ�����Ϊ��,�������������ѭ��
            break;
        L->r[s]=L->r[j];                        //�������r[s]�滻Ϊ�ϴ��ӽ��r[j]
        s=j;                                    //sָ��j������forѭ�����������µ�r[s]Ϊ���Ķ�
    }
    L->r[s]=rc;
}

void CreatHeap(SqList *L){                      //������
    int n=L->length;
    int i;
    for(i=n/2; i>0; i--)
        HeapAdjust(L, i, n);
}

void HeapSort(SqList *L){                       //������
    CreatHeap(L);
    int i;
    for(i=L->length; i>1; i--){
        RedType x=L->r[1];
        L->r[1]=L->r[i];
        L->r[i]=x;
        HeapAdjust(L, 1, i-1);
    }
}

void main(){
SqList *L=(SqList *)malloc(sizeof(SqList));
    L->r[1].key=5;
    L->r[2].key=6;
    L->r[3].key=7;
    L->r[4].key=4;
    L->r[5].key=9;
    L->r[6].key=9;
    L->r[7].key=44;
    L->r[8].key=32;
    L->r[9].key=12;
    L->length=9;

    SqList *temp=(SqList *)malloc(sizeof(SqList));
    temp->length=L->length;

    printf("              ԭʼ����Ϊ��");
    for(int i=1; i<=L->length; i++)
        printf("%3d",L->r[i].key);
    printf("\n");

    for(int i=1; i<=temp->length; i++)
        temp->r[i]=L->r[i];
    SelectSort(temp);
    printf("��ѡ������������Ϊ��");
    for(int i=1; i<=temp->length; i++)
        printf("%3d",temp->r[i].key);
    printf("\n");

    for(int i=1; i<=temp->length; i++)
        temp->r[i]=L->r[i];
    HeapSort(temp);
    printf("      ������������Ϊ��");
    for(int i=1; i<=temp->length; i++)
        printf("%3d",temp->r[i].key);
     printf("\n");
}
