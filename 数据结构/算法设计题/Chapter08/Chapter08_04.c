#include <stdio.h>

void Process(int a[], int n){//����������a�еĸ�ֵԪ��������ֵԪ��֮ǰ
	int low=0;
	int high=n-1;
	while(low<high){
		while(a[low]<0)
			low++;
		while(a[high]>0)
			high--;
		if(low<high){
			int temp=a[low];
			a[low]=a[high];
			a[high]=temp;
			low++;
			high--;
		}
	}
}

void main(){
	int n;
	printf("����������a��Ԫ�ظ�����");
	scanf("%d", &n);

	int a[n];
	printf("��������������a��Ԫ�أ�");
	for(int i=0; i<n; i++)
		scanf("%d", &a[i]);

	printf("����ǰ�����飺");
	for(int i=0; i<n; i++)
		printf("%3d", a[i]);
	printf("\n");

	Process(a, n);
	printf("���������飺");
	for(int i=0; i<n; i++)
		printf("%3d", a[i]);
}

/*
	��д�㷨����n���ؼ���ȡ����ֵ�ļ�¼����������ʹ���йؼ���Ϊ��ֵ�ļ�¼���ڹؼ���Ϊ�Ǹ�ֵ
	�ļ�¼֮ǰ��Ҫ��
	�ٲ���˳��洢�ṹ������ʹ��һ����¼�ĸ����洢�ռ�
	���㷨��ʱ�临�Ӷ�ΪO(n)
*/
