/*测试数据 
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
	cout << "****创建二叉树****\n";
	cout << "请按照扩展先根序的方式输入二叉树\n";
	char tem[5];
	memset(tem , '\0' , sizeof(tem));
	cin >> tem;
	if(strcmp(tem , "#") == 0)
	{
		cout << "生成空树\n";
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
		cout << "这就是个空树\n";
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
		cout << "这就是个空树\n";
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
		cout << "这就是个空树\n";
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
		cout << "这就是个空树\n";
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
	cout << "请输入想要查询的节点数据：";
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
		cout << "在树中没有这样的节点\n";
		return ;
	}
	else 
	{
		cout << "：这些是找到的父亲节点中保存的数据\n";
		return ;
	}
}
void Tree::DelTree(void)
{
	cout << "请输入想要删除的节点（及其子树）：";
	int tem;
	cin >> tem;
	if(tem == root->value)
	{
		root = NULL;
		cout << "删除结束\n";
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
	cout << "删除结束\n";
}
void Tree::FindArea(void)
{
	cout << "请输入想要查找的数据域范围：";
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
	cout << "：这些是树中在数据域范围的节点数据\n";
	cout << "共" << sum << "个节点\n";
}
void Tree::RootFirst_X(void)
{
	if(root == NULL)
	{
		cout << "这就是个空树\n";
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
		cout << "这就是个空树\n";
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
		else  //左子树已经打完了 
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
		cout << "1、遍历二叉树 2、搜索 3、删除 4、退出\n";
		cout << "请选择想要进行的操作：\n";
		int tem;
		cin >> tem;
		fflush(stdin);
		if(tem == 1)
		{
			cout << "1、先根（递归） 2、中根（递归） 3、后根（递归）4、广度优先搜素 5、先根（迭代） 6、中根（迭代）7、后根（迭代）\n";
			cout << "请选择遍历的方式："; 
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
			cout << "1、搜索父节点 2、搜索数据域\n";
			cout << "请选择搜索的方式：";
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
			cout << "程序结束\n"; 
			break;
		}
		else
		{
			cout << "请输入正确的操作！\n";
		}
		fflush(stdin);
		getchar();
		system("cls");
	}
	return 0;
}
