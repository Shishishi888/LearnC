#include <stdio.h>

void Process(int a[], int n){//将整形数列a中的负值元素排在正值元素之前
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
	printf("请输入数组a的元素个数：");
	scanf("%d", &n);

	int a[n];
	printf("请依次输入数组a的元素：");
	for(int i=0; i<n; i++)
		scanf("%d", &a[i]);

	printf("整理前的数组：");
	for(int i=0; i<n; i++)
		printf("%3d", a[i]);
	printf("\n");

	Process(a, n);
	printf("整理后的数组：");
	for(int i=0; i<n; i++)
		printf("%3d", a[i]);
}

/*
	编写算法，对n个关键字取整数值的记录进行整理，以使所有关键字为负值的记录排在关键字为非负值
	的记录之前，要求：
	①采用顺序存储结构，至多使用一个记录的辅助存储空间
	②算法的时间复杂度为O(n)
*/
