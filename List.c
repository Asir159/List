#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <string.h>

#define MAXSIZE 20

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

typedef int Elmtype;		//Ԫ������
typedef int Status;			//״̬�뺯��

typedef struct SqList
{
	Elmtype data[MAXSIZE];
	int len;
}SqList;

/*	  ��ʼ�����Ա�		*/
Status InitList(SqList* L)
{
	//memset(L->data,0,sizeof(int)*MAXSIZE);
	L->len = 0;

	return OK;
}

Status ListInsert(SqList* L, int i, Elmtype e)
{
	int j;
	if (L->len >= MAXSIZE)	    //˳�������
		return ERROR;
	if (i<1 || i >L->len+1)		//��i��λ��С�����Ա�ĳ��Ȼ��ߴ��ڵĳ���
		return ERROR;
	//�ڵ�i��λ�ò���Ԫ��
	if (i < L->len)  //������ڱ�β
	{
		for (j = L->len-1; j >= i-1; j--)		//����Ԫ������ƶ�һ��
		{
			L->data[j + 1] = L->data[j];
		}
	}
	L->data[i-1] = e;							//������Ԫ��
	L->len++;								//���ȼ�һ

	return OK;
}

/*	  ����dataԪ��	  */
Status vist(Elmtype e)					
{
	printf("%d  ", e);
	return OK;
}

/*		����data����			*/	
Status ListTraverse(SqList L)
{
	int i;
	for (i = 0; i < L.len; i++)
	{
		vist(L.data[i]);
	}
	printf("\n");
}

/*	�鿴���Ƿ�Ϊ��	*/
Status ListEmpty(SqList L)
{
	if (L.len == 0)
		return TRUE;
	return FALSE;
}

/*		�������Ϊ�ձ�		*/	
Status ClearList(SqList* L)
{
	L->len = 0;			//ֻ��Ҫ�ѱ��ĳ���������, ���ݺ����ɸ���
	return OK;
}

/*			��ȡָ����Ԫ��			*/	
Status GetElm(SqList L, int i, Elmtype* e)
{
	if (i<1 || i>L.len || L.len == 0)			//��i��/С�ڱ���,���ĳ���Ϊ0
		return ERROR;							//�׳�����
	*e = L.data[i-1];					//Ԫ�ظ���
	return OK;
}

int ListLength(SqList L)
{
	return L.len;
}

Status ListDelete(SqList* L, int i, Elmtype* e)
{
	int j;
	if (L->len == 0)		//����Ϊ��
		return ERROR;
	if (i<0 || i>L->len)	//λ�ò���С�ںʹ��ڳ���
		return ERROR;
	*e = L->data[i-1];
	if (i < L->len)						//������ڱ�β
	{
		for (j = i; j < L->len - 1; j++)
		{
			L->data[j] = L->data[j + 1];
		}
	}

	L->len--;
	return OK;
}

/*		Ѱ�ұ����Ƿ��з��ϵ�Ԫ��		*/
/*            û�з���0             */
Status LocateElem(SqList L, Elmtype e)
{
	int i;
	if (L.len == 0)
		return 0;
	for (i = 0; i < L.len; i++)
	{
		if (L.data[i] == e)
		{
			break;
		}
	}
	if (i >= L.len)
		return 0;

	return i + 1;
}

/*��������Lb�е�����La�е�Ԫ�ز����La��*/
Status UnionL(SqList* La, SqList Lb)
{
	int i;
	Elmtype e;
	int len_La, len_Lb;

	if (La->len == 0 || Lb.len == 0)			//����λ�ձ�
		return ERROR;

	len_La = ListLength(*La);
	len_Lb = ListLength(Lb);

	for (i = 1; i < len_Lb; i++)
	{
		//��ȡLb��Ԫ��
		GetElm(Lb, i, &e);
		if(!LocateElem(*La,e))				//Ѱ��La�в����ں�e��ͬ��Ԫ��
		ListInsert(La,++len_La,e);			//La�ڱ�β�в���Lb
	}
}

int main()
{
	int i,j,len;
	Elmtype e;
	SqList L,Lb;
	Status sta;
	//��ʼ�����
	sta = InitList(&L);
	printf("��ʼ��L��len�ĳ���:%d\n",L.len);
	for (i = 1; i <= 5; i++)
	{
		sta = ListInsert(&L,i,i);     //����Ԫ��
	}
	printf("�ڱ�ͷ����1~5��L.data = ");
	ListTraverse(L);
	
	printf("L�ĳ���Ϊ:%d \n",L.len);
	sta = ListEmpty(L);
	printf("L�Ƿ�Ϊ��:%d  (1:��  0:��)\n", sta);

	sta = ClearList(&L);
	printf("��պ�L�ĳ���Ϊ:%d \n", L.len);
	sta = ListEmpty(L);
	printf("L�Ƿ�Ϊ��:%d  (1:��  0:��)\n", sta);

	for (j = 1; j <= 10; j++)
	{
		sta = ListInsert(&L, j, j);
	}
	printf("�ڱ�β����1~10��L.data = ");
	ListTraverse(L);
	printf("L�ĳ���Ϊ:%d \n", L.len);

	ListInsert(&L, 1, 0);
	printf("�ڱ�β����0��L.data = ");
	ListTraverse(L);
	printf("L�ĳ���Ϊ:%d \n", L.len);

	GetElm(L,5,&e);
	printf("��5��Ԫ�ص�ֵΪ:%d\n",e);
	for (j = 3; j <= 4; j++)
	{
		sta = LocateElem(L,j);
		if (sta == 0)
			printf("û�и�%d��Ԫ��\n", sta);
		else
			printf("��%d��Ԫ�ص�ֵΪ%d\n",sta,j);
	}

	len = ListLength(L);  //�����

	for (j = len + 1; j >= len; j--)
	{
		sta = ListDelete(&L, j, &e);
		if (sta == ERROR)
			printf("ɾ��%d������ʧ��\n", j);
		else
			printf("ɾ����%d����Ԫ��ֵΪ:%d\n",j,e);
	}
	printf("�������Ԫ��:");
	ListTraverse(L);
	printf("L�ĳ���Ϊ:%d \n", L.len);

	j = 5;
	ListDelete(&L, j, &e);
	printf("�������Ԫ��:");
	ListTraverse(L);
	printf("L�ĳ���Ϊ:%d \n", L.len);

	sta = InitList(&Lb);		//��ʼ��Lb��
	i = 15;
	for (j = 1; j <= 5; j++)
	{
		sta = ListInsert(&Lb,j,i);
		i++;
	}
	printf("�������Ԫ��:");
	ListTraverse(Lb);

	UnionL(&L, Lb);

	printf("��������ϲ���Lb��L��Ԫ��");
	ListTraverse(L);


	return 0;
}