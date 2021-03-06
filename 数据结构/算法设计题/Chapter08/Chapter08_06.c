#include <stdio.h>

typedef char ElemType[20];

typedef struct{
	int key;
	ElemType info;
}RecType;

void CountSort(RecType a[], RecType b[], int n){
	//计数排序算法，将包括n个数据的数组a中的记录排序后放入数组b中
	for(int i=0; i<n; i++){//针对数组中的每个关键字
		int c=0;
		for(int j=0; j<n; j++)//统计关键字比当前关键字小的元素个数
			if(a[j].key<a[i].key)
				c++;
		b[c]=a[i];//根据比当前关键字小的元素个数将当前的关键字存放在数组b中
	}
}
void main(){
	int n;
	printf("请输入待排序元素的个数：");
	scanf("%d", &n);

	RecType a[n];
	printf("请依次输入待排序元素的关键字：");
	for(int i=0; i<n; i++)
		scanf("%d", &a[i].key);

	RecType b[n];
	CountSort(a, b, n);
	printf("计数排序的排序结果为：");
	for(int i=0; i<n; i++)
		printf("%3d", b[i].key);

}

/*
	有一种简答的排序算法，叫做计数排序。这种排序算法对一个待排序的表进行排序，并将排序结果
	存放在另一个新的表中。必须注意的是，表中所有待排序的关键字互不相同，计数排序算法对表中
	的每个记录，扫描待排序的表一趟，统计表中有多少个记录的关键字比该记录的关键字小。假设针
	对某一个记录，统计出的计数值为c，那么，这个记录在新的有序表中的适合的存放位置即为c。
	①给出适合计数排序的顺序表定义；
	②编写实现计数排序的算法；
*/
