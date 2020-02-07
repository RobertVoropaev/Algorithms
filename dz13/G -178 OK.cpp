//////////////////////
////Voropaev Robert////
//MIPT/DIHT/592 group//
///////////////////////
#define _CRT_SECURE_NO_WARNINGS


#include <iostream>
#include <vector>
#include <limits.h>
#include <cstdio>
#include <algorithm>

using namespace std;

struct edge
{
	int begin, end, weight;
};

class Graph
{
public:
	Graph(vector<edge> edges, int n);
	void Bellman_Ford(int v);
	int getDistance(int v);
private:
	vector<edge> _edges;
	int _n;
	vector<int> _distance;
	void _relax(int v, int u, int w);
	void _preparation();
};

Graph::Graph(vector<edge> edges, int n)
{
	_edges = edges;
	_n = n;
}

void Graph::_relax(int v, int u, int w)
{
	if (_distance[u] > _distance[v] + w)
		_distance[u] = _distance[v] + w;
}

void Graph::_preparation()
{
	for (int i = 0; i < _n; i++)
		_distance.push_back(INT_MAX);
}

void Graph::Bellman_Ford(int v)
{
	_preparation();
	_distance[v] = 0;
	while (true)
	{
		bool any = false;
		for (int i = 0; i < _edges.size(); i++)
			if (_distance[_edges[i].begin] < INT_MAX)
			{
				int v = _edges[i].begin, u =  _edges[i].end, w = _edges[i].weight;
				if (_distance[u] > _distance[v] + w)
				{
					_distance[u] = _distance[v] + w;
					any = true;
				}
			}
		if (!any)
			break;
	}
}

int Graph::getDistance(int v)
{
	return _distance[v];
}

int main()
{
	int n, m;
	cin >> n >> m;
	edge A;
	vector<edge> edges;
	for (int i = 0; i < m; i++)
	{
		cin >> A.begin >> A.end >> A.weight;
		A.begin--; A.end--;
		edges.push_back(A);
	}
	Graph G(edges, n);
	G.Bellman_Ford(0);
	for (int i = 0; i < n; i++)
	{
		int d = G.getDistance(i);
		if (d < INT_MAX)
			cout << d << " ";
		else
			cout << 30000 << " ";
	}
	//system("pause");
	return 0;
}