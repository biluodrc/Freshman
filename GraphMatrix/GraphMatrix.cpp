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
	cout << "�������\n";
	int tem;
	while(1)
	{
		cout << "1����ͼ 2������ 3����� 4��ɾ�� 5������ 6���������� 7���ؼ�·�� 8�����· 9������ 10���˳�\n";
		cout << "��ѡ����Ҫ���еĲ�����";
		cin >> tem;
		if(tem == 1)
		{
			BuildGraph();
		}
		else if(tem == 2)
		{
			cout << "1��BFS 2��DFS\n";
			cout << "��ѡ������ķ�ʽ��";
			cin >> tem;
			if(tem == 1)
			{
				BFS();
			}
			else if(tem == 2)
			{
				cout << "���ĸ��ڵ㿪ʼ������";
				cin >> tem;
				if(pflag[tem] == 0)
				{
					cout << "���Ȳ��������\n";
					continue;
				}
				int flag = 0;
				for(int i = 1 ; i <= point ; i++)
				{
					if(Graph[tem][i] != INF)
						break;
					if(i == point)
					{
						cout << "����ڵ��ǹ�����\n";
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
			cout << "1������� 2�������\n";
			cout << "��ѡ��";
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
			cout << "1���� 2����\n";
			cout << "��ѡ��ɾ����ʽ��";
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
			cout << "1��ָ����Ȩֵ 2��ĳ�����һ���ڽӵ�\n";
			cout << "��ѡ��";
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
			cout << "1����Դ���· 2�����ⶥ�����·\n";
			cout << "��ѡ��";
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
			cout << "�������\n"; 
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
	cout << "������ߵ����յ��ţ�";
	int from , to;
	cin >> from >> to;
	if(Graph[from][to] == INF)
	{
		cout << "�������ڵ�֮��û�б�\n";
		return;
	}
	else
	{
		cout << "��������ߵ�Ȩֵ��" << Graph[from][to] << endl;
		return;
	}
}
void InsertVer(void)
{
	int tem;
	cout << "��ѡ���ţ�";
	cin >> tem;
	pflag[tem] = 1;
	if(tem > point)
		point++;
}
void InsertEdge(void)
{
	int from , to , value;
	cout << "���������ߵ����յ㼰��Ȩ��";
	cin >> from >> to >> value;
	if(pflag[from] == 0 || pflag[to] == 0)
	{
		cout << "���Ȳ����\n";
		return;
	}
	Graph[from][to] = value;
}
void BFS(void)
{
	int start;
	cout << "���ĸ��ڵ㿪ʼ���ѣ�";
	cin >> start;
	if(pflag[start] == 0)
	{
		cout << "���Ȳ��������\n";
		return;
	}
	for(int i = 1 ; i <= point ; i++)
	{
		if(Graph[start][i] != INF)
			break;
		if(i == point)
		{
			cout << "������ǹ�����\n";
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
	cout << "�����Ǹ��ڵ����һ���ڵ㣺";
	int tem;
	cin >> tem;
	if(pflag[tem] == 0)
	{
		cout << "���Ȳ��������\n";
		return;
	}
	for(int i = 1 ; i <= point ; i++)
	{
		if(Graph[tem][i] && i != tem)
		{
			cout << i << "��������ڵ�\n";
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
	cout << "ɾ���ĸ��ڵ㣺";
	int tem;
	cin >> tem;
	if(tem > point)
	{
		cout << "��������ͼ�б�����û�������\n";
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
	cout << "������ɾ���ߵ����յ㣺";
	int from , to;
	cin >> from >> to;
	if(Graph[from][to] == INF || from > point || to > point)
	{
		cout << "������֮�䲢û�б�\n";
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
			cout << "�л�·\n";
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
	cout << "�������һ����������"<< endl;
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
	cout << "��Щ���ǹؼ��¼�\n"; 
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
	cout << "������ǹؼ�·��"; 
}
void Dij(void)
{
	int dist[100];
	int flag[100];
	int v[100];
	cout << "��ѡ��Դ�㣺";
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
//	cout << "dist:";  //�Ƚ�������ʾ��ʽ 
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
	for(int i = 1 ; i <= point ; i++)  //���������������ʾ��ʽ 
	{
		if(i == from)
			continue;
		if(dist[i] == INF)
		{
			cout << "Դ�㵽����" << i << "��" << endl << endl;
			continue; 
		}
		cout << "Դ�㵽" << i << "�����̾���Ϊ" << dist[i] << endl; 
		int now = i;
		stack<int> path;
		while(now != from)
		{
			path.push(now);
			now = v[now];
		}
		path.push(from);
		cout << "·��Ϊ��";
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
				cout << "�� ";
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