#include <stdio.h>
#include <string.h>
#define MAXSTRLEN 255 //�û�����255���ڶ�����󴮳�
#define OK 1
#define ERROR 0
typedef int Status;
typedef unsigned char SString[MAXSTRLEN+1]; //0�ŵ�Ԫ����ַ����ĳ���

/*�������ַ�������*/
void StrCreat(SString str)
{
    char ch;
    int i=0;
    scanf("%c",&ch);
    while(ch!='#'&&i<MAXSTRLEN)
    {
        i=i+1;
        str[i]=ch;
        scanf("%c",&ch);
    }
    str[i+1]='\0';
    str[0]=i;
}

/*���*/
void StrDisplay(SString str)
{
    int i;
    for(i=1;i<=str[0];i++)
        printf("%c",str[i]);
}

/*���Ӵ�*/
Status SubString(SString Sub, SString str, int pos, int len)
{
    int i;
    int left=str[0]-pos+1;
    if(pos>str[0]||pos<1||len<0)
    {
        printf("�����ַ������ȣ�");
        return ERROR;
    }
    if(len>left) len=left;
    for(i=1;i<=len;i++)
        Sub[i]=str[pos+i-1];
    Sub[len+1]='\0';
    Sub[0]=len;
    return OK;
}

/*�������㣺�ڴ�����s��posλ��ǰ����һ����t*/
Status StrInsert(SString s, int pos, SString t)
{
    int i;
    if(pos>s[0]+1||pos<1)
    {
        printf("����λ�ó�����Χ��");
        return ERROR;
    }
    if(pos+t[0]>MAXSTRLEN)
    {
        for(i=pos;i<=MAXSTRLEN;i++)
            s[i]=t[i-pos+1];
        s[0]=MAXSTRLEN;
    }
    else
    {
        if(s[0]+t[0]<=MAXSTRLEN)
        {
            for(i=s[0];i>=pos;i--)
                s[i+t[0]]=s[i];
            for(i=1;i<=t[0];i++)
                s[pos+i-1]=t[i];
            s[0]=s[0]+t[0];
        }
        else
        {
            for(i=MAXSTRLEN;i>pos+t[0]-1;i--)
                s[i]=s[i-t[0]];
            for(i=1;i<=t[0];i++)
                s[pos+i-1]=t[i];
            s[0]=MAXSTRLEN;
        }
    }
    return OK;
}

/*ɾ�����е�һ���Ӵ�*/
Status StrDelete(SString s, int pos, int num)
{
    int i;
    if(pos>s[0]||pos<1)
    {
        printf("������Χ��");
        return ERROR;
    }
    if(pos+num>s[0])
        s[0]=pos-1;
    else
    {
        for(i=pos+num;i<=s[0];i++)
            s[i-num]=s[i];
        s[0]=s[0]-num;
    }
    return OK;
}

/*������*/
void main(void)
{
    int pos, num, k;
    SString str, s1, Sub;
    do
    {
        printf("\n           1.�����ַ���");
        printf("\n           2.ȡ�Ӵ�");
        printf("\n           3.�����Ӵ�s1");
        printf("\n           4.ɾ���Ӵ�");
        printf("\n           5.��������");
        printf("\n****************************");
        printf("\n����������ѡ��1��2��3��4��5����");
        scanf("%d", &k);
        getchar();
        switch(k)
        {
            case 1:{
                printf("������һ���ַ�����");
                StrCreat(str);
                printf("�ַ���Ϊ��");
                StrDisplay(str);
            }break;

            case 2:{
                printf("�������ַ����Ľ�ȡλ��pos���ַ�������num��");
                scanf("%d %d",&pos, &num);
                SubString(Sub, str, pos, num);
                printf("����ȡ���Ӵ�Ϊ��");
                StrDisplay(Sub);
            }break;

            case 3:{
                printf("�������Ӵ�����λ��pos��");
                scanf("%d",&pos);
                getchar();
                printf("������Ҫ������Ӵ���");
                StrCreat(s1);
                StrInsert(str, pos, s1);
                printf("�������ַ���Ϊ��");
                StrDisplay(str);
            }break;

            case 4:{
                printf("������Ҫɾ���Ӵ��Ŀ�ʼλ��pos���Ӵ�����num��");
                scanf("%d %d",&pos, &num);
                StrDelete(str, pos, num);
                printf("ɾ������ַ���Ϊ��");
                StrDisplay(str);
            }break;
            default:break;
        }
         printf("\n****************************");
    }
    while(k>=1&&k<5);
    printf("\n           �ټ���");
    printf("\n           ������������ء�");
}









