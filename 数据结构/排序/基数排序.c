#include <stdio.h>
#define MAXNUM_KEY 8//�ؼ������������ֵ
#define RADIX 10//�ؼ��ֻ�������ʱ��ʮ���ƵĻ���
#define MAX_SPACE 10000

typedef struct{
	KeyType keys[MAXNUM_KEY];//�ؼ���
	InfoType otheritems;
	int next;
}SLCell;//��̬����Ľ������

typedef struct{
	SLCell r[MAX_SPACE];//��̬��Ŀ��ÿռ䣬r[0]Ϊͷ���
	int keynum;//��¼�ĵ�ǰ�ؼ��ָ���
	int recnum;//��̬����ĵ�ǰ����
}SLList;//��̬���������

typedef int ArrType[RADIX]//��������

void Distribute(SLCell *r, int i, ArrType *f, ArrType *e){
	//��̬����L��r���м�¼�Ѱ���keys[0],����, keys[i-1]������
	//���㷨����i���ؼ���keys[i]����RADIX���ӱ�ʹͬһ���ӱ��м�¼��keys[i]��ͬ
	//f[0..RADIX-1]��e[0..RADIX-1]�ֱ�ָ������ӱ��еĵ�һ�������һ����¼
	for(j=0; j<RADIX; ++j) f[j]=0;//���ӱ��ʼ��Ϊ�ձ�
	for(p=r[0].next; p; p=r[p].next){
		j=ord(r[p].keys[i]);//ord����¼�е�i���ؼ���ӳ�䵽[0..RADIX-1]
		if(!f[j]) f[j]=p;
		else r[e[j]].next=p;
		e[j]=p;//��p��ָ�Ľ������j���ӱ���
	}
}

void Collect(SLCell *r, int i, ArrType f, ArrType e){
	//���㷨��keys[i]��С����ؽ�f[0..RADIX-1]��ָ�����ӱ��������ӳ�һ������
	//e[0..RADIX]Ϊ�����ӱ��βָ��
	for(j=0; !f[j]; j=succ(j));//�ҵ�һ���ǿ��ӱ�succΪ���̺���
	r[0].next=f[j];//r[0].nextָ���һ���ǿ��ӱ��еĵ�һ�����
	t=e[j];
	while(j<RADIX){
		for(j=succ(j); j<RADIX-1&&!f[j]; j=succ(j));//�ҵ���һ���ǿ��ӱ�
		if(f[j]){//���������ǿ��ӱ�
			r[t].next=f[j];
			t=e[j];
		}
		r[t].next=0;
	}
}

/*��������*/
void RadixSort(SLList *L){
	//L�ǲ��þ�̬�����ʾ��˳���
	//��L����������ʹ��L��Ϊ���ؼ�����С���������̬����L.r[0]Ϊͷ���
	for(i=0; i<L.recnum; ++i)
		L.r[i].next=i+1;
	L.r[L.recnum].next=0;//��L����Ϊ��̬����
	for(i=0; i<L.keynum; ++i){//�����λ�������ζԸ����ؼ��ֽ��з�����ռ�
		Distribute(L.r, i, f, e);//��i�˷���
		Collect(L.r, i, f, e);//��i���ռ�
	}
}


/*
#define BIT_key 8//ָ���ؼ��ֵ�λ��d
#define RADIX 10//ָ���ؼ��ֻ���r

typedef struct RecType{
	char key[BIT_key];//�ؼ�����
	infoType otheritems;
	struct RecType *next;
}SRecord, *f[RADIX], *e[RADIX];//f��e�ֱ�ΪͰ��ͷβָ������

void Radix_sort(SRecord *head){
	int j, k, m;
	SRecord *p, *q, *f[RADIX], *e[RADIX];
	for(j=BIT_key-1; j>=0; j--){//�ؼ��ֵ�ÿһλһ������
		for(k=0; k<RADIX; k++)//ͷβָ�������ʼ��
			f[k]=e[k]=NULL;
		p=head;
		while(p!=NULL){//һ�˻�������
			m=ord(p->key[j])//ȡ�ؼ��ֵĵ�jλ
			if(f[m]==NULL)
				f[m]=p;
			else e[m]->next=p;
			p=p->next;
		}
		head=NULL;//��head��Ϊͷָ������ռ�
		q=head;//q��Ϊ�ռ����βָ��
		for(k=0; k<RADIX; k++){
			if(f[k]!=NULL){//��k�����в��գ����ռ�
				if(head!=NULL)
					q->next=f[k];
				else
					q=e[k];
			}

		}//���һ��������ռ�
		q->next=NULL;//�޸��ռ�βָ��
	}
}
*/

voidmain(){}
