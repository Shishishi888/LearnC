#include <stdio.h>
typedef int ElemType;

int Search(ElemType r[], int low, int high, ElemType key){
	while(low<high){
		while(low<=high&&r[high]>key)
			high--;//���Ҳ࿪ʼ�ҵ�һ�������ڹؼ��ֵļ�¼����λ��Ϊhigh
		if(r[high]==key)
			return high;
		while(low<=high&&r[low]<key)
			low++;//����࿪ʼ�ҵ�һ����С�ڹؼ��ֵļ�¼����λ��Ϊlow
		if(r[low]==key)
			return low;
	}
	printf("not find");
	return 0;
}
void main(){
	int n;
	printf("����������r��Ԫ�ظ�����");
	scanf("%d", &n);

	int r[n+1];
	printf("��������������a��Ԫ�أ�");
	for(int i=1; i<n+1; i++)
		scanf("%d", &r[i]);

	int key;
	printf("������Ҫ���ҵ�Ԫ��key��");
	scanf("%d", &key);

	int low=1;
	int high=n;

	int location=Search(r, low, high, key);
	if(location)
		printf("Ԫ��e������r�е�λ��Ϊ��%d", location);
}

/*
	��������������㷨˼�룬��һ������ļ�¼�в��Ҹ����ؼ���ֵ����key�ļ�¼��
	������¼���������r[1...n]�С������ҳɹ���������ü�¼��r�����е�λ��
	����ֵ��������ʾ��not found����Ϣ�����Ҫ˵���㷨˼�벢��д�㷨��
*/
