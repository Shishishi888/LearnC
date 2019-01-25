#include <stdio.h>

/*串的定长顺序储存结构*/
#define MAXLEN 255//串的最大长度

typedef struct{
	char ch[MAXLEN+1];//储存串的一维数组
	int length;//串的当前长度
}HString;

/*串的堆式顺序储存结构*/
typedef struct{
	char *ch;//若是非空串，则按串长分配储存区，否则ch为NULL
	int length;//串的当前长度
}HString;

/*串的链式储存结构*/
#define CHUNKSIZE 80//定义块的大小

typedef struct Chunk{
	char ch[CHUNKSIZE];
	struct Chunk *next;
}Chunk;

typedef struct{
	Chunk *head, *tail;//串的头指针和尾指针
	int length;//串的当前长度
}


/*串的模式匹配算法*/
//BF算法
int Index_BF(SString S, SString T, int pos){
	//返回模式T在主串S中第pos个字符开始第一次出现的位置。若不存在，则返回0
	//其中，T非空，1≤pos≤S.length
	int i=pos;//初始化
	int j=1;
	while(i<=S.length&&j<=T.length){//两个串均未比较到串尾
		if(S.ch[i]==T.ch[j]){//继续比较后继字符
			++i;
			++j;
		}
		else{//指针后退重新开始匹配
			i=j-i+2;
			j=1;
		}
	}
	if(j>T.length)//匹配成功
		return i-T.length;
	else//匹配失败
		return 0;

}

//KMP算法
int Index_KMP(SString S, SString T, int pos){
	//利用模式串T的next函数求T在主串S中第pos个字符之后的位置
	//其中，T非空，1≤pos≤S.length
	int i=pos;//初始化
	int j=1;
	while(i<=S.length&&j<=T.length){//两个串均未比较到串尾
		if(j==0||S.ch[i]==T.ch[j]){//继续比较后继字符
			++i;
			++j;
		}
		else
			j=next[j];//模式串向右移动
	}
	if(j>T.length)//匹配成功
		return i-T.length;
	else//匹配失败
		return 0;
}

void get_next(SString T, int next[]){//计算next函数值
	//求模式串T的next函数值并存入数组next
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

void get_nextval(SString T, int next[]){//计算next函数修正值
	//求模式串T的next函数修正值并存入数组nextval
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
