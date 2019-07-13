#include<iostream>
#include<cstdlib>
using namespace std;
struct node{
	int value;
	struct node *next;
};
class line{
	private:
		struct node *head,*tail,*cur;
	public:
		line();
		~line(){}
		void insert_h(void);  //ͷ����
		void insert_t(void);  //β����
		void insert_c(void);  //��ǰ�ڵ����
		void del_h(void);  //ͷɾ��
		void del_t(void);  //βɾ��
		void del_c(void);  //��ǰ�ڵ�ɾ��
		int out_cur(void);  //�����ǰ�ڵ�
		int out_k(int k);  //�����k���ڵ�
		void store_cur(void);  //�ı䵱ǰ�ڵ��ֵ
		void store_k(int k);   //�ı��k���ڵ��ֵ 
		int find(int x);  //����
		void print(void);  //��ӡ���� 
		void change_cur(void);  //�ı䵱ǰ�ڵ�ָ���λ��
};

line::line()
{
	head = tail = cur = NULL;
}

void line::insert_h(void)
{
	cout << "����ͷ�������ݣ���-1����\n";
	while(1)
	{
		int tem;
		cin >> tem;
		if(tem == -1)
			break;
		struct node *tt = (struct node *)malloc(sizeof(struct node));
		tt->value = tem;
		tt->next = NULL;
		if(head == NULL)
		{
			head = tt;
			tail = tt;
			cur = tt;
		}
		else
		{
			tt->next = head;
			head = tt;
			cur = tt;
		}
	}
}

void line::insert_t(void)
{
	cout << "����β�������ݣ���-1����\n";
	while(1)
	{
		int tem;
		cin >> tem;
		if(tem == -1)
			break;
		struct node *tt = (struct node *)malloc(sizeof(struct node));
		tt->value = tem;
		tt->next = NULL;
		if(head == NULL)
		{
			head = tt;
			tail = tt;
			cur = tt;
		}
		else
		{
			tail->next = tt;
			tail = tt;
			cur = tt;
		}
	}
}

void line::insert_c(void)
{
	cout << "�ڵ�ǰ�����������ݣ���-1����\n";
	while(1)
	{
		int tem;
		cin >> tem;
		if(tem == -1)
			break;
		struct node *tt = (struct node *)malloc(sizeof(struct node));
		tt->value = tem;
		tt->next = NULL;
		if(head == NULL)
		{
			head = tt;
			tail = tt;
			cur = tt;
		}
		else if(cur == tail)
		{
			tail->next = tt;
			cur = tail = tt;
		}
		else
		{
			tt->next = cur->next;
			cur->next = tt;
			cur = tt;
		}
	}	
}

void line::del_h(void)
{
	cout << "ɾ��ͷ���\n";
	if(head == tail)
	{
		free(head);
		head = cur = tail = NULL;
	}
	else if(head == cur)
	{
		struct node *tem = head;
		cur = cur->next;
		head = head->next;
		free(tem); 
	}
	else
	{
		struct node *tem = head;
		head = head->next;
		free(tem); 
	}
} 

void line::del_t(void)
{
	cout << "ɾ��β���\n";
	if(head == tail)
	{
		free(tail);
		tail = head = cur = NULL;
	}
	else if(tail == cur)
	{
		struct node *scan = head;
		while(scan->next != tail)
			scan = scan->next;
		free(tail);
		scan->next = NULL;
		tail = scan;
		cur = scan;
	}
	else
	{
		struct node *scan = head;
		while(scan->next != tail)
			scan = scan->next;
		free(tail);
		scan->next = NULL;
		tail = scan;
	}
}

void line::del_c(void) 
{
	cout << "ɾ����ǰ���ĺ�̽ڵ�\n";
	struct node *scan = head;
	if(tail == cur)
	{
		cout << "��ǰ�ڵ�Ϊ���һ���ڵ㣬�޺�̽ڵ�\n";
		return;
	}
	struct node *tem = cur->next;
	cur->next = cur->next->next;
	free(tem);
}

int line::out_cur(void)
{
	cout << "��ǰ����ֵΪ��" << cur->value << endl;
	return cur->value; 
}

int line::out_k(int k)
{
	struct node *scan = head;
	for(int i = 0 ; i < k ; i++)
	{
		if(scan == NULL)
		{
			cout << "������û����ô����\n";
			return 0;
		}
		scan = scan->next;
	}
	cout << "�����е�" << k << "�����ǣ�" << scan->value << endl;
	return scan->value; 
}

int line::find(int x)
{
	struct node *scan = head;
	while(scan != NULL)
	{
		if(scan->value == x)
		{
			cout << "�ҵ���\n";
			return 1;
		}
		scan = scan->next;
	}
	cout << "������û�������\n";
	return 0;
}

void line::print(void) 
{
	struct node *scan = head;
	cout << "=>";
	while(scan != NULL)
	{
		cout << scan->value << "->";
		scan = scan->next;
	}
	cout << scan->value << endl;
}

void line::store_cur(void)
{
	cout << "��������Ҫ�洢��ֵ��";
	int tem;
	cin >> tem;
	cur->value = tem; 
}

void line::store_k(int k)
{
	struct node *scan = head;
	int place = 0;
	while(place != k && scan != NULL)
	{
		place++;
		scan = scan->next;
	}
	if(place != k)
	{
		cout << "������û����ô��Ľڵ�\n";
		return;
	}
	else
	{
		cout << "��������Ҫ�洢��ֵ\n";
		int tem;
		cin >> tem;
		scan->value = tem;
	}
}

void line::change_cur(void)
{
	cout << "�������뽫curָ��ָ���λ�ã�";
	int tem;
	cin >> tem;
	struct node *scan = head;
	int place = 0;
	while(place != tem)
	{
		place++;
		scan = scan->next;
	}
	cur = scan;
	cout << "���ĳɹ�\n";
}

int main(void)
{
	int flag = 1;
	line l;
	while(1)
	{
		cout << "1���������� 2������ 3��ɾ�� 4������ 5����ȡ 6����ӡ 7���˳� 8������curλ��\n";
		cout << "ѡ�������\n";
		int tem;
		cin >> tem;
		fflush(stdin);
		if(tem != 1 && flag)
		{
			cout << "���ȴ�������\n";
			continue;
		}
		if(tem == 1)
		{
			if(flag == 0)
			{
				cout << "�Ѿ�����������ִ����������\n";
				continue;
			}
			l = line();
			flag = 0;
			cout << "�����ɹ�\n";
		}
		else if(tem == 2)
		{
			cout << "1��ͷ���� 2��β���� 3����ǰ������\n";
			cin >> tem;
			if(tem == 1)
				l.insert_h();
			else if(tem == 2)
				l.insert_t();
			else if(tem == 3)
				l.insert_c();
		}
		else if(tem == 3)
		{
			cout << "1��ͷɾ�� 2��βɾ�� 3����ǰ���ɾ��\n";
			cin >> tem;
			if(tem == 1)
				l.del_h();
			else if(tem == 2)
				l.del_t();
			else if(tem == 3)
				l.del_c(); 
		}
		else if(tem == 4)
		{
			cout << "������ҵ�ֵ��";
			cin >> tem;
			l.find(tem); 
		} 
		else if(tem == 5)
		{
			cout << "1����ǰ��ȡ 2��λ�ö�ȡ 3����ǰ�洢 4��λ�ô洢\n";
			cin >> tem;
			if(tem == 1)
			{
				l.out_cur(); 
			} 
			else if(tem == 2)
			{
				cout << "��ȡ��λ�ã�";
				cin >> tem;
				l.out_k(tem);
			}
			else if(tem == 3)
			{
				l.store_cur();
			}
			else if(tem == 4)
			{
				cout << "�洢��λ�ã�";
				cin >> tem;
				l.store_k(tem);
			}
		}
		else if(tem == 6)
		{
			l.print();
		 } 
		else if(tem == 7)
		{
			cout << "��������\n";
			break;
		}
		else if(tem == 8)
		{
			l.change_cur();
		}
		else
		{
			cout << "��������ȷ������\n";
		}
		
	}
}
