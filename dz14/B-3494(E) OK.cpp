//////////////////////
////Voropaev Robert////
//MIPT/DIHT/592 group//
///////////////////////
#define _CRT_SECURE_NO_WARNINGS
#define INT_MAX 2009000999 

#include <iostream>
#include <vector>
//#include <limits.h>
#include <set>
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
	vector<vector<pair<int, int> > > _adjList;
	vector<int> _distance;
	vector<bool> _visit;
	set<pair<int, int> > _distanceAndVertex;
	vector<int> _parent;
	void _relax(int v, int u, int w);
	void _preparation();
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
		_distanceAndVertex.erase(make_pair(_distance[u], u));
		_distance[u] = _distance[v] + w;
		_parent[u] = v;
		_distanceAndVertex.insert(make_pair(_distance[u], u));
	}
}

void Graph::_preparation()
{
	if (_distance.size() == 0)
		for (int i = 0; i < _adjList.size(); i++)
		{
			_distance.push_back(INT_MAX);
			_distanceAndVertex.insert(make_pair(INT_MAX, i));
			_parent.push_back(-1);
		}
	else
	{
		_distanceAndVertex.clear();
		for (int i = 0; i < _adjList.size(); i++)
		{
			_distance[i] = INT_MAX;
			_distanceAndVertex.insert(make_pair(INT_MAX, i));
			_parent[i] = -1;
		}
	}
}

void Graph::Dijkstra(int v)
{
	_lastVertex = v;
	_preparation();
	_distanceAndVertex.erase(make_pair(_distance[v], v));
	_distance[v] = 0;
	_distanceAndVertex.insert(make_pair(_distance[v], v));
	while (!_distanceAndVertex.empty())
	{
		v = _distanceAndVertex.begin()->second;
		_distanceAndVertex.erase(_distanceAndVertex.begin());
		for (int j = 0; j < _adjList[v].size(); j++)
				_relax(v, _adjList[v][j].first, _adjList[v][j].second);
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
	int N;
	scanf("%d", &N);
	vector<vector<int> > results(N);
	for (int i = 0; i < N; i++)
	{
		int n, m;
		scanf("%d%d", &n, &m);
		vector<vector<pair<int, int> > > adjList(n);
		for (int j = 0; j < m; j++)
		{
			int a, b, w;
			scanf("%d%d%d", &a, &b, &w);
			adjList[a].push_back(make_pair(b, w));
			adjList[b].push_back(make_pair(a, w));
		}
		Graph G(adjList);
		int v;
		scanf("%d", &v);
		G.Dijkstra(v);
		for (int j = 0; j < n; j++)
			results[i].push_back(G.getDistance(j));
	}
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < results[i].size(); j++)
			printf("%d ", results[i][j]);
		printf("\n");
	}
	//system("pause");
	return 0;
}