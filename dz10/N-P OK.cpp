//////////////////////
////Voropaev Robert////
//MIPT/DIHT/592 group//
///////////////////////
//#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

class Graph
{
public:
	vector<pair<int, pair<int, int> > > MST_Kruskal(vector <pair<int, pair<int, int> > > Edge, int n);
private:
	void _makeSet(int v);
	int _findSet(int v);
	void _unionSet(int u, int v);
	vector<int> _parent;
	vector<int> _size;
};

vector<pair<int, pair<int, int> > > Graph::MST_Kruskal(vector <pair<int, pair<int, int> > > Edge, int n)// n - number of edge
{
	vector<pair<int, pair<int, int> > > res;
	vector<int> vertiesToSet;
	for (int i = 0; i < n; i++)
		_makeSet(i);
	sort(Edge.begin(), Edge.end());
	for (int i = 0; i < Edge.size(); i++)
	{
		int firstV = Edge[i].second.first, secondV = Edge[i].second.second;
		if (_findSet(firstV) != _findSet(secondV))
		{
			_unionSet(firstV, secondV);
			res.push_back(make_pair(Edge[i].first, make_pair(firstV, secondV)));
		}
	}
	return res;
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
	vector <pair<int, pair<int, int> > > Edge;
	int n, m;
	scanf("%d%d", &n, &m);
	for (int i = 0; i < m; i++)
	{
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		a--;
		b--;
		Edge.push_back(make_pair(c, make_pair(b, a)));
	}
	Graph G;
	vector<pair<int, pair<int, int> > > res = G.MST_Kruskal(Edge, n);
	int s = 0;
	for (int i = 0; i < res.size(); i++)
		s += res[i].first;
	printf("%d", s);
	//system("pause");
	return 0;
}