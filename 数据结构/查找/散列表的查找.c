#include <stdio.h>
#include <string.h>
#define m 20//散列表的长度
#define NULLKEY -1
#define NULLINFO "NULL"

typedef int KeyType;
typedef char InfoType[20];

typedef struct
{
    KeyType key;
    InfoType otherInfo;
}HashTable[m];


/*散列表的插入*/
void InsertHash(HashTable HT, KeyType key, InfoType otherInfo)
{//在散列表中插入关键字为key，信息为otherInfo的元素
 //开放地址法

    int H0=H(key);//根据散列函数H(key)计算散列地址

    if(HT[H0].key==NULLKEY)//若单元H0为空，则将要插入的元素插入H0
    {
        HT[H0].key=key;
        strcpy(HT[H0].otherInfo, otherInfo);
    }
    else//若单元H0不为空，即发生冲突
    {
        for(int i=1; i<m; i++)
        {
            int Hi=(H0+i)%m;//按照线性探索法计算下一个散列地址H1
            if(HT[Hi].key==NULLKEY)//若单元Hi为空，则将要插入的元素插入Hi
            {
                HT[Hi].key=key;
                strcpy(HT[Hi].otherInfo, otherInfo);
                break;
            }
        }
    }
}

/*散列表的创建*/
void CreatHT(HashTable HT)
{
    if(HT)
    {
        for(int i=0; i<m; i++)
        {
            HT[i].key=NULLKEY;
            strcpy(HT[i].otherInfo, NULLINFO);
        }

        printf("请向散列表中插入元素（关键字，信息），当插入的元素的关键字为-1时，停止插入\n");

        KeyType key;
        InfoType otherInfo;
        for(int i=0; i<m; i++)
        {
            printf("请插入第%d个元素：", i+1);
            scanf("%d，%s", &key, &otherInfo);
            if(key==-1)
                break;
            InsertHash(HT, key, otherInfo);
        }
    }
}

/*散列表的查找*/
int SearchHash(HashTable HT, KeyType key)
{//在散列表中查找关键字为key的元素，若插入成功，返回散列表的单元标号，否则返回-1
 //开放地址法

    int H0=H(key);//根据散列函数H(key)计算散列地址

    if(HT[H0].key==NULLKEY)//若单元H0为空，则所查找的元素不存在
        return -1;
    else if(HT[H0].key==key)//若单元H0中的元素的关键字为key，则查找成功
        return H0;
    else
    {
        for(int i=1; i<m; ++i)
        {
            int Hi=(H0+i)%m;//按照线性探索法计算下一个散列地址H1
            if(HT[Hi].key==NULLKEY)//若单元Hi为空，则所查找的元素不存在
                return -1;
            else if(HT[Hi].key==key)//若单元H0中的元素的关键字为key，则查找成功
                return Hi;
        }
    }

    return -1;//查找失败
}

int H(KeyType key)//散列函数
{
    return key%(m-3);
}

//如果数组a在main()函数之外声明，则a将被处理为全局变量
//系统在编译时会将a中的每个数组成员会初始化为0
//若数组a在main()函数之内声明，则a将被处理为局部变量
//当某个数组成员未赋值时，该成员的值既不是0，也不是NULL，也不是'\0'，难以判断其是否为“空”

void main()
{
    HashTable HT;
    CreatHT(HT);
    printf("散列表创建成功！\n");
    printf("该散列表的遍历结果（关键字，信息）为：\n");
    for(int i=0; i<m; i++)
        //if(HT[i].key!=-1)
            printf("%d，%s  ", HT[i].key, HT[i].otherInfo);
    printf("\n");

    KeyType key;
    printf("请输入您想要查找的元素的关键字：");
    scanf("%d", &key);
    printf("\n");

    if(SearchHash(HT, key)!=-1)
    {
        printf("查找成功！该元素在散列表中的位置为：%d\n", SearchHash(HT, key));
        printf("          该元素的信息为：%s", HT[SearchHash(HT, key)].otherInfo);
    }
    else
        printf("查找失败！该散列表中没有您要查找的元素！");
}
