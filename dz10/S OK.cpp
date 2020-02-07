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
	int sum(int v);
	void addEdge(pair<int, pair<int, int> > edge);
private:
	vector<pair<int, pair<int, int> > > _Edge;
	void _makeSet(int v);
	int _findSet(int v);
	int _unionSet(int u, int v);
	vector<int> _parent;
	vector<int> _size;
	vector<int> _weight;
};

Graph::Graph(int n)
{
	for (int i = 0; i < n; i++)
		_makeSet(i);
}

void Graph::addEdge(pair <int, pair <int, int> > edge)
{
	int i = _findSet(edge.second.first);
	if (_findSet(edge.second.first) != _findSet(edge.second.second))
		i = _unionSet(edge.second.first, edge.second.second);
	_weight[i] += edge.first;
	
}

int Graph::sum(int v)
{
	return _weight[_findSet(v)];
}

void Graph::_makeSet(int v)
{
	int a = 1 + v - _parent.size();
	for (int i = 0; i < a; i++)
	{
		_size.push_back(1);
		_weight.push_back(0);
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

int Graph::_unionSet(int u, int v)
{
	u = _findSet(u); v = _findSet(v);
	if (u != v)
	{
		if (_size[u] < _size[v])
			swap(u, v);
		_parent[v] = u;
		_size[u] += _size[v];
		_weight[u] += _weight[v];
	}
	return u;
}

int main()
{
	int n, m;
	scanf("%d%d", &n, &m);
	Graph G(n);
	for (int i = 0; i < m; i++)
	{
		int command;
		scanf("%d", &command);
		if (command == 1)
		{
			int a, b, c;
			scanf("%d%d%d", &a, &b, &c);
			a--; b--;
			G.addEdge(make_pair(c, make_pair(a, b)));
		}
		else
		{
			int v;
			scanf("%d", &v);
			v--;
			printf("%d\n", G.sum(v));
		}
	}
	//system("pause");
	return 0;
}