#include <stdio.h>

bool Insert(int data){//��ɢ�б��в���ؼ���ΪK�ļ�¼������ַ����
    int ant=H(data);
    LNode *p=HT[ant];//�ҵ���ɢ�е�ַ�����λ��

    while(p->next){
        if(p->next->data==data)
            return false;
        p=p->next;
    }

    LNode *s=(LNode *)malloc(sizeof(LNode));
    s->data=data;
    s->next=p->next;
    p->next=s;//���½�������β
    return true;
}

bool Delete(int data){//ɾ��ɢ�б��йؼ���ΪK�ļ�¼������ַ����
    int ant=H(data);
    LNode *p=HT[ant];//�ҵ���ɢ�е�ַ�����λ��

    while(p->next){
        if(p->next->data==data){
            LNode *s=p->next;
            p->next=s->next;
            free(s);//ɾ���ý��
            return true;
        }
        p=p->next;//����������һ�����
    }

    return false;
}
void main(){
}
/*
    �ֱ�д����ɢ�б��в����ɾ���ؼ���ΪK��һ����¼���㷨����ɢ�к���ΪH�������ͻ�İ취Ϊ����ַ����
*/
