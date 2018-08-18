#include <stdio.h>
#include <string.h>
#define MAXSTRLEN 255 //用户可在255以内定义最大串长
#define OK 1
#define ERROR 0
typedef int Status;
typedef unsigned char SString[MAXSTRLEN+1]; //0号单元存放字符串的长度

/*生成新字符串函数*/
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

/*输出*/
void StrDisplay(SString str)
{
    int i;
    for(i=1;i<=str[0];i++)
        printf("%c",str[i]);
}

/*求子串*/
Status SubString(SString Sub, SString str, int pos, int len)
{
    int i;
    int left=str[0]-pos+1;
    if(pos>str[0]||pos<1||len<0)
    {
        printf("超过字符串长度！");
        return ERROR;
    }
    if(len>left) len=left;
    for(i=1;i<=len;i++)
        Sub[i]=str[pos+i-1];
    Sub[len+1]='\0';
    Sub[0]=len;
    return OK;
}

/*插入运算：在串对象s的pos位置前插入一个串t*/
Status StrInsert(SString s, int pos, SString t)
{
    int i;
    if(pos>s[0]+1||pos<1)
    {
        printf("插入位置超出范围！");
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

/*删除串中的一个子串*/
Status StrDelete(SString s, int pos, int num)
{
    int i;
    if(pos>s[0]||pos<1)
    {
        printf("超出范围！");
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

/*主函数*/
void main(void)
{
    int pos, num, k;
    SString str, s1, Sub;
    do
    {
        printf("\n           1.生成字符串");
        printf("\n           2.取子串");
        printf("\n           3.插入子串s1");
        printf("\n           4.删除子串");
        printf("\n           5.结束程序");
        printf("\n****************************");
        printf("\n请输入您的选择（1，2，3，4，5）：");
        scanf("%d", &k);
        getchar();
        switch(k)
        {
            case 1:{
                printf("请输入一个字符串：");
                StrCreat(str);
                printf("字符串为：");
                StrDisplay(str);
            }break;

            case 2:{
                printf("请输入字符串的截取位置pos及字符串长度num：");
                scanf("%d %d",&pos, &num);
                SubString(Sub, str, pos, num);
                printf("您所取的子串为：");
                StrDisplay(Sub);
            }break;

            case 3:{
                printf("请输入子串插入位置pos：");
                scanf("%d",&pos);
                getchar();
                printf("请输入要插入的子串：");
                StrCreat(s1);
                StrInsert(str, pos, s1);
                printf("插入后的字符串为：");
                StrDisplay(str);
            }break;

            case 4:{
                printf("请输入要删除子串的开始位置pos及子串长度num：");
                scanf("%d %d",&pos, &num);
                StrDelete(str, pos, num);
                printf("删除后的字符串为：");
                StrDisplay(str);
            }break;
            default:break;
        }
         printf("\n****************************");
    }
    while(k>=1&&k<5);
    printf("\n           再见！");
    printf("\n           按任意键，返回。");
}









