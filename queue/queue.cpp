#include<iostream>
using namespace std;
template<typename T>
class queue{
private:
	T *q;
	int max_size;
	int head,tail;
public:
	queue(void)
	{
		cout << "请确定队列大小："; 
		cin >> max_size;
		q = new T[max_size];
		head = tail = 0;
		cout << "创建成功\n";
	}
	void Insert(void)
	{
		cout << "****入队（以-1结束）****\n";
		T tem;
		while(1)
		{
			cin >> tem;
			if(tem == -1)
				break;
			if(max_size <= tail)
			{
				cout << "队列已满 结束插入\n";
				return ; 
			}
			if(tail == 0)
			{
				q[head] = tem;
				tail++;
			}
			else
			{
				q[tail++] = tem;
			}
		}
		cout << "入队结束\n";
	}
	void DelFirstEle(void)
	{
		if(tail <= 0)
		{
			cout << "队列中已经没有元素，不能再删\n";
			return ;
		}
		for(int i = 0 ; i < tail - 1 ; i++)
			q[i] = q[i + 1];
		tail--;
		cout << "删除成功\n";
	}
	void ReturnFirstEle(void)
	{
		if(tail == 0)
		{
			cout << "队列中现在没有元素\n";
			return;
		}
		cout << "队首元素为：";
		cout << q[head]; 
	}
	void print(void)
	{
		cout << "=>";
		for(int i = 0 ; i < tail ; i++)
		{
			cout << q[i];
			if(i != tail - 1)
				cout << "->";
		}
	}
	~queue(){}
}; 
int main(void)
{
	int tem;
	queue<int> Final;
	while(1)
	{
		cout << "1、退出程序 2、插入元素 3、删除队首元素 4、读取队首元素 5、打印队列\n"; 
		cout << "请选择操作：";
		cin >> tem;
		if(tem == 1)
		{
			cout << "程序退出\n"; 
			break; 
		}
		else if(tem == 2)
		{
			Final.Insert();
		}
		else if(tem == 3)
		{
			Final.DelFirstEle();
		}
		else if(tem == 4)
		{
			Final.ReturnFirstEle();
		}
		else if(tem == 5)
		{
			Final.print();
		}
		else 
		{
			cout << "输入有误，请重新输入\n";
		}
		fflush(stdin);
		getchar();
		system("cls");
	}
}

