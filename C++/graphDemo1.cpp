#include <iostream>
#include <string>
#include "gragh.h"
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;

#define E 9 //图的边数
#define N 7//图的顶点数
#define INF 9999

typedef int vextype;  //顶点的数据类型
typedef int adjtype; //边的权值数据类型
//图的结构体定义
typedef struct
{
	vextype vexs[N];     //顶点信息
	adjtype adjs[N][N];  //领接矩阵
} graph;


graph* g = new graph();
int visit[N];

//初始化无向图
void Creat_graph(graph* g)
{
	int array[9][3] = { {0,1,28},{0,5,10},{1,6,14},{1,2,16},{4,5,25},{4,6,24},{3,4,22},{3,6,18},{2,3,12} };

	for (int i = 0; i < N; ++i)
	{
		g->vexs[i] = i;
	}

	//初始化邻接矩阵
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; j++)
		{
			g->adjs[i][j] = INF;
		}
	}
	for (int i = 0; i < E; ++i)
	{
		g->adjs[array[i][0]][array[i][1]] = array[i][2];
		g->adjs[array[i][1]][array[i][0]] = array[i][2];
	}
}

void DFSA(int i)
{
	visit[i] = 1;
	cout <<"current vex:"<< g->vexs[i] << ";";
	for (int j = 0; j < N; ++j)//依次遍历i顶点的邻接点
	{
		if ((g->adjs[i][j] != INF) && (visit[j] == 0))//与i相连且未被访问过
		{
			cout << "test adj:" << i << "->" << j << "(" << g->adjs[i][j] << ")" << endl;
			DFSA(j);
		}
	}
}

void dijkstra(int s) 
{
	std::vector<int> d;
	for (size_t i = 0; i < N; i++)    //源点离所有点的距离均记为无穷
	{
		d.push_back(INF);
	}
	d[s] = 0;       //源点离自身距离置为0
	for (size_t i = 0; i < N; i++)     
	{
		int u = -1;
		int min = INF;
		cout << "test vexs:";
		for (size_t j = 0; j < N; j++)     //寻找一个未访问过，且离源点最近的节点u
		{
			if (visit[j] == 0 && d[j] < min)
			{
				cout << j <<" ";
				u = j;
				min = d[j];
			}
		}
		cout << " --- " << "selected vex:"<< u << " --- ";
		if (u == -1)
			return;
		visit[u] = 1;                                  //标记u已被访问
		cout << "updated vexs:";
		for (int v = 0; v < N; ++v)
		{
			//遍历所有顶点，如果v未被访问&&u能够到达v&&以u为中介点可以使d[v]更优
			if (visit[v] == 0 && d[u] + g->adjs[u][v] < d[v])
			{
				cout << v << " ";
				d[v] = d[u] + g->adjs[u][v];             //更新d[v]
			}
		}
		cout << endl;
	}
	cout << "result:";
	for (size_t i = 0; i < N; i++)
	{
		cout << d[i] << " ";
	}
	cout << endl;
}

void prim(int s)
{
	std::vector<int> d;
	int pre[N];			//定义父结点列表
	for (size_t i = 0; i < N; i++)
	{
		d.push_back(INF);
	}
	d[s] = 0;     //源节点离树距离置为0
	pre[s] = s;   //父结点为自身
	for (size_t i = 0; i < N; i++) //循环N次，将所有节点入树
	{
		int k = -1;
		cout << "test vexs:";
		for (size_t j = 0; j < N; j++)
		{
			if (visit[j] == 0 && (k == -1 || d[k] > d[j]))  //寻找离树最近的节点
			{
				k = j;
				cout << k << " ";
			}
		}
		cout << " --- " << "selected vex:" << k << endl;
		visit[k] = 1;   //入树
		for (size_t j = 0; j < N; j++)    //更新离树距离
		{
			if (visit[j] == 0 && d[j] > g->adjs[k][j] && g->adjs[k][j] != INF)
			{
				d[j] = g->adjs[k][j];
				pre[j] = k;  //定义父结点
			}
		}
	}
	cout << endl << "result:" << endl;
	for (size_t i = 0; i < N; i++)
	{
		if(i == s)
			cout << "vex" << "(" << i << ")'s parent vex:" << "None" << endl;
		else
			cout << "vex" << "(" << i << ")'s parent vex:" << pre[i] << endl;
	}
}

void show()
{
	int source;
	cout << "please input a source(0-6):";
	cin >> source;
	if (source < 0||source >= N)
	{
		return;
	}
	cout << "1. dfs, 2. dijkstra, 3. prim" << endl;
	cout << "please select an algorithm:";
	int input;
	cin >> input;
	if (input == 1)
	{
		DFSA(source);
	}
	else if (input == 2)
	{
		dijkstra(source);
	}
	else if (input == 3)
	{
		prim(source);
	}
	else
	{
		return;
	}
	return;
}

void visitToZero()
{
	for (size_t i = 0; i < N; i++)
	{
		visit[i] = 0;
	}
}

int main() 
{
	Creat_graph(g);
	char t = 'n';
	while (1)
	{
		show();
		cout << "continue?(enter y or n)" << endl;
		cin >> t;
		if ( t== 'y')
		{
			system("cls");
			visitToZero();
		}
		else
		{
			return 0;
		}
		
	}
	return 0;
}