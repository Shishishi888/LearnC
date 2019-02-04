#include <stdio.h>
typedef int ElemType;

int Search(ElemType r[], int low, int high, ElemType key){
	while(low<high){
		while(low<=high&&r[high]>key)
			high--;//从右侧开始找第一个不大于关键字的记录，其位置为high
		if(r[high]==key)
			return high;
		while(low<=high&&r[low]<key)
			low++;//从左侧开始找第一个不小于关键字的记录，其位置为low
		if(r[low]==key)
			return low;
	}
	printf("not find");
	return 0;
}
void main(){
	int n;
	printf("请输入数组r的元素个数：");
	scanf("%d", &n);

	int r[n+1];
	printf("请依次输入数组a的元素：");
	for(int i=1; i<n+1; i++)
		scanf("%d", &r[i]);

	int key;
	printf("请输入要查找的元素key：");
	scanf("%d", &key);

	int low=1;
	int high=n;

	int location=Search(r, low, high, key);
	if(location)
		printf("元素e在数组r中的位置为：%d", location);
}

/*
	借助快速排序的算法思想，在一组无序的记录中查找给定关键字值等于key的记录。
	设此组记录存放于数组r[1...n]中。若查找成功，则输出该记录在r数组中的位置
	及其值，否则显示“not found”信息。请简要说明算法思想并编写算法。
*/
