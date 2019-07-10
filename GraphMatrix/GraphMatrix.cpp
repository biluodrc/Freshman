#include<iostream>
#include<cstring>
#include<cstdlib>
#include<queue>
#include<stack>
using namespace std;

#define INF 1000000L

int Graph[100][100];
int pflag[100];
int point;
int kflag[100];
void BuildGraph(void);  //
void EdgeValue(void);  //
void InsertVer(void);  //
void InsertEdge(void);  //
void DelVer(void);  // 
void DelEdge(void);  // 
void FindNext(void);  //
void BFS(void);  //
void DFS(int now);  //
void Topo(void);  // 
void KeyWay(void);
void Dij(void);  // 
void Floyd(void);  // 
void Test(void);  //

int main(void)
{
	cout << "进入程序\n";
	int tem;
	while(1)
	{
		cout << "1、建图 2、遍历 3、添加 4、删除 5、查找 6、拓扑排序 7、关键路径 8、最短路 9、测试 10、退出\n";
		cout << "请选择想要进行的操作：";
		cin >> tem;
		if(tem == 1)
		{
			BuildGraph();
		}
		else if(tem == 2)
		{
			cout << "1、BFS 2、DFS\n";
			cout << "请选择遍历的方式：";
			cin >> tem;
			if(tem == 1)
			{
				BFS();
			}
			else if(tem == 2)
			{
				cout << "从哪个节点开始遍历：";
				cin >> tem;
				if(pflag[tem] == 0)
				{
					cout << "请先插入这个点\n";
					continue;
				}
				int flag = 0;
				for(int i = 1 ; i <= point ; i++)
				{
					if(Graph[tem][i] != INF)
						break;
					if(i == point)
					{
						cout << "这个节点是孤立的\n";
						flag = 1;
					}
				}
				if(flag)
					continue;
				memset(kflag , 0 , sizeof(kflag));
				DFS(tem);
				kflag[tem] = 1; 
				for(int i = 1 ; i <= point ; i++)
				{
					for(int j = 1 ; j < 100 ; j++)
					{
						if(kflag[j] == 0 && pflag[j] == 1)
						{
							cout << endl;
							DFS(j);
							kflag[j] = 1;
						}
					}
				}
				cout << endl;
			}
		}
		else if(tem == 3)
		{
			cout << "1、插入点 2、插入边\n";
			cout << "请选择：";
			cin >> tem;
			if(tem == 1)
			{
				InsertVer();
			}
			else if(tem == 2)
			{
				InsertEdge();
			}
		}
		else if(tem == 4)
		{
			cout << "1、点 2、边\n";
			cout << "请选择删除方式：";
			cin >> tem;
			if(tem == 1)
			{
				DelVer();
			}
			else if(tem == 2)
			{
				DelEdge();
			}
		}
		else if(tem == 5)
		{
			cout << "1、指定边权值 2、某定点第一个邻接点\n";
			cout << "请选择：";
			cin >> tem;
			if(tem == 1)
			{
				EdgeValue();
			 } 
			else if(tem == 2)
			{
				FindNext();
			} 
		}
		else if(tem == 6)
		{
			Topo();
		}
		else if(tem == 7)
		{
			KeyWay();
		}
		else if(tem == 8)
		{
			cout << "1、单源最短路 2、任意顶点最短路\n";
			cout << "请选择：";
			cin >> tem;
			if(tem == 1)
			{
				Dij();
			}
			else if(tem == 2)
			{
				Floyd();
			}
		}
		else if(tem == 9)
		{
			Test();
		 } 
		else if(tem == 10)
		{
			cout << "程序结束\n"; 
			break;
		}
		fflush(stdin);
		getchar();
		system("cls");
	}
}

void BuildGraph(void)
{
	FILE *fp = fopen("Graph.txt" , "r");
	int tem;
	int from , to , value;
	fscanf(fp , "%d %d" , &point , &tem);
	memset(Graph , 0 , sizeof(Graph));
	for(int i = 1 ; i <= point ; i++)
		for(int j = 1 ; j <= point ; j++)
			Graph[i][j] = INF;
	while(tem--)
	{
		fscanf(fp , "%d%d%d" , &from , &to , &value);
		Graph[from][to] = value;
		pflag[from] = 1;
		pflag[to] = 1;
	}
//	for(int i = 1 ; i <= point ; i++)
//	{
//		for(int j = 1 ; j <= point ; j++)
//			cout << Graph[i][j] << ' ';
//		cout << endl;
//	}
}
void EdgeValue(void)
{
	cout << "请输入边的起终点编号：";
	int from , to;
	cin >> from >> to;
	if(Graph[from][to] == INF)
	{
		cout << "这两个节点之间没有边\n";
		return;
	}
	else
	{
		cout << "这是这个边的权值：" << Graph[from][to] << endl;
		return;
	}
}
void InsertVer(void)
{
	int tem;
	cout << "请选择编号：";
	cin >> tem;
	pflag[tem] = 1;
	if(tem > point)
		point++;
}
void InsertEdge(void)
{
	int from , to , value;
	cout << "请输入插入边的起终点及边权：";
	cin >> from >> to >> value;
	if(pflag[from] == 0 || pflag[to] == 0)
	{
		cout << "请先插入点\n";
		return;
	}
	Graph[from][to] = value;
}
void BFS(void)
{
	int start;
	cout << "从哪个节点开始广搜：";
	cin >> start;
	if(pflag[start] == 0)
	{
		cout << "请先插入这个点\n";
		return;
	}
	for(int i = 1 ; i <= point ; i++)
	{
		if(Graph[start][i] != INF)
			break;
		if(i == point)
		{
			cout << "这个点是孤立的\n";
			return;
		}
	}
	int flag[100];
	memset(flag , 0 , sizeof(flag));
	queue<int> q;
	q.push(start);
	flag[start] = 1;
	while(!q.empty())
	{
		int now = q.front();
		q.pop();
		cout << now << ' ';
		for(int i = 1 ; i <= point ; i++)
		{
			if(Graph[now][i] != INF && flag[i] == 0)
			{
				q.push(i);
				flag[i] = 1;
			}
		}
	}
	for(int i = 1 ; i <= point ; i++)
	{
		for(int i = 1 ; i < 100 ; i++)
		{
			if(pflag[i] == 1 && flag[i] == 0)
			{
				cout << endl;
				start = i;
				q.push(start);
				flag[start] = 1;
				while(!q.empty())
				{
					int now = q.front();
					q.pop();
					cout << now << ' ';
					for(int i = 1 ; i <= point ; i++)
					{
						if(Graph[now][i] != INF && flag[i] == 0)
						{
							q.push(i);
							flag[i] = 1;
						}
					}
				}
			}
		}
	} 
	cout << endl;
}
void FindNext(void)
{
	cout << "查找那个节点的下一个节点：";
	int tem;
	cin >> tem;
	if(pflag[tem] == 0)
	{
		cout << "请先插入这个点\n";
		return;
	}
	for(int i = 1 ; i <= point ; i++)
	{
		if(Graph[tem][i] && i != tem)
		{
			cout << i << "：是所求节点\n";
			return;
		}
	}
}
void DFS(int now)
{

	cout << now << ' ';
	for(int i = 1 ; i <= point ; i++)
	{
		if(Graph[now][i] != INF && kflag[i] == 0)
		{
			kflag[i] = 1;
			DFS(i);
		}
	}
}
void DelVer(void)
{
	cout << "删除哪个节点：";
	int tem;
	cin >> tem;
	if(tem > point)
	{
		cout << "建起来的图中本来就没有这个点\n";
		return;
	}
	for(int i = 1 ; i <= point ; i++)
	{
		Graph[tem][i] = INF;
		Graph[i][tem] = INF;
	}
	pflag[tem] = 0;
}
void DelEdge(void)
{
	cout << "请输入删除边的起终点：";
	int from , to;
	cin >> from >> to;
	if(Graph[from][to] == INF || from > point || to > point)
	{
		cout << "这两点之间并没有边\n";
		return;
	}
	Graph[from][to] = INF;
}
void Topo(void)
{
	int du[100];
	memset(du , 0 , sizeof(du));
	for(int i = 1 ; i <= point ; i++)
	{
		for(int j = 1 ; j <= point ; j++)
		{
			if(Graph[i][j] != INF)
				du[j]++;
		}
	}
//	for(int i = 1 ; i <= point ; i++)
//		cout << du[i] <<  ' '; 
	//cout << endl;
	queue<int> q;
	for(int i = 1 ; i <= point ; i++)
	{
		if(pflag[i] == 1 && du[i] == 0)
		{
			q.push(i);
			du[i]--;
		}
	}
	int pp = 0;
	for(int i = 1 ; i <= point ; i++)
		if(pflag[i] == 1)
			pp++;
	for(int i = 1 ; i <= pp ; i++)
	{
		if(q.empty())
		{
			cout << "有回路\n";
			break;
		}
		int now = q.front();
		q.pop();
		cout << now << ' ';
		du[now]--;
		for(int j = 1 ; j <= point ; j++)
		{
			if(Graph[now][j] != INF)
				du[j]--;
			if(pflag[j] == 1 && du[j] == 0)
			{
				du[j]--;
				q.push(j);
			}
		}
	}
	cout << "：这个是一种拓扑排序"<< endl;
 } 
void KeyWay(void)
{
	int ve[100] , vl[100] , e , l;
	int path[100];
	memset(path , 0 , sizeof(path));
	for(int i = 1 ; i <= point ; i++)
	{
		ve[i] = 0;
	}
	for(int i = 1 ; i <= point ; i++)
	{
		for(int j = 1 ; j <= point ; j++)
		{
			if(Graph[i][j] != INF && ve[i] + Graph[i][j] > ve[j])
				ve[j] = ve[i] + Graph[i][j];
		}
	}
//	for(int i = 1 ; i <= point ; i++)
//		cout << ve[i] << ' ';
//	cout << endl;
	for(int i = 1 ; i <= point ; i++)
	{
		vl[i] = ve[point];
	}
	for(int i = point - 1 ; i >= 1 ; i--)
	{
		for(int j = 1 ; j <= point ; j++)
		{
			if(Graph[i][j] != INF && vl[j] - Graph[i][j] < vl[i])
				vl[i] = vl[j] - Graph[i][j];
		}
	}
//	for(int i = 1 ; i <= point ; i++)
//		cout << vl[i] << ' ';
//	cout << endl;
	for(int i = 1 ; i <= point ; i++)
	{
		for(int j = 1 ; j <= point ; j++)
		{
			e = ve[i];
			l = vl[j] - Graph[i][j];
			if(e == l)
			{
				cout << i << ' ' << j << endl;
				path[i] = j;
			}
		}
	}
	cout << "这些就是关键事件\n"; 
	int now = 1;
	for(int i = 1 ; i < point ; i++)
		if(path[i] != 0)
		{
			now = i;
			break;
		}
	
	while(1)
	{
		if(path[now] == 0)
		{
			cout << now;
			break;
		}
		cout << now << ' ';
		now = path[now];
	}
	cout << "：这个是关键路径"; 
}
void Dij(void)
{
	int dist[100];
	int flag[100];
	int v[100];
	cout << "请选择源点：";
	int from;
	cin >> from;
	for(int i = 1 ; i <= point ; i++)
	{
		dist[i] = INF;
		flag[i] = 0;
		v[i] = -1;
	}
	for(int i = 1 ; i <= point ; i++)
	{
		if(Graph[from][i] != INF)
		{
			dist[i] = Graph[from][i];
			v[i] = from;
		}
	}
	dist[from] = 0;
	flag[from] = 1;
	for(int i = 1 ; i < point ; i++)
	{
		for(int j = 1 ; j <= point ; j++)
		{
			if(Graph[i][j] != INF)
			{
				if(dist[j] > dist[i] + Graph[i][j])
				{
					dist[j] = dist[i] + Graph[i][j];
					v[j] = i;
				}
			}
		}
	}
//	cout << "dist:";  //比较弱的显示方式 
//	for(int i = 1 ; i <= point ; i++)
//	{
//		cout << dist[i] << ' ';
//	}
//	cout << "\nv:";
//	for(int i = 1 ; i <= point ; i++)
//	{
//		cout << v[i] << ' ';
//	}
//	cout << endl;
	for(int i = 1 ; i <= point ; i++)  //看起来更舒服的显示方式 
	{
		if(i == from)
			continue;
		if(dist[i] == INF)
		{
			cout << "源点到不了" << i << "点" << endl << endl;
			continue; 
		}
		cout << "源点到" << i << "点的最短距离为" << dist[i] << endl; 
		int now = i;
		stack<int> path;
		while(now != from)
		{
			path.push(now);
			now = v[now];
		}
		path.push(from);
		cout << "路径为：";
		cout << path.top();
		path.pop();
		while(!path.empty())
		{
			cout << "->" << path.top();
			path.pop();
		 }
		cout << endl << endl;
	}
}
void Floyd(void)
{
	int A[100][100];
	for(int i = 1 ; i <= point ; i++)
	{
		for(int j = 1 ; j <= point ; j++)
		{
			A[i][j] = Graph[i][j];
		}
	}
//	for(int i = 1 ; i <= point ; i++)
//	{
//		for(int j = 1 ; j <= point ; j++)
//		{
//			cout << A[i][j] << " "; 
//		}
//		cout << endl;
//	}
	for(int k = 1 ; k <= point ; k++)
	{
		for(int i = 1 ; i <= point ; i++)
		{
			for(int j = 1 ; j <= point ; j++)
			{
				if(A[i][k] + A[k][j] < A[i][j])
				{
					A[i][j] = A[i][k] + A[k][j];
				}
			}
		}
	}
	for(int i = 1 ; i <= point ; i++)
	{
		for(int j = 1 ; j <= point ; j++)
		{
			if(A[i][j] == INF)
			{
				cout << "无 ";
			}
			else
			{
				printf("%-2d " , A[i][j]);
			}
		}
		cout << endl;
	}
}

void Test(void)
{
	for(int i = 1 ; i <= point ; i++)
	{
		for(int j = 1 ; j <= point ; j++)
		{
			if(Graph[i][j] == INF)
				cout << "INF ";
			else
				printf("%3d " , Graph[i][j]);
		}
		cout << endl;
	}
 } 