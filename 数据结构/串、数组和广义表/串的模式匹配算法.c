#include <stdio.h>

/*���Ķ���˳�򴢴�ṹ*/
#define MAXLEN 255//������󳤶�

typedef struct{
	char ch[MAXLEN+1];//���洮��һά����
	int length;//���ĵ�ǰ����
}HString;

/*���Ķ�ʽ˳�򴢴�ṹ*/
typedef struct{
	char *ch;//���Ƿǿմ����򰴴������䴢����������chΪNULL
	int length;//���ĵ�ǰ����
}HString;

/*������ʽ����ṹ*/
#define CHUNKSIZE 80//�����Ĵ�С

typedef struct Chunk{
	char ch[CHUNKSIZE];
	struct Chunk *next;
}Chunk;

typedef struct{
	Chunk *head, *tail;//����ͷָ���βָ��
	int length;//���ĵ�ǰ����
}


/*����ģʽƥ���㷨*/
//BF�㷨
int Index_BF(SString S, SString T, int pos){
	//����ģʽT������S�е�pos���ַ���ʼ��һ�γ��ֵ�λ�á��������ڣ��򷵻�0
	//���У�T�ǿգ�1��pos��S.length
	int i=pos;//��ʼ��
	int j=1;
	while(i<=S.length&&j<=T.length){//��������δ�Ƚϵ���β
		if(S.ch[i]==T.ch[j]){//�����ȽϺ���ַ�
			++i;
			++j;
		}
		else{//ָ��������¿�ʼƥ��
			i=j-i+2;
			j=1;
		}
	}
	if(j>T.length)//ƥ��ɹ�
		return i-T.length;
	else//ƥ��ʧ��
		return 0;

}

//KMP�㷨
int Index_KMP(SString S, SString T, int pos){
	//����ģʽ��T��next������T������S�е�pos���ַ�֮���λ��
	//���У�T�ǿգ�1��pos��S.length
	int i=pos;//��ʼ��
	int j=1;
	while(i<=S.length&&j<=T.length){//��������δ�Ƚϵ���β
		if(j==0||S.ch[i]==T.ch[j]){//�����ȽϺ���ַ�
			++i;
			++j;
		}
		else
			j=next[j];//ģʽ�������ƶ�
	}
	if(j>T.length)//ƥ��ɹ�
		return i-T.length;
	else//ƥ��ʧ��
		return 0;
}

void get_next(SString T, int next[]){//����next����ֵ
	//��ģʽ��T��next����ֵ����������next
	int i=1;
	next[1]=0;
	int j=0;
	while(i<T.length){
		if(j==0||T.chi[i]==T.ch[j]){
			++i;
			++j;
			next[i]=j;
		}
		else
			j=next[j];
	}
}

void get_nextval(SString T, int next[]){//����next��������ֵ
	//��ģʽ��T��next��������ֵ����������nextval
	int i=1;
	nextval[1]=0;
	int j=0;
	while(i<T.length){
		if(j==0||T.chi[i]==T.ch[j]){
			++i;
			++j;
			if(T.ch[i]!=T.ch[j])
				nextval[i]=j;
			else
				nextval[i]=nextval[j];
		}
		else
			j=nextval[j];
	}
}
