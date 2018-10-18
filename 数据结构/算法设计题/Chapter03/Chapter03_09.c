#include <stdio.h>

int Ack(int m, int n){//递归算法
    if(m==0) return n+1;
    else{
        if(n==0) return Ack(m-1, 1);
        else     return Ack(m-1, Ack(m, n-1));
    }
}

int Ackman(int m, int n){//非递归算法
    int akm[m][n];

    int i, j;
    for(j=0; j<n; j++)//首先得到Ack(0, n)的值，然后逐个循环计算其他的值
        akm[0][j]=j+1;

    for(i=1; i<m; i++){
        akm[i][0]=akm[i-1][1];
        for(j=1; j<n; j++)
            akm[i][j]=akm[i-1][akm[i][j-1]];
    }

    return akm[m][n];

}

void main(){
    printf("计算Ack(2, 1)\n");
    printf("Ackermann函数的递归算法计算结果：%d\n", Ack(2, 1));
    printf("Ackermann函数的非递归算法计算结果：%d\n", Ackman(2, 1));
}

/*
    已知Ackermann函数定义如下：
        Ack(m, n)=n+1                    m=0;
                 =Ack(m-1, 1)            m!=0, n=0;
                 =Ack(m-1, Ack(m, n-1)   m!=0, n!=0;
    1. 写出计算Ack(m, n)的递归算法
    2. 写出计算Ack(m, n)的非递归算法
*/
