#include <stdio.h>
#include <string.h>
#define m 20//ɢ�б�ĳ���
#define NULLKEY -1
#define NULLINFO "NULL"

typedef int KeyType;
typedef char InfoType[20];

typedef struct
{
    KeyType key;
    InfoType otherInfo;
}HashTable[m];


/*ɢ�б�Ĳ���*/
void InsertHash(HashTable HT, KeyType key, InfoType otherInfo)
{//��ɢ�б��в���ؼ���Ϊkey����ϢΪotherInfo��Ԫ��
 //���ŵ�ַ��

    int H0=H(key);//����ɢ�к���H(key)����ɢ�е�ַ

    if(HT[H0].key==NULLKEY)//����ԪH0Ϊ�գ���Ҫ�����Ԫ�ز���H0
    {
        HT[H0].key=key;
        strcpy(HT[H0].otherInfo, otherInfo);
    }
    else//����ԪH0��Ϊ�գ���������ͻ
    {
        for(int i=1; i<m; i++)
        {
            int Hi=(H0+i)%m;//��������̽����������һ��ɢ�е�ַH1
            if(HT[Hi].key==NULLKEY)//����ԪHiΪ�գ���Ҫ�����Ԫ�ز���Hi
            {
                HT[Hi].key=key;
                strcpy(HT[Hi].otherInfo, otherInfo);
                break;
            }
        }
    }
}

/*ɢ�б�Ĵ���*/
void CreatHT(HashTable HT)
{
    if(HT)
    {
        for(int i=0; i<m; i++)
        {
            HT[i].key=NULLKEY;
            strcpy(HT[i].otherInfo, NULLINFO);
        }

        printf("����ɢ�б��в���Ԫ�أ��ؼ��֣���Ϣ�����������Ԫ�صĹؼ���Ϊ-1ʱ��ֹͣ����\n");

        KeyType key;
        InfoType otherInfo;
        for(int i=0; i<m; i++)
        {
            printf("������%d��Ԫ�أ�", i+1);
            scanf("%d��%s", &key, &otherInfo);
            if(key==-1)
                break;
            InsertHash(HT, key, otherInfo);
        }
    }
}

/*ɢ�б�Ĳ���*/
int SearchHash(HashTable HT, KeyType key)
{//��ɢ�б��в��ҹؼ���Ϊkey��Ԫ�أ�������ɹ�������ɢ�б�ĵ�Ԫ��ţ����򷵻�-1
 //���ŵ�ַ��

    int H0=H(key);//����ɢ�к���H(key)����ɢ�е�ַ

    if(HT[H0].key==NULLKEY)//����ԪH0Ϊ�գ��������ҵ�Ԫ�ز�����
        return -1;
    else if(HT[H0].key==key)//����ԪH0�е�Ԫ�صĹؼ���Ϊkey������ҳɹ�
        return H0;
    else
    {
        for(int i=1; i<m; ++i)
        {
            int Hi=(H0+i)%m;//��������̽����������һ��ɢ�е�ַH1
            if(HT[Hi].key==NULLKEY)//����ԪHiΪ�գ��������ҵ�Ԫ�ز�����
                return -1;
            else if(HT[Hi].key==key)//����ԪH0�е�Ԫ�صĹؼ���Ϊkey������ҳɹ�
                return Hi;
        }
    }

    return -1;//����ʧ��
}

int H(KeyType key)//ɢ�к���
{
    return key%(m-3);
}

//�������a��main()����֮����������a��������Ϊȫ�ֱ���
//ϵͳ�ڱ���ʱ�Ὣa�е�ÿ�������Ա���ʼ��Ϊ0
//������a��main()����֮����������a��������Ϊ�ֲ�����
//��ĳ�������Աδ��ֵʱ���ó�Ա��ֵ�Ȳ���0��Ҳ����NULL��Ҳ����'\0'�������ж����Ƿ�Ϊ���ա�

void main()
{
    HashTable HT;
    CreatHT(HT);
    printf("ɢ�б����ɹ���\n");
    printf("��ɢ�б�ı���������ؼ��֣���Ϣ��Ϊ��\n");
    for(int i=0; i<m; i++)
        //if(HT[i].key!=-1)
            printf("%d��%s  ", HT[i].key, HT[i].otherInfo);
    printf("\n");

    KeyType key;
    printf("����������Ҫ���ҵ�Ԫ�صĹؼ��֣�");
    scanf("%d", &key);
    printf("\n");

    if(SearchHash(HT, key)!=-1)
    {
        printf("���ҳɹ�����Ԫ����ɢ�б��е�λ��Ϊ��%d\n", SearchHash(HT, key));
        printf("          ��Ԫ�ص���ϢΪ��%s", HT[SearchHash(HT, key)].otherInfo);
    }
    else
        printf("����ʧ�ܣ���ɢ�б���û����Ҫ���ҵ�Ԫ�أ�");
}
