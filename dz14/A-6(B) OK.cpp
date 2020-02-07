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

class Graph
{
public:
	Graph(vector<vector<pair<int, int> > > adjList);
	void Dijkstra(int v);
	int getDistance(int v);
	vector<int> getPath(int v);
private:
	vector<vector<pair<int,int> > > _adjList;
	vector<int> _distance;
	vector<bool> _visit;
	vector<int> _parent;
	void _relax(int v, int u, int w);
	void _preparation();
	int _getMinvertex();
	int _lastVertex;
};

Graph::Graph(vector<vector<pair<int, int> > > adjList)
{
	_adjList = adjList;
}

void Graph::_relax(int v, int u, int w)
{
		if (_distance[u] > _distance[v] + w)
		{
			_distance[u] = _distance[v] + w;
			_parent[u] = v;
		}
}

void Graph::_preparation()
{
	//if (_distance.size()==0)
		for (int i = 0; i < _adjList.size(); i++)
		{
			_distance.push_back(INT_MAX);
			_visit.push_back(false);
			_parent.push_back(-1);
		}
		/*
	else
		for (int i = 0; i < _adjList.size(); i++)
		{
			_distance[i] = INT_MAX;
			_visit[i] = false;
			_parent[i] = -1;
		}
		*/
}

int Graph::_getMinvertex()
{
	int min = INT_MAX, index  = 0;
	for (int i = 0; i < _adjList.size(); i++)
		if (!_visit[i] && _distance[i] < min)
		{
			min = _distance[i];
			index = i;
		}
	return index;
}

void Graph::Dijkstra(int v)
{
	_lastVertex = v;
	_preparation();
	_distance[v] = 0;
	for (int i = 0; i < _adjList.size(); i++)
	{
		v = _getMinvertex();
		for (int j = 0; j < _adjList[v].size(); j++)
			if (!_visit[_adjList[v][j].first])
				_relax(v, _adjList[v][j].first, _adjList[v][j].second);
		_visit[v] = true;
	}
}

int Graph::getDistance(int v)
{
	return _distance[v];
}

vector<int> Graph::getPath(int v)
{
	vector<int> Path;
	while (v != _lastVertex)
	{
		Path.push_back(v);
		v = _parent[v];
	}
	Path.push_back(v);
	reverse(Path.begin(), Path.end());
	return Path;
}

int main()
{
	int n, s, f;
	scanf("%d%d%d", &n, &s, &f);
	vector<vector<pair<int, int> > > adjList;
	vector<pair<int, int> > edge;
	for (int i = 0; i < n; i++)
	{
		edge.clear();
		for (int j = 0; j < n; j++)
		{
			int a;
			scanf("%d", &a);
			if (a >= 0)
				edge.push_back(make_pair(j, a));
		}
		adjList.push_back(edge);
	}
	Graph G(adjList);
	G.Dijkstra(s-1);
	int distance = G.getDistance(f - 1);
	if (distance != INT_MAX)
	{
		printf("%d\n", distance);
		vector<int> Path = G.getPath(f - 1);
		printf("%d\n", Path.size());
		for (int i = 0; i < Path.size(); i++)
			printf("%d ", Path[i] + 1);	
	}
	else
		printf("-1");
	//system("pause");
	return 0;
}