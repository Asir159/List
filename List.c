#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <string.h>

#define MAXSIZE 20

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

typedef int Elmtype;		//元素类型
typedef int Status;			//状态码函数

typedef struct SqList
{
	Elmtype data[MAXSIZE];
	int len;
}SqList;

/*	  初始化线性表		*/
Status InitList(SqList* L)
{
	//memset(L->data,0,sizeof(int)*MAXSIZE);
	L->len = 0;

	return OK;
}

Status ListInsert(SqList* L, int i, Elmtype e)
{
	int j;
	if (L->len >= MAXSIZE)	    //顺序表已满
		return ERROR;
	if (i<1 || i >L->len+1)		//当i的位置小于线性表的长度或者大于的长度
		return ERROR;
	//在第i个位置插入元素
	if (i < L->len)  //如果不在表尾
	{
		for (j = L->len-1; j >= i-1; j--)		//整体元素向后移动一格
		{
			L->data[j + 1] = L->data[j];
		}
	}
	L->data[i-1] = e;							//插入新元素
	L->len++;								//长度加一

	return OK;
}

/*	  访问data元素	  */
Status vist(Elmtype e)					
{
	printf("%d  ", e);
	return OK;
}

/*		遍历data数组			*/	
Status ListTraverse(SqList L)
{
	int i;
	for (i = 0; i < L.len; i++)
	{
		vist(L.data[i]);
	}
	printf("\n");
}

/*	查看表是否为空	*/
Status ListEmpty(SqList L)
{
	if (L.len == 0)
		return TRUE;
	return FALSE;
}

/*		将表格置为空表		*/	
Status ClearList(SqList* L)
{
	L->len = 0;			//只需要把表格的长度清理即可, 数据后续可覆盖
	return OK;
}

/*			获取指定的元素			*/	
Status GetElm(SqList L, int i, Elmtype* e)
{
	if (i<1 || i>L.len || L.len == 0)			//若i大/小于表长度,或表的长度为0
		return ERROR;							//抛出错误
	*e = L.data[i-1];					//元素给予
	return OK;
}

int ListLength(SqList L)
{
	return L.len;
}

Status ListDelete(SqList* L, int i, Elmtype* e)
{
	int j;
	if (L->len == 0)		//表不能为空
		return ERROR;
	if (i<0 || i>L->len)	//位置不能小于和大于长度
		return ERROR;
	*e = L->data[i-1];
	if (i < L->len)						//如果不在表尾
	{
		for (j = i; j < L->len - 1; j++)
		{
			L->data[j] = L->data[j + 1];
		}
	}

	L->len--;
	return OK;
}

/*		寻找表中是否有符合的元素		*/
/*            没有返回0             */
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

/*将所有在Lb中但不在La中的元素插入进La中*/
Status UnionL(SqList* La, SqList Lb)
{
	int i;
	Elmtype e;
	int len_La, len_Lb;

	if (La->len == 0 || Lb.len == 0)			//不能位空表
		return ERROR;

	len_La = ListLength(*La);
	len_Lb = ListLength(Lb);

	for (i = 1; i < len_Lb; i++)
	{
		//获取Lb的元素
		GetElm(Lb, i, &e);
		if(!LocateElem(*La,e))				//寻找La中不存在和e相同的元素
		ListInsert(La,++len_La,e);			//La在表尾中插入Lb
	}
}

int main()
{
	int i,j,len;
	Elmtype e;
	SqList L,Lb;
	Status sta;
	//初始化表格
	sta = InitList(&L);
	printf("初始化L后len的长度:%d\n",L.len);
	for (i = 1; i <= 5; i++)
	{
		sta = ListInsert(&L,i,i);     //插入元素
	}
	printf("在表头插入1~5后：L.data = ");
	ListTraverse(L);
	
	printf("L的长度为:%d \n",L.len);
	sta = ListEmpty(L);
	printf("L是否为空:%d  (1:是  0:否)\n", sta);

	sta = ClearList(&L);
	printf("清空后L的长度为:%d \n", L.len);
	sta = ListEmpty(L);
	printf("L是否为空:%d  (1:是  0:否)\n", sta);

	for (j = 1; j <= 10; j++)
	{
		sta = ListInsert(&L, j, j);
	}
	printf("在表尾插入1~10后：L.data = ");
	ListTraverse(L);
	printf("L的长度为:%d \n", L.len);

	ListInsert(&L, 1, 0);
	printf("在表尾插入0：L.data = ");
	ListTraverse(L);
	printf("L的长度为:%d \n", L.len);

	GetElm(L,5,&e);
	printf("第5个元素的值为:%d\n",e);
	for (j = 3; j <= 4; j++)
	{
		sta = LocateElem(L,j);
		if (sta == 0)
			printf("没有该%d的元素\n", sta);
		else
			printf("第%d个元素的值为%d\n",sta,j);
	}

	len = ListLength(L);  //求出表长

	for (j = len + 1; j >= len; j--)
	{
		sta = ListDelete(&L, j, &e);
		if (sta == ERROR)
			printf("删除%d的数据失败\n", j);
		else
			printf("删除第%d个的元素值为:%d\n",j,e);
	}
	printf("依次输出元素:");
	ListTraverse(L);
	printf("L的长度为:%d \n", L.len);

	j = 5;
	ListDelete(&L, j, &e);
	printf("依次输出元素:");
	ListTraverse(L);
	printf("L的长度为:%d \n", L.len);

	sta = InitList(&Lb);		//初始化Lb表
	i = 15;
	for (j = 1; j <= 5; j++)
	{
		sta = ListInsert(&Lb,j,i);
		i++;
	}
	printf("依次输出元素:");
	ListTraverse(Lb);

	UnionL(&L, Lb);

	printf("依次输入合并了Lb的L的元素");
	ListTraverse(L);


	return 0;
}