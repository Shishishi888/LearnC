#include <stdio.h>
#define MAXNUM_KEY 8//关键字项数的最大值
#define RADIX 10//关键字基数，此时是十进制的基数
#define MAX_SPACE 10000

typedef struct{
	KeyType keys[MAXNUM_KEY];//关键字
	InfoType otheritems;
	int next;
}SLCell;//静态链表的结点类型

typedef struct{
	SLCell r[MAX_SPACE];//静态表的可用空间，r[0]为头结点
	int keynum;//记录的当前关键字个数
	int recnum;//静态链表的当前长度
}SLList;//静态链表的类型

typedef int ArrType[RADIX]//数组类型

void Distribute(SLCell *r, int i, ArrType *f, ArrType *e){
	//静态链表L的r域中记录已按（keys[0],……, keys[i-1]）有序
	//本算法按第i个关键字keys[i]建立RADIX个子表，使同一个子表中记录的keys[i]相同
	//f[0..RADIX-1]和e[0..RADIX-1]分别指向各个子表中的第一个和最后一个记录
	for(j=0; j<RADIX; ++j) f[j]=0;//各子表初始化为空表
	for(p=r[0].next; p; p=r[p].next){
		j=ord(r[p].keys[i]);//ord将记录中第i个关键字映射到[0..RADIX-1]
		if(!f[j]) f[j]=p;
		else r[e[j]].next=p;
		e[j]=p;//将p所指的结点插入第j个子表中
	}
}

void Collect(SLCell *r, int i, ArrType f, ArrType e){
	//本算法按keys[i]自小到大地将f[0..RADIX-1]所指各个子表依次链接成一个链表
	//e[0..RADIX]为各个子表的尾指针
	for(j=0; !f[j]; j=succ(j));//找第一个非空子表，succ为求后继函数
	r[0].next=f[j];//r[0].next指向第一个非空子表中的第一个结点
	t=e[j];
	while(j<RADIX){
		for(j=succ(j); j<RADIX-1&&!f[j]; j=succ(j));//找到下一个非空子表
		if(f[j]){//链接两个非空子表
			r[t].next=f[j];
			t=e[j];
		}
		r[t].next=0;
	}
}

/*基数排序*/
void RadixSort(SLList *L){
	//L是采用静态链表表示的顺序表
	//对L做基数排序，使得L成为按关键字自小到大的有序静态链表，L.r[0]为头结点
	for(i=0; i<L.recnum; ++i)
		L.r[i].next=i+1;
	L.r[L.recnum].next=0;//将L改造为静态链表
	for(i=0; i<L.keynum; ++i){//按最低位优先依次对各个关键字进行分配和收集
		Distribute(L.r, i, f, e);//第i趟分配
		Collect(L.r, i, f, e);//第i趟收集
	}
}


/*
#define BIT_key 8//指定关键字的位数d
#define RADIX 10//指定关键字基数r

typedef struct RecType{
	char key[BIT_key];//关键字域
	infoType otheritems;
	struct RecType *next;
}SRecord, *f[RADIX], *e[RADIX];//f，e分别为桶的头尾指针数组

void Radix_sort(SRecord *head){
	int j, k, m;
	SRecord *p, *q, *f[RADIX], *e[RADIX];
	for(j=BIT_key-1; j>=0; j--){//关键字的每一位一趟排序
		for(k=0; k<RADIX; k++)//头尾指针数组初始化
			f[k]=e[k]=NULL;
		p=head;
		while(p!=NULL){//一趟基数排序
			m=ord(p->key[j])//取关键字的第j位
			if(f[m]==NULL)
				f[m]=p;
			else e[m]->next=p;
			p=p->next;
		}
		head=NULL;//以head作为头指针进行收集
		q=head;//q作为收集后的尾指针
		for(k=0; k<RADIX; k++){
			if(f[k]!=NULL){//第k个队列不空，则收集
				if(head!=NULL)
					q->next=f[k];
				else
					q=e[k];
			}

		}//完成一趟排序的收集
		q->next=NULL;//修改收集尾指针
	}
}
*/

voidmain(){}
