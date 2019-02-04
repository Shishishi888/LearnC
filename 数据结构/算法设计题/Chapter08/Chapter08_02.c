#include <stdio.h>

typedef struct DuLNode{
	ElemType data;
	struct DuLNode *prior, *next;
}DuLNode, *DuLinkList;

void DuplexSort(DuLinkList L){//�Դ����ڴ�ͷ����˫������L�е�Ԫ�ؽ���˫��ð������
	int exchange=1;//�Ƿ��������ı��
	DuLNode *head=L;//˫������ͷ������ð�ݿ�ʼ�Ľ��
	DuLNode *tail=NULL;//˫������β������ð�ݿ�ʼ�Ľ��
	while(exchange){
		DuLNode *p=head->next;//p�ǹ���ָ�룬ָ��ǰ���
		exchange=0;//�ٶ������޽���
		while(p->next!=tail){//����ð�ݣ�ÿһ����һ���Ԫ�س���
			if(p->data>p->next->data){//���������ָ�룬�漰6����
				DuLNode *temp=p->next;
				exchange=1;//�н���
				p->next=temp->next;
				temp->next->prior=p;//�Ƚ�����������ժ��
				temp->next=p;
				p->prior->next=temp;//��temp�嵽���*pǰ
				temp->prior=p->prior;
				p->prior=temp;
			}
			else//�޽�����ָ�����
				p=p->next;
		}

		tail=p;//׼����������
		p=tail->prior;
		while(exchange&&p->prior!=head){//����ð�ݣ�ÿһ����һ��СԪ��ð��
			if(p->data<p->prior->data){//������ָ�룬�漰��6����
				DuLNode *temp=p->prior;
				exchange=1;//�н���
				p->prior=temp->prior;
				temp->prior->next=p;//�Ƚ�temp������ժ��
				temp->prior=p;
				p->next->prior=temp;//��temp����p����
				temp->next=p->next;
				p->next=temp;

			}
			else p=p->prior;//�޽�����ָ��ǰ��
		}
		head=p;//׼����������
	}
}

void main(){}

/*
	��n����¼�����ڴ�ͷ����˫�������У�����˫��ð�����򷨶��䰴�����������
	��д������������㷨����ע��˫��ð���������������������෴����ð�ݣ�
*/
