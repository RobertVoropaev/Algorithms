//////////////////////
////Voropaev Robert////
//MIPT/DIHT/592 group//
///////////////////////
//#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdio>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

class Graph
{
public:
	pair<int, int> MST_Kruskal(vector <pair<int, int> > Edge, int n);
private:
	void _makeSet(int v);
	int _findSet(int v);
	void _unionSet(int u, int v);
	vector<int> _parent;
	vector<int> _size;
}; 

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


pair<int, int> Graph::MST_Kruskal(vector <pair<int, int> > Edge, int n)
{
	for (int i = 0; i < n; i++)
		_makeSet(i);
	pair <int, int> edge;
	for (int i = 0; i < Edge.size(); i++)
	{
		int firstV = Edge[i].first, secondV = Edge[i].second;
		if (_findSet(firstV) != _findSet(secondV))
		{
			_unionSet(firstV, secondV);
			edge.first = firstV; edge.second = secondV;
		}
	}
	return edge;
}

int main()
{
	vector <pair<int, int> > Edge;
	int n, m;
	scanf("%d%d", &n, &m);
	for (int i = 0; i < m; i++)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		Edge.push_back(make_pair(b, a));
	}
	Graph G;
	pair<int, int> lastEdge = G.MST_Kruskal(Edge, n);
	int i = 0;
	while (lastEdge != Edge[i])
		i++;
	cout << i+1;
	//system("pause");
	return 0;
}