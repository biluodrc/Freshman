/*�������� 
12
22
#
#
32
#
#
*/
#include<iostream>
#include<queue>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<stack>
using namespace std;
struct node{
	int value;
	struct node *left;
	struct node *right;
};
class Tree{
private:
	struct node *root;
public:
	Tree(void);
	~Tree(){}
	void RootFirst_D(struct node *t); //  
	void RootMid_D(struct node *t); // 
	void RootFinal_D(struct node *t); //	
	void RootFirst_X(void);
	void RootMid_X(void);
	void RootFinal_X(void);
	void BFS(void);  // 
	void FindFather(void);  // 
	void FindArea(void);  //
	void DelTree(void);  // 
	struct node* BackRoot(void)
	{
		return root;
	}
	//void Print(void);
};
struct node * Read(struct node *p)
{
	char tem[5];
	memset(tem , '\0' , sizeof(tem));
	cin >> tem;
	if(strcmp(tem , "#") == 0)
	{
		return NULL;
	}
	else
	{
		p->value = atoi(tem);
		p->left = (struct node*)malloc(sizeof(struct node));
		p->right = (struct node*)malloc(sizeof(struct node));
		p->left = Read(p->left);
		p->right = Read(p->right);
		return p;
	}
}
Tree::Tree(void)
{
	cout << "****����������****\n";
	cout << "�밴����չ�ȸ���ķ�ʽ���������\n";
	char tem[5];
	memset(tem , '\0' , sizeof(tem));
	cin >> tem;
	if(strcmp(tem , "#") == 0)
	{
		cout << "���ɿ���\n";
		return ;
	}
	else
	{
		root = (struct node*)malloc(sizeof(struct node));
		root->value = atoi(tem);
		root->left = (struct node*)malloc(sizeof(struct node));
		root->right = (struct node*)malloc(sizeof(struct node));
		root->left = Read(root->left);
		root->right = Read(root->right);
	}
} 
void Tree::RootFirst_D(struct node *t) 
{
	if(root == NULL)
	{
		cout << "����Ǹ�����\n";
		return ;
	 } 
	if(t == NULL)
		return;
	cout << t->value << " ";
	if(t->left != NULL)
		RootFirst_D(t->left);
	if(t->right != NULL)
		RootFirst_D(t->right);
}
void Tree::RootMid_D(struct node *t)
{
	if(root == NULL)
	{
		cout << "����Ǹ�����\n";
		return ;
	 } 
	if(t == NULL)
		return;
	if(t->left != NULL)
		RootFirst_D(t->left);
	cout << t->value << " ";	
	if(t->right != NULL)
		RootFirst_D(t->right);	
}
void Tree::RootFinal_D(struct node *t)
{
	if(root == NULL)
	{
		cout << "����Ǹ�����\n";
		return ;
	 } 
	if(t == NULL)
		return;
	if(t->left != NULL)
		RootFirst_D(t->left);
	if(t->right != NULL)
		RootFirst_D(t->right);
	cout << t->value << " ";	
}
void Tree::BFS(void)
{	
	if(root == NULL)
	{
		cout << "����Ǹ�����\n";
		return ;
	 } 
	queue<struct node*> q; 
	q.push(root);
	while(!q.empty())
	{
		struct node *now = q.front();
		q.pop();
		cout << now->value << " ";
		if(now->left != NULL)
			q.push(now->left);
		if(now->right != NULL)
			q.push(now->right);
	}
}
void Tree::FindFather(void)
{
	cout << "��������Ҫ��ѯ�Ľڵ����ݣ�";
	int tem,flag = 1;
	cin >> tem;
	queue<struct node*> q; 
	q.push(root);
	while(!q.empty())
	{
		struct node *now = q.front();
		q.pop();
		if((now->left != NULL && (now->left)->value == tem) || (now->right != NULL && (now->right)->value == tem))
		{
			flag = 0;
			cout << now->value << " ";
		}
		if(now->left != NULL)
			q.push(now->left);
		if(now->right != NULL)
			q.push(now->right);
	}	
	if(flag)
	{
		cout << "������û�������Ľڵ�\n";
		return ;
	}
	else 
	{
		cout << "����Щ���ҵ��ĸ��׽ڵ��б��������\n";
		return ;
	}
}
void Tree::DelTree(void)
{
	cout << "��������Ҫɾ���Ľڵ㣨������������";
	int tem;
	cin >> tem;
	if(tem == root->value)
	{
		root = NULL;
		cout << "ɾ������\n";
		return ;
	}
	queue<struct node*> q; 
	q.push(root);
	struct node *now;
	while(!q.empty())
	{
		now = q.front();
		q.pop();
		if(now->left->value == tem)
		{
			now->left = NULL;
			break;
		}
		if(now->right->value == tem)
		{
			now->right = NULL;
			break;
		}
		if(now->left != NULL)
			q.push(now->left);
		if(now->right != NULL)
			q.push(now->right);
	}
	//cout << "asdf";
	cout << "ɾ������\n";
}
void Tree::FindArea(void)
{
	cout << "��������Ҫ���ҵ�������Χ��";
	int min,max;
	cin >> min >> max;
	if(max < min)
		swap(max , min);
	queue<struct node*> q; 
	q.push(root);
	int sum = 0; 
	while(!q.empty())
	{
		struct node *now = q.front();
		q.pop();
		if(now->value <= max && now->value >= min)
		{
			cout << now->value << ' ';
			sum++;
		}
		if(now->left != NULL)
			q.push(now->left);
		if(now->right != NULL)
			q.push(now->right);
	}
	cout << "����Щ��������������Χ�Ľڵ�����\n";
	cout << "��" << sum << "���ڵ�\n";
}
void Tree::RootFirst_X(void)
{
	if(root == NULL)
	{
		cout << "����Ǹ�����\n";
		return ;
	 } 
	stack<struct node*> s;
	struct node* now = root;
	while(now != NULL || !s.empty())
	{
		if(now)
		{
			cout << now->value << ' ';
			s.push(now);
			now = now->left;
		}
		else
		{
			now = s.top();
			s.pop();
			now = now->right;
		}
	}
 } 
void Tree::RootMid_X(void)
{
	if(root == NULL)
	{
		cout << "����Ǹ�����\n";
		return ;
	 } 
	stack<struct node*> s;
	struct node *now = root;
	while(now != NULL || !s.empty())
	{
		if(now)
		{
			s.push(now);
			now = now->left;
		}
		else  //�������Ѿ������� 
		{
			now = s.top();
			s.pop();
			cout << now->value << ' ';
			now = now->right;
		}
	}
}

void Tree::RootFinal_X(void)
{
	int ans[1000],place = 0;
	stack<struct node*> s;
	s.push(root);
	struct node *pre,*now;
	while(!s.empty())
	{
		now = s.top();
		if(now->left != NULL && now->left != pre && now->right != pre)
		{
			s.push(now->left);
		}
		else if(now->right != NULL && now->right != pre)
		{
			s.push(now->right);
		}
		else 
		{
			ans[place++] = now->value;
			s.pop();
			pre = now;
		}
	}
	for(int i = 0 ; i < place ; i++)
		cout << ans[i] << ' ';
}
int main(void)
{
	Tree t;
	while(1)
	{
		cout << "1������������ 2������ 3��ɾ�� 4���˳�\n";
		cout << "��ѡ����Ҫ���еĲ�����\n";
		int tem;
		cin >> tem;
		fflush(stdin);
		if(tem == 1)
		{
			cout << "1���ȸ����ݹ飩 2���и����ݹ飩 3��������ݹ飩4������������� 5���ȸ��������� 6���и���������7�������������\n";
			cout << "��ѡ������ķ�ʽ��"; 
			cin >> tem;
			if(tem == 1)
			{
				t.RootFirst_D(t.BackRoot());
				cout << "\n";
			}
			else if(tem == 2)
			{
				t.RootMid_D(t.BackRoot());
				cout << "\n";
			}
			else if(tem == 3)
			{
				t.RootFinal_D(t.BackRoot());
				cout << "\n";
			}
			else if(tem == 4)
			{
				t.BFS();
				cout << "\n";
			}
			else if(tem == 5)
			{
				t.RootFirst_X();
				cout << "\n";
			}
			else if(tem == 6)
			{
				t.RootMid_X();
				cout << "\n";
			 } 
			else if(tem == 7)
			{
				t.RootFinal_X();
				cout << "\n"; 
			}
		}
		else if(tem == 2)
		{
			cout << "1���������ڵ� 2������������\n";
			cout << "��ѡ�������ķ�ʽ��";
			cin >> tem;
			if(tem == 1)
			{
				t.FindFather();
			}
			else if(tem == 2)
			{
				t.FindArea();
			}
		}
		else if(tem == 3)
		{
			t.DelTree();
		}
		else if(tem == 4)
		{
			cout << "�������\n"; 
			break;
		}
		else
		{
			cout << "��������ȷ�Ĳ�����\n";
		}
		fflush(stdin);
		getchar();
		system("cls");
	}
	return 0;
}
