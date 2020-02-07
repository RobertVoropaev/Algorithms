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
	vector<int> getPath(int v);
	vector<int> getCycle();
private:
	vector<edge> _edges;
	int _n;
	int _lastVertex;
	int _lastBFVertex;
	vector<int> _parent;
	vector<int> _distance;
	void _preparation();
};

Graph::Graph(vector<edge> edges, int n)
{
	_edges = edges;
	_n = n;
}

void Graph::_preparation()
{
	_distance.clear();
	_parent.clear();
	for (int i = 0; i < _n; i++)
	{
		_distance.push_back(INT_MAX);
		_parent.push_back(-1);
	}
	
}

void Graph::Bellman_Ford(int v)
{
	_lastVertex = v;
	_preparation();
	_distance[v] = 0;
	for(int j =0; j < _n; j++)
	{
		_lastBFVertex = -1;
		for (int i = 0; i < _edges.size(); i++)
			if (_distance[_edges[i].begin] < INT_MAX)
				if (_distance[_edges[i].end] > _distance[_edges[i].begin] + _edges[i].weight)
				{
					_distance[_edges[i].end] = _distance[_edges[i].begin] + _edges[i].weight;
					_parent[_edges[i].end] = _edges[i].begin;
					_lastBFVertex = _edges[i].end;
				}
	}
}

int Graph::getDistance(int v)
{
	return _distance[v];
}

vector<int> Graph::getPath(int v)
{
	vector<int> path;
	if (_distance[v] != INT_MAX)
	{
		while (v != _lastVertex)
		{
			path.push_back(v);
			v = _parent[v];
		}
		path.push_back(v);
		reverse(path.begin(), path.end());
		return path;
	}
	else
		return path;
}

vector<int> Graph::getCycle()
{
	vector<int> cycle;
	if (_lastBFVertex == -1)
		return cycle;
	else
	{
		int y = _lastBFVertex;
		for (int i = 0; i < _n; i++)
			y = _parent[y];
		int c = y;
		while (true)
		{
			cycle.push_back(c);
			if (c == y && cycle.size() > 1)
				break;
			c = _parent[c];
		}
		reverse(cycle.begin(), cycle.end());
		return cycle;
	}
}

int main()
{
	int n;
	cin >> n;
	edge A;
	vector<edge> Edges;
	for(int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
		{
			int a;
			cin >> a;
			if (a != 100000)
			{
				A.begin = i; A.end = j; A.weight = a;
				Edges.push_back(A);
			}
		}
	Graph G(Edges, n);
	vector<bool> ver(n, false);//Достижимость вершин
	vector<int> cycle;
	for (int i = 0; i < n; i++)
	{
		if (!ver[i])
		{
			G.Bellman_Ford(i);
			for (int j = 0; j < n; j++)
				if (G.getDistance(j) != INT_MAX)
					ver[j] = true;
			cycle = G.getCycle();
			if (cycle.size()!=0)
				break;
		}
	}
	if (cycle.size() == 0)
		cout << "NO";
	else
	{
		cout << "YES" << endl;
		cout << cycle.size() << endl;
		for (int i = 0; i < cycle.size(); i++)
			cout << cycle[i] + 1<< " ";
	}
	//system("pause");
	return 0;
}