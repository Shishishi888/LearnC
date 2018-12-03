#include <stdio.h>

bool Insert(int data){//向散列表中插入关键字为K的记录（链地址法）
    int ant=H(data);
    LNode *p=HT[ant];//找到该散列地址代表的位置

    while(p->next){
        if(p->next->data==data)
            return false;
        p=p->next;
    }

    LNode *s=(LNode *)malloc(sizeof(LNode));
    s->data=data;
    s->next=p->next;
    p->next=s;//将新结点插入链尾
    return true;
}

bool Delete(int data){//删除散列表中关键字为K的记录（链地址法）
    int ant=H(data);
    LNode *p=HT[ant];//找到该散列地址代表的位置

    while(p->next){
        if(p->next->data==data){
            LNode *s=p->next;
            p->next=s->next;
            free(s);//删除该结点
            return true;
        }
        p=p->next;//继续遍历下一个结点
    }

    return false;
}
void main(){
}
/*
    分别写出在散列表中插入和删除关键字为K的一个记录的算法，设散列函数为H，解决冲突的办法为链地址法。
*/
