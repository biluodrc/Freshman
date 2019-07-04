/*
6.28 
最后一次的数据结构实验课作业
希尔怎么这么优。。。
快排、归并还有待优化 
*/ 

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<algorithm>
using namespace std;

#define T1 1000
#define T2 10000
#define T3 100000
#define T4 1000000

int a[1000000 + 5] , b[1000000 + 5];
int strt , over; 

//程序中的cmp和move是用来得出每种排序方法的比较、移动次数 
 
void PopSort(int *a , long n , long long &cmp , long long &move)
{
	int flag = 1;
	cmp = move = 0; 
	int strt = clock() , over;
	while(flag)
	{
		over = clock();
		if(over - strt >= 1000)
		{
			cmp = -1;
			move = -1;
			return;
		}
		
		flag = 0;
		for(long i = 0 ; i < n - 1 ; i++)
		{
			if(a[i] > a[i + 1])
			{
				int tem = a[i];
				a[i] = a[i + 1];
				a[i + 1] = tem;
				flag = 1;
				move += 3;
			}
			cmp++;
		}
	}
}

void InsertSort(int *a , long n , long long &cmp , long long &move)
{
	cmp = move = 0;
	int strt = clock() , over;  //测试时间，超过一秒直接结束 
	for(long i = 1 ; i < n ; i++)
	{
		over = clock();
		if(over - strt >= 1000)
		{
			cmp = -1;
			move = -1;
			return;
		}
		
		long place = i;
		while(1)
		{
			cmp++;
			if(place == 0)
				break;
			if(a[place - 1] >= a[i])
				place--;
			else
				break;
		}
		if(place == i)
			continue;
		int tem = a[i];
		for(int j = i ; j > place ; j--)
		{
			a[j] = a[j - 1];
			move++;
		}
		a[place] = tem;
		move++;
	}
}

void XuanSort(int *a , long n , long long &cmp , long long &move)
{
	cmp = move = 0;
	int strt = clock() , over;  //测试时间，超过一秒直接结束 
	for(long i = n - 1 ; i >= 0 ; i--)
	{
		over = clock();
		if(over - strt >= 1000)
		{
			cmp = -1;
			move = -1;
			return;
		}
		
		int max = -1 , u = -1;
		for(long j = 0 ; j <= i ; j++)
		{
			if(max < a[j])
			{
				max = a[j];
				u = j;
				cmp++;
			}
		}
		int tem = a[i];
		a[i] = a[u];
		a[u] = tem;
		move += 3;
	}
}

void FastSort(int *a , long m , long n , long long &cmp , long long &move)
{
	over = clock();
	if(over - strt >= 1000)
	{
		cmp = -1;
		move = -1;
		return;
	}
	if(cmp == -1)
		return ;
	
	if(m >= n)
		return;
	long i = m , j = n + 1;
//	static int strt = clock() , over;  //测试时间，超过一秒直接结束 
	while(i < j)
	{
		//printf("a");
		
		i++;
		while(a[i] < a[m])
		{
			i++;
			cmp++;
		}
		j--;
		while(a[j] > a[m])
		{
			j--;
			cmp++;
		}
		if(i < j)
		{
			int tem = a[j];
			a[j] = a[i];
			a[i] = tem;
			move += 3;
		}
	}
	int tem = a[m];
	a[m] = a[j];
	a[j] = tem;
	move += 3;
//	over = clock();
//	if(over - strt >= 1000)
//	{
//		cmp = -1;
//		move = -1;
//		return;
//	}
	FastSort(a , m , j - 1 , cmp , move);
	FastSort(a , j + 1 , n , cmp , move);
}

//void FastSort(int *a , long n , )

void ShellSort(int *a , long n , long long &cmp , long long &move)
{
	long d = n >> 1;
	while(d)
	{
		for(long i = 0 ; i + d < n ; i++)
		{
			if(a[i] > a[i + d])
			{
				int tem = a[i];
				a[i] = a[i + d];
				a[i + d] = tem;
				move += 3;
				
			}
			cmp++;
		}
		d = d >> 1;
	}
}

void HeapSort(int *a , long n , long long &cmp , long long &move)
{
	int strt = clock() , over;
	for(long i = n / 2 ; i >= 0 ; i--)
	{
		long now = i;
		while((2 * now + 1 < n && a[2 * now + 1] > a[now]) || (2 * now + 2 < n && a[2 * now + 2] > a[now]))
		{
			long j = 2 * now + 1;
			if(2 * now + 2 < n && a[2 * now + 2] > a[2 * now + 1])
				j++;
			cmp++;
			int tem = a[now];
			a[now] = a[j];
			a[j] = tem;
			now = j;
			move += 3;
		}
	}
	for(long i = 0 ; i < n - 1 ; i++)
	{
		over = clock();
		if(over - strt >= 1000)
		{
			cmp = -1;
			move = -1;
			return;
		}
		int tem = a[0];
		a[0] = a[n - i - 1];
		a[n - i - 1] = tem;
		long now = 0;
		while((2 * now + 1 < n - i && a[2 * now + 1] > a[now]) || (2 * now + 2 < n - i && a[2 * now + 2] > a[now]))
		{
			long j = 2 * now + 1;
			if(2 * now + 2 < n - i && a[2 * now + 2] > a[2 * now + 1])
				j++;
			cmp++;
			int tem = a[now];
			a[now] = a[j];
			a[j] = tem;
			now = j;
			move += 3;
		}
	}
//	for(int i = 0 ; i < n ; i++)
//		printf("%d " , a[i]);
}

void MergeSort(int *a , long m , long n , long long &cmp , long long &move)
{
	over = clock();
	if(over - strt >= 1000)
	{
		cmp = -1;
		move = -1;
		return ;
	}
	if(cmp == -1)
		return ;
	if(m + 1 >= n)
		return ;
	MergeSort(a , m , m + (n - m) / 2 , cmp , move);
	MergeSort(a , m + (n - m) / 2 , n , cmp , move);
	for(long i = m ; i < n ; i++)
	{
		b[i] = a[i];
		move++;
	}
	long i = m , j = m + (n - m) / 2 , k = m;
	while(1)
	{
		if(i < m + (n - m) / 2 && j < n)
		{
			if(b[i] > b[j])
			{
				a[k++] = b[j++];
				move++;
			}
			else
			{
				a[k++] = b[i++];
				move++;
			}
			cmp++;
		}
		else
			break;
	}
	if(i < m + (n - m) / 2)
		while(k < n)
		{
			a[k++] = b[i++];
			move++;
		}
	if(j < n)
		while(k < n)
		{
			a[k++] = b[j++];
			move++;
		}
}

void Out(long long &cmp , long long &move , int kind)
{
	if(kind == 1)
	{
		printf("冒泡排序 ");
	}
	else if(kind == 2)
	{
		printf("直接插入排序 ");
	}
	else if(kind == 3)
	{
		printf("简单选择排序 "); 
	}
	else if(kind == 4)
	{
		printf("快速排序 ");
		FILE *fp = fopen("SHELL.txt" , "w");
		for(long i = 0 ; i < 1000000 ; i++)
			fprintf(fp , "%d " , a[i]);
	}
	else if(kind == 5)
	{
		printf("希尔排序 ");
	}
	else if(kind == 6)
	{
		printf("堆排序 ");
	}
	else if(kind == 7)
	{
		printf("归并排序 ");
	}
	
	if(cmp == -1)  //打印cmp和move 
	{
		printf("INF INF\n");
	}
	else 
	{
		printf("%lld %lld\n" , cmp , move);
	}

}

int main(void)
{
	long long cmp , move;
	//测试
//	int a[10] = {5,4,3,2,1};
//	MergeSort(a , 0 , 5 , cmp , move);
	
	while(1)
	{
		printf("1000 10000 100000 1000000\n");
		printf("请选择数据范围：");
		long tem;
		scanf("%ld" , &tem);
		if(tem == -1)
			break;
		FILE *fp;
		if(tem == 1000)
			fp = fopen("1000.txt" , "r");
		else if(tem == 10000)
			fp = fopen("10000.txt" , "r");
		else if(tem == 100000)
			fp = fopen("100000.txt" , "r");
		else 
			fp = fopen("1000000.txt" , "r");
			
		printf("      比较次数       移动次数\n");
		
		rewind(fp);
		for(long i = 0 ; i < tem ; i++)  //执行排序 
			fscanf(fp , "%d" , &a[i]);
		cmp = move = 0;
		strt = clock();
		PopSort(a , tem , cmp , move);
		over = clock();
		Out(cmp , move , 1);
		printf("%.4fs\n\n" , 1.0 * (over - strt) / 1000);
		
		rewind(fp);
		for(long i = 0 ; i < tem ; i++)
			fscanf(fp , "%d" , &a[i]);
		cmp = move = 0;
		strt = clock();
		InsertSort(a , T2 , cmp , move);
		over = clock();
		Out(cmp , move , 2);
		printf("%.4fs\n\n" , 1.0 * (over - strt) / 1000);
		
		rewind(fp);
		for(long i = 0 ; i < tem ; i++) 
			fscanf(fp , "%d" , &a[i]);
		cmp = move = 0;
		strt = clock();
		XuanSort(a , tem , cmp , move);
		over = clock();
		Out(cmp , move , 3);
		printf("%.4fs\n\n" , 1.0 * (over - strt) / 1000);
		
		rewind(fp);
		for(long i = 0 ; i < tem ; i++)  
			fscanf(fp , "%d" , &a[i]);
		cmp = move = 0;
		strt = clock();
		FastSort(a , 0 , tem - 1 , cmp , move);
		over = clock();
		Out(cmp , move , 4);
		printf("%.4fs\n\n" , 1.0 * (over - strt) / 1000);
		
		rewind(fp);
		for(long i = 0 ; i < tem ; i++)  
			fscanf(fp , "%d" , &a[i]);
		cmp = move = 0;
		strt = clock();
		ShellSort(a , tem , cmp , move);
		over = clock();
		Out(cmp , move , 5);
		printf("%.4fs\n\n" , 1.0 * (over - strt) / 1000);
		
		rewind(fp);
		for(long i = 0 ; i < tem ; i++)  
			fscanf(fp , "%d" , &a[i]);
		cmp = move = 0;
		strt = clock();
		HeapSort(a , tem , cmp , move);
		over = clock();
		Out(cmp , move , 6);
		printf("%.4fs\n\n" , 1.0 * (over - strt) / 1000);
		
		rewind(fp);
		for(long i = 0 ; i < tem ; i++)  
			fscanf(fp , "%d" , &a[i]);
		cmp = move = 0;
		strt = clock();
		MergeSort(a , 0 , tem , cmp , move);
		over = clock();
		Out(cmp , move , 7);
		printf("%.4fs\n\n" , 1.0 * (over - strt) / 1000);
		
		fflush(stdin);
		getchar();
		system("cls");
	}
	return 0;
}
