#include <stdio.h>

typedef struct DuLNode{
	ElemType data;
	struct DuLNode *prior, *next;
}DuLNode, *DuLinkList;

void DuplexSort(DuLinkList L){//对储存在带头结点的双向链表L中的元素进行双向冒泡排序
	int exchange=1;//是否发生交换的标记
	DuLNode *head=L;//双向链表头，向下冒泡开始的结点
	DuLNode *tail=NULL;//双向链表尾，向上冒泡开始的结点
	while(exchange){
		DuLNode *p=head->next;//p是工作指针，指向当前结点
		exchange=0;//假定本趟无交换
		while(p->next!=tail){//向下冒泡，每一趟是一最大元素沉底
			if(p->data>p->next->data){//交换两结点指针，涉及6条链
				DuLNode *temp=p->next;
				exchange=1;//有交换
				p->next=temp->next;
				temp->next->prior=p;//先将结点从链表上摘下
				temp->next=p;
				p->prior->next=temp;//将temp插到结点*p前
				temp->prior=p->prior;
				p->prior=temp;
			}
			else//无交换，指针后移
				p=p->next;
		}

		tail=p;//准备向上气泡
		p=tail->prior;
		while(exchange&&p->prior!=head){//向上冒泡，每一趟有一最小元素冒出
			if(p->data<p->prior->data){//交换两指针，涉及到6条链
				DuLNode *temp=p->prior;
				exchange=1;//有交换
				p->prior=temp->prior;
				temp->prior->next=p;//先将temp从链上摘下
				temp->prior=p;
				p->next->prior=temp;//将temp插在p结点后
				temp->next=p->next;
				p->next=temp;

			}
			else p=p->prior;//无交换，指针前移
		}
		head=p;//准备向下起泡
	}
}

void main(){}

/*
	有n个记录储存在带头结点的双向链表中，利用双向冒泡排序法对其按升序进行排序，
	请写出这种排序的算法。（注：双向冒泡排序即相邻两趟排序向相反方向冒泡）
*/
