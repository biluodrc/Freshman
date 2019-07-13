#include<iostream>
#include<stdlib.h>
#include<string.h>
using namespace std;
template<typename T>
class order{
	private:
		T *a;
		int M;
		int N;  //顺序表中有几个已插入的元素 
	public:
		order();
		void build(void);
		void insert(void);
		int out(int k);
		int del(int k);
		int find(T x);
		void print(void); 
		int *out_a(void);
};
template<typename T>
order<T>::order()
{
	M = N = 0;
	a = NULL;
}
template<typename T>
void order<T>::build(void)
{
	printf("请输入节点的个数：");
	scanf("%d",&M);
	a = (T *)malloc(sizeof(T) * M);
	memset(a,1,sizeof(int) * M);
	printf("创建成功，可容纳%d个结点\n",M);
	N = 0; 
	fflush(stdin);
	getchar();
	system("cls");
}
template<typename T>
void order<T>::insert(void)
{
	printf("****插入结点****\n");
	printf("输入插入位置和数据，以-1 -1接结束\n");
	int p,n,tem = -1;
	while(1)
	{
		cin >> p >> n;
		if(p < 0 && p != -1)
		{
			printf("请重新输入！");
			continue;
		}
		//printf("%d %d\n",p,n);
		if(p == -1 && n == -1)
			break;
		if((tem != -1 && p - tem != 1) || (tem == -1 && p != 0))
		{
			printf("顺序表请使用顺序输入！\n");
			continue;
		}
		a[p] = n;
		tem = p;
		N++;
	}
	printf("插入结束\n");
	fflush(stdin);
	getchar();
	system("cls");
}
template<typename T>
int order<T>::out(int k)
{
	if(k >= N)
		return 0; 
	printf("顺序表中第%d个数为：%d",k,a[k]);
	return a[k];
}
template<typename T>
int order<T>::del(int k)
{
	if(k > M)
	{
		printf("删除失败，k结点位置超过顺序表容量\n");
		return 0;
	}
	for(int i = k ; i < M ; i++)
		a[k] = a[k + 1];
	N--;
	printf("删除成功\n");
	return 1;
} 
template<typename T>
int order<T>::find(T x)
{
	for(int i = 0 ; i < M ; i++)
		if(x == a[i])
			return i;
	return -1;
}
template<typename T>
void order<T>::print(void)
{
	for(int i = 0 ; i < N ; i++)
		cout << a[i] << "->";
	printf("end\n");
}
template<typename T>
int *order<T>::out_a(void)
{
	return a;
}
int main(void)
{
	order<int> o;
	while(1)
	{
		printf("输入想要进行的操作：");
		printf("1、创建  2、插入  3、存取  4、删除  5、查找  6、打印  7、退出\n");
		int tem;
		scanf("%d",&tem);
		fflush(stdin);
		getchar();
		system("cls");
		if(tem != 1 && o.out_a() == NULL)
		{
			printf("请先创建链表再执行其他操作\n");
			continue;
		}
		if(tem == 1)
		{
			o.build();
		}
		else if(tem == 2)
		{
			o.insert();
		}
		else if(tem == 3)
		{
			printf("需要哪个节点的值：");
			scanf("%d",&tem);
			if(o.out(tem))
				printf("找到了\n");
			else 
				printf("么有找到\n");
		}
		else if(tem == 4)
		{
			printf("删除哪个节点:");
			scanf("%d",&tem); 
			o.del(tem);
		}
		else if(tem == 5)
		{
			int tt;
			printf("查找什么值：");
			scanf("%d",&tt);
			int flag = o.find(tt);
			if(flag != -1)
				printf("是%d个结点\n",flag);
			else 
				printf("没有这个结点\n"); 
		}
		else if(tem == 6) 
		{
			o.print();
		}
		else if(tem == 7)
		{
			printf("程序结束\n");
			break;
		}
	}
	return 0;
}
