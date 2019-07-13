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
		void insert_h(void);  //头插入
		void insert_t(void);  //尾插入
		void insert_c(void);  //当前节点插入
		void del_h(void);  //头删除
		void del_t(void);  //尾删除
		void del_c(void);  //当前节点删除
		int out_cur(void);  //输出当前节点
		int out_k(int k);  //输出第k个节点
		void store_cur(void);  //改变当前节点的值
		void store_k(int k);   //改变第k个节点的值 
		int find(int x);  //查找
		void print(void);  //打印链表 
		void change_cur(void);  //改变当前节点指向的位置
};

line::line()
{
	head = tail = cur = NULL;
}

void line::insert_h(void)
{
	cout << "在链头插入数据，以-1结束\n";
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
	cout << "在链尾输入数据，以-1结束\n";
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
	cout << "在当前结点后输入数据，以-1结束\n";
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
	cout << "删除头结点\n";
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
	cout << "删除尾结点\n";
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
	cout << "删除当前结点的后继节点\n";
	struct node *scan = head;
	if(tail == cur)
	{
		cout << "当前节点为最后一个节点，无后继节点\n";
		return;
	}
	struct node *tem = cur->next;
	cur->next = cur->next->next;
	free(tem);
}

int line::out_cur(void)
{
	cout << "当前结点的值为：" << cur->value << endl;
	return cur->value; 
}

int line::out_k(int k)
{
	struct node *scan = head;
	for(int i = 0 ; i < k ; i++)
	{
		if(scan == NULL)
		{
			cout << "链表中没有这么多结点\n";
			return 0;
		}
		scan = scan->next;
	}
	cout << "链表中第" << k << "个数是：" << scan->value << endl;
	return scan->value; 
}

int line::find(int x)
{
	struct node *scan = head;
	while(scan != NULL)
	{
		if(scan->value == x)
		{
			cout << "找到了\n";
			return 1;
		}
		scan = scan->next;
	}
	cout << "链表中没有这个数\n";
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
	cout << "请输入想要存储的值：";
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
		cout << "链表中没有这么多的节点\n";
		return;
	}
	else
	{
		cout << "请输入想要存储的值\n";
		int tem;
		cin >> tem;
		scan->value = tem;
	}
}

void line::change_cur(void)
{
	cout << "请输入想将cur指针指向的位置：";
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
	cout << "更改成功\n";
}

int main(void)
{
	int flag = 1;
	line l;
	while(1)
	{
		cout << "1、创建链表 2、插入 3、删除 4、查找 5、存取 6、打印 7、退出 8、更改cur位置\n";
		cout << "选择操作：\n";
		int tem;
		cin >> tem;
		fflush(stdin);
		if(tem != 1 && flag)
		{
			cout << "请先创建链表\n";
			continue;
		}
		if(tem == 1)
		{
			if(flag == 0)
			{
				cout << "已经创建链表，请执行其他操作\n";
				continue;
			}
			l = line();
			flag = 0;
			cout << "创建成功\n";
		}
		else if(tem == 2)
		{
			cout << "1、头插入 2、尾插入 3、当前结点插入\n";
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
			cout << "1、头删除 2、尾删除 3、当前结点删除\n";
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
			cout << "输入查找的值：";
			cin >> tem;
			l.find(tem); 
		} 
		else if(tem == 5)
		{
			cout << "1、当前读取 2、位置读取 3、当前存储 4、位置存储\n";
			cin >> tem;
			if(tem == 1)
			{
				l.out_cur(); 
			} 
			else if(tem == 2)
			{
				cout << "存取的位置：";
				cin >> tem;
				l.out_k(tem);
			}
			else if(tem == 3)
			{
				l.store_cur();
			}
			else if(tem == 4)
			{
				cout << "存储的位置：";
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
			cout << "操作结束\n";
			break;
		}
		else if(tem == 8)
		{
			l.change_cur();
		}
		else
		{
			cout << "请输入正确的数字\n";
		}
		
	}
}
