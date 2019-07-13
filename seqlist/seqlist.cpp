#include<iostream>
#include<stdlib.h>
#include<string.h>
using namespace std;
template<typename T>
class order{
	private:
		T *a;
		int M;
		int N;  //˳������м����Ѳ����Ԫ�� 
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
	printf("������ڵ�ĸ�����");
	scanf("%d",&M);
	a = (T *)malloc(sizeof(T) * M);
	memset(a,1,sizeof(int) * M);
	printf("�����ɹ���������%d�����\n",M);
	N = 0; 
	fflush(stdin);
	getchar();
	system("cls");
}
template<typename T>
void order<T>::insert(void)
{
	printf("****������****\n");
	printf("�������λ�ú����ݣ���-1 -1�ӽ���\n");
	int p,n,tem = -1;
	while(1)
	{
		cin >> p >> n;
		if(p < 0 && p != -1)
		{
			printf("���������룡");
			continue;
		}
		//printf("%d %d\n",p,n);
		if(p == -1 && n == -1)
			break;
		if((tem != -1 && p - tem != 1) || (tem == -1 && p != 0))
		{
			printf("˳�����ʹ��˳�����룡\n");
			continue;
		}
		a[p] = n;
		tem = p;
		N++;
	}
	printf("�������\n");
	fflush(stdin);
	getchar();
	system("cls");
}
template<typename T>
int order<T>::out(int k)
{
	if(k >= N)
		return 0; 
	printf("˳����е�%d����Ϊ��%d",k,a[k]);
	return a[k];
}
template<typename T>
int order<T>::del(int k)
{
	if(k > M)
	{
		printf("ɾ��ʧ�ܣ�k���λ�ó���˳�������\n");
		return 0;
	}
	for(int i = k ; i < M ; i++)
		a[k] = a[k + 1];
	N--;
	printf("ɾ���ɹ�\n");
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
		printf("������Ҫ���еĲ�����");
		printf("1������  2������  3����ȡ  4��ɾ��  5������  6����ӡ  7���˳�\n");
		int tem;
		scanf("%d",&tem);
		fflush(stdin);
		getchar();
		system("cls");
		if(tem != 1 && o.out_a() == NULL)
		{
			printf("���ȴ���������ִ����������\n");
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
			printf("��Ҫ�ĸ��ڵ��ֵ��");
			scanf("%d",&tem);
			if(o.out(tem))
				printf("�ҵ���\n");
			else 
				printf("ô���ҵ�\n");
		}
		else if(tem == 4)
		{
			printf("ɾ���ĸ��ڵ�:");
			scanf("%d",&tem); 
			o.del(tem);
		}
		else if(tem == 5)
		{
			int tt;
			printf("����ʲôֵ��");
			scanf("%d",&tt);
			int flag = o.find(tt);
			if(flag != -1)
				printf("��%d�����\n",flag);
			else 
				printf("û��������\n"); 
		}
		else if(tem == 6) 
		{
			o.print();
		}
		else if(tem == 7)
		{
			printf("�������\n");
			break;
		}
	}
	return 0;
}
