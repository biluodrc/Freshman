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
		cout << "��ȷ�����д�С��"; 
		cin >> max_size;
		q = new T[max_size];
		head = tail = 0;
		cout << "�����ɹ�\n";
	}
	void Insert(void)
	{
		cout << "****��ӣ���-1������****\n";
		T tem;
		while(1)
		{
			cin >> tem;
			if(tem == -1)
				break;
			if(max_size <= tail)
			{
				cout << "�������� ��������\n";
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
		cout << "��ӽ���\n";
	}
	void DelFirstEle(void)
	{
		if(tail <= 0)
		{
			cout << "�������Ѿ�û��Ԫ�أ�������ɾ\n";
			return ;
		}
		for(int i = 0 ; i < tail - 1 ; i++)
			q[i] = q[i + 1];
		tail--;
		cout << "ɾ���ɹ�\n";
	}
	void ReturnFirstEle(void)
	{
		if(tail == 0)
		{
			cout << "����������û��Ԫ��\n";
			return;
		}
		cout << "����Ԫ��Ϊ��";
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
		cout << "1���˳����� 2������Ԫ�� 3��ɾ������Ԫ�� 4����ȡ����Ԫ�� 5����ӡ����\n"; 
		cout << "��ѡ�������";
		cin >> tem;
		if(tem == 1)
		{
			cout << "�����˳�\n"; 
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
			cout << "������������������\n";
		}
		fflush(stdin);
		getchar();
		system("cls");
	}
}

