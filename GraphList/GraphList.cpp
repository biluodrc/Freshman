#include<iostream>
#include<cstring>
#include<algorithm>
#include<queue> 
using namespace std;

struct node{
	int value;
	int to;
	struct node *next;
};
struct edge{
	int from;
	int to;
	int value;
	int order;
};

struct node *(head[1000 + 5]);
struct edge e[10000];
int mark[1000 + 5];
int A[1000 + 5][1000 + 5],edge[1000 + 5][1000 + 5];
int head_sum,edge_sum;
int set[1000 + 5];  //并查集 

void BuildGraph(void);  //  之后改的时候将连接表中的东西进行一下排序 ,不改了 
void EdgeValue(void);  //
void NextVertax(void);  //
void BFS(void);  //
void DFS(int now);  //
void Floyd(void);  //
void Kruskal(void);
void Prim(void);
void test(void);  //看链接表中的节点 


void Prim(void)
{
	int INF = 100000;
	int dist[1000 + 5] , flag[1000 + 5] , path[1000 + 5];
	for(int i = 1 ; i <= head_sum ; i++)
	{
		dist[i] = INF;
		flag[i] = 0;
		path[i] = 0;
	}
	dist[1] = 0; flag[1] = 1;
	for(struct node *scan = head[1]->next ; scan != NULL ; scan = scan->next)
	{
		dist[scan->to] = scan->value;
		path[scan->to] = 1;
	}
	for(int i = 1 ; i < head_sum ; i++)
	{
		int min = 100000,u = -1;
		for(int j = 1 ; j <= head_sum ; j++)
		{
			if(flag[j] == 0 && dist[j] < min)
			{
				u = j;
				min = dist[j];
				//cout << "b";
			}
		}
		if(u == -1)
		{
			break;
		}
		flag[u] = 1;
		for(struct node *scan = head[u]->next ; scan != NULL ; scan = scan->next)
		{
			if(dist[scan->to] > scan->value && flag[scan->to] == 0)  //这里在更新dist和path时，要注意还是要检查终点是否已经在选中点中（即flag），是在不要让走过的点在发生改变 
			{
				dist[scan->to] = scan->value;
				path[scan->to] = u;
			}
		}
	}
	cout << "path：";
	for(int i = 1 ; i <= head_sum ; i++)
	{
		cout << path[i] << " ";
	}
	cout << endl; 
	cout << "path[i] == j ：表示的是最小生成树中i和j是相连的\n";
}

int cmp(const void* x , const void* y)
{
	if(((struct edge*)x)->value <= ((struct edge*)y)->value)
		return -1;
	else
		return 1;
}

struct edge *GetEdge(void)
{
	
	for(int i = 1 ; i <= head_sum ; i++)
	{
		for(struct node *scan = head[i]->next ; scan != NULL ; scan = scan->next)
		{
			int from = i ,to = scan->to , value = scan->value;
			if(from > to)
				swap(from , to); 
			int flag = 0;
			for(int j = 0 ; j < edge_sum ; j++)
			{
				if((e[j]).from == from && (e[j]).to == to)
				{
					flag = 1;
					break;
				}
			}
			if(flag == 0)
			{
				e[edge_sum].from = from;
				e[edge_sum].to = to;
				e[edge_sum].value = value;
				e[edge_sum].order = -1;
				edge_sum++;
			}
		}
	}
	qsort(e , edge_sum , sizeof(struct edge) , cmp);
//	for(int i = 0 ; i < edge_sum ; i++)
//	{
//		cout << e[i].from << " " << e[i].to << ' ' << e[i].value << endl;
//	}
} 

int NoCircle(int tem)
{
	if(set[e[tem].from] == -1 || set[e[tem].to] == -1)
		return 1;
	else
	{
		if(set[e[tem].from] == set[e[tem].to])
			return 0;
		else
			return 1;
	}
}

void MergeSet(int from , int to)  //合并并查集 
{
	if(set[to] == -1)
	{
		if(set[from] == -1)
		{
			set[from] = from;
			set[to] = to;
		}
		else
		{
			set[to] = set[from];
		}
	}
	else
	{
		int to_head = set[to];
		int from_head = set[from] == -1 ? from : set[from];
		for(int i = 0 ; i < edge_sum ; i++)
		{
			if(set[i] == to_head)
				set[i] = from_head;
		}
	}
}

void Kruskal(void)
{
	GetEdge();
	int order = 0;
	memset(set , -1 , sizeof(set));
	for(int i = 1 ; i < head_sum ; i++)
	{
		int min = 100000 , now = -1;
		for(int j = 0 ; j < edge_sum ; j++)
		{
			if(e[j].order == -1 && min > e[j].value && NoCircle(j))
			{
				min = e[j].value;
				now = j;
				break;
			}		
		}		
	//	cout << now;
		if(now == -1)
		{
			cout << "这个图有挂起的节点，没有最小生成树\n";
			return ;
		}
		e[now].order = order++;
		MergeSet(e[now].from , e[now].to);
		//cout << e[now].from << ' '  << e[now].to << ' ' << e[now].order << e[now].head << endl;
	}
	cout << "pf pt\n";
	for(int i = 0 ; i < order ; i++)
	{
		for(int j = 0 ; j < edge_sum ; j++)
		{
			if(e[j].order == i)
			{
				cout << e[j].from << ' ' << e[j].to << ' ' << endl;
			}
		}
	}
	cout << "pf pt表示最小生成树中pf和pt相连\n";
}

void Floyd(void)
{
	memset(A , 0 , sizeof(A));
	for(int i = 1 ; i <= head_sum ; i++)
	{
		struct node *scan = head[i]->next;
		while(scan != NULL)
		{
			edge[i][scan->to] = scan->value;
			scan = scan->next;
		}
	}
	for(int i = 1 ; i <= head_sum ; i++)
	{
		for(int j = 1 ; j <= head_sum ; j++)
		{
			if(edge[i][j] == 0 && i != j)
			{
				A[i][j] = 100000;
			}
			else 
			{
				A[i][j] = edge[i][j];
			}
		}
	}
	
	for(int k = 1 ; k <= head_sum ; k++)
	{
		for(int i = 1 ; i <= head_sum ; i++)
		{
			for(int j = 1 ; j <= head_sum ; j++)
			{
				if(A[i][k] + A[k][j] < A[i][j])
					A[i][j] = A[i][k] + A[k][j];
			}
		}
	}
	cout << "  ";
	for(int i = 1 ; i <= head_sum ; i++)
		printf("%3d ",i);
	cout << endl;
	for(int i = 1 ; i <= head_sum ; i++)
	{
		cout << i << ' ';
		for(int j = 1 ; j <= head_sum ; j++)
		{
			printf("%3d ",A[i][j]);
		}
		cout << endl;
	}
	cout << "这个矩阵表示任意两点之间最短路径长度\n";
}
void NextVertax(void)
{
	cout << "请选择想要查找的点：";
	int tem;
	cin >> tem;
	fflush(stdin);
	struct node *scan = head[tem]->next;
	int min = 100000;
	while(scan != NULL)
	{
		if(min > scan->to)
			min = scan->to;
		scan = scan->next;
	}
	if(min == 100000)
		cout << "这个点没有邻接点\n";
	else
		cout << min << " 这个是" << tem << "点的第一个邻接顶点\n"; 
}
void EdgeValue(void)
{
	cout << "请输入想要查找的边权两端的节点编号：";
	int n,m;
	cin >> n >> m;
	fflush(stdin);
	if(n > head_sum || m > head_sum)
	{
		cout << "没有这样的节点" << endl;
		return; 
	}
	struct node *scan = head[n]->next;
	while(scan != NULL)
	{
		if(scan->to == m)
		{
			cout << "这条边的权值为：" << scan->value << endl;
			return ;
		}
		scan = scan->next;
	}
	cout << "这两个点之间并没有边相连\n";
 } 

void BuildGraph(void)
{
	FILE *fp = fopen("test.txt" , "r");
	int m , n;
	fscanf(fp , "%d%d" , &m , &n);
	head_sum = m;
	for(int i = 1 ; i <= m ; i ++)
	{
		head[i] = new struct node;
		head[i]->next = NULL;
		head[i]->value = i;
	}
	for(int i = 0 ; i < n ; i++)
	{
		//printf("a");
		int a , b , c;
		fscanf(fp , "%d%d%d" , &a , &b , &c);
		if(head[a]->next == NULL)  //连接 b 到 head[a] 
		{
			head[a]->next = new struct node;
			head[a]->next->to = b;
			head[a]->next->value = c;
			head[a]->next->next = NULL;
		 } 
		else 
		{
			struct node *scan = head[a]->next;
			while(1)
			{
				if(scan->next == NULL)
					break;
				scan = scan->next;
			}
			scan->next = new struct node;
			scan = scan->next;
			scan->to = b;
			scan->value = c;
			scan->next = NULL;
		}
		if(head[b]->next == NULL)  //连接 a 到 head[b] 
		{
			head[b]->next = new struct node;
			head[b]->next->to = a;
			head[b]->next->value = c;
			head[b]->next->next = NULL;
		 } 
		else 
		{
			struct node *scan = head[b]->next;
			while(1)
			{
				if(scan->next == NULL)
					break;
				scan = scan->next;
			}
			scan->next = new struct node;
			scan = scan->next;
			scan->to = a;
			scan->value = c;
			scan->next = NULL;
		}
	}
	cout << "建图完成，当前无向图中有" << m << "个点，" << n << "条边\n"; 
}
void BFS(void)
{
	queue<int> q;
	int flag[10000];
	memset(flag , 0 , sizeof(flag));
	cout << "请选择从哪个节点开始遍历：";
	int tem;
	cin >> tem;
	fflush(stdin);
	if(tem > head_sum)
	{
		cout << "总共只有" << head_sum << "个节点，无法从该节点开始遍历";
		return ;
	}
	if(tem <= 0)
	{
		cout << "节点名称都是正整数，无法从该节点开始\n";
		return ;
	}
	q.push(tem);
	flag[tem] = 1;
	while(!q.empty())
	{
		int now = q.front();
		q.pop();
		cout << now << " ";
		struct node *scan = head[now]->next;
		while(scan != NULL)
		{
			if(flag[scan->to] == 0)
			{
				q.push(scan->to);
				flag[scan->to] = 1;
			}
			scan = scan->next;
		}
	}
}
void DFS(int now)
{
	if(mark[now] == 1)
	{
		return ;
	}
	else
	{
		cout << now << " ";
		mark[now] = 1;
		struct node *scan = head[now]->next;
		while(scan != NULL)
		{
			//printf("a");
			DFS(scan->to);
			scan = scan->next;
		}
	}
}
void test(void)
{
	for(int i = 1 ; i <= head_sum ; i++)
	{
		struct node *scan = head[i]->next;
		cout << "第" << i << "行链接表："; 
		while(scan != NULL)
		{
			cout << scan->to << " "; 
			scan = scan->next;
		}
		cout << endl;
	}
}
int main(void)
{
	head_sum = 0;
	while(1)
	{
		cout << "1、建图 2、遍历 3、搜索 4、最短路径 5、最小生成树 6、显示邻接表 7、退出\n";
		cout << "请选择想要进行的操作：";
		int tem;
		cin >> tem;
		fflush(stdin);
		if(tem == 1)
		{
			BuildGraph();
		}
		else if(tem == 2)
		{
			cout << "1、深度优先遍历 2、广度优先遍历\n";  
			cout << "请选择想要进行的遍历方式：";
			cin >> tem;
			if(tem == 1)
			{
				cout << "请选择从哪个节点开始遍历：";
				int tem;
				cin >> tem;
				fflush(stdin);
				if(tem > head_sum)
				{
					cout << "总共只有" << head_sum << "个节点，无法从该节点开始遍历";
					getchar();
					system("cls");
					continue; 
				}
				if(tem <= 0)
				{
					cout << "节点名称都是正整数，无法从该节点开始\n";
					getchar();
					system("cls");
					continue; 
				}
				memset(mark , 0 , sizeof(mark));
				DFS(tem);
				cout << endl;
			}
			else if(tem == 2)
			{
				BFS();
			}
		}
		else if(tem == 3)
		{
			cout << "1、指定边的权值 2、某顶点的第一个邻接顶点\n";
			cout << "请选择想要进行的搜索方式：";
			cin >> tem;
			if(tem == 1)
			{
				EdgeValue();
			}
			else if(tem == 2)
			{
				NextVertax();
			}
		}
		else if(tem == 4)
		{
			Floyd();
		}
		else if(tem == 5)
		{
			cout << "1、Prim 2、Kruskal\n"; 
			cout << "请选择使用什么方法：";
			cin >> tem;
			fflush(stdin);
			if(tem == 1)
			{
				Prim();
			}
			else if(tem == 2)
			{
				Kruskal();
			}
		}
		else if(tem == 6)
		{
			test();	
		 } 
		else if(tem == 7)
		{
			cout << "程序结束" << endl;
			break;
		 } 
		else 
		{
			cout << "请输入正确的数字\n";
		}
		getchar();
		system("cls");
	}
}
