#include <stdio.h>

int Ack(int m, int n){//�ݹ��㷨
    if(m==0) return n+1;
    else{
        if(n==0) return Ack(m-1, 1);
        else     return Ack(m-1, Ack(m, n-1));
    }
}

int Ackman(int m, int n){//�ǵݹ��㷨
    int akm[m][n];

    int i, j;
    for(j=0; j<n; j++)//���ȵõ�Ack(0, n)��ֵ��Ȼ�����ѭ������������ֵ
        akm[0][j]=j+1;

    for(i=1; i<m; i++){
        akm[i][0]=akm[i-1][1];
        for(j=1; j<n; j++)
            akm[i][j]=akm[i-1][akm[i][j-1]];
    }

    return akm[m][n];

}

void main(){
    printf("����Ack(2, 1)\n");
    printf("Ackermann�����ĵݹ��㷨��������%d\n", Ack(2, 1));
    printf("Ackermann�����ķǵݹ��㷨��������%d\n", Ackman(2, 1));
}

/*
    ��֪Ackermann�����������£�
        Ack(m, n)=n+1                    m=0;
                 =Ack(m-1, 1)            m!=0, n=0;
                 =Ack(m-1, Ack(m, n-1)   m!=0, n!=0;
    1. д������Ack(m, n)�ĵݹ��㷨
    2. д������Ack(m, n)�ķǵݹ��㷨
*/
