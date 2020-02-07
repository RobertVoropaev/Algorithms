//////////////////////
////Voropaev Robert////
//MIPT/DIHT/592 group//
///////////////////////
//#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

class Graph
{
public:
	Graph(int n);
	bool ask(int v1, int v2);
	void addEdge(pair<int,int> edge);
private:
	void _makeSet(int v);
	int _findSet(int v);
	void _unionSet(int u, int v);
	vector<int> _parent;
	vector<int> _size;
};

Graph::Graph(int n)
{
	for (int i = 0; i < n; i++)
		_makeSet(i);
}

void Graph::addEdge(pair<int,int> edge)
{
	if (_findSet(edge.first) != _findSet(edge.second))
		_unionSet(edge.first, edge.second);
}

bool Graph::ask(int v1, int v2)
{
	return _findSet(v1) == _findSet(v2);
}

void Graph::_makeSet(int v)
{
	int a = 1 + v - _parent.size();
	for (int i = 0; i < a; i++)
	{
		_size.push_back(1);
		_parent.push_back(-a + 1 + v + i);
	}
	_parent[v] = v;
}

int Graph::_findSet(int v)
{
	if (v == _parent[v])
		return v;
	else
		return _parent[v] = _findSet(_parent[v]);
}

void Graph::_unionSet(int u, int v)
{
	u = _findSet(u); v = _findSet(v);
	if (u != v)
	{
		if (_size[u] < _size[v])
			swap(u, v);
		_parent[v] = u;
		_size[u] += _size[v];
	}
}

int main()
{
	int n, m, k;
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 0; i < m; i++)
	{
		int a, b;
		scanf("%d%d", &a, &b);
	}
	Graph G(n);
	vector<vector<int> > command;//Первое число: 0 - спросить, 1 - разрезать; 2 и 3 число - номер вершин
	vector<int> R;
	for (int i = 0; i < k; i++)
	{
		R.clear();
		string str;
		cin >> str;
		if (str == "ask")
		{
			int a, b;
			scanf("%d%d", &a, &b);
			a--; b--;
			R.push_back(0); R.push_back(a); R.push_back(b);
			command.push_back(R);
		}
		else if (str == "cut")
		{
			int a, b;
			scanf("%d%d", &a, &b);
			a--; b--;
			R.push_back(1); R.push_back(a); R.push_back(b);
			command.push_back(R);
		}
	}
	reverse(command.begin(), command.end());
	vector<bool> answer;
	for (int i = 0; i < k; i++)
	{
		if (command[i][0])
		{
			pair<int,int> T;
			T.first = command[i][1]; T.second = command[i][2];
			G.addEdge(T);
		}
		else
			answer.push_back(G.ask(command[i][1], command[i][2]));
	}
	for (int i = answer.size()-1; i >= 0; i--)
	{
		if (answer[i])
			printf("YES\n");
		else
			printf("NO\n");
	}
	//system("pause");
	return 0;
}