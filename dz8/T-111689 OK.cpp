//////////////////////
////Voropaev Robert////
//MIPT/DIHT/592 group//
///////////////////////
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <list>
#include <algorithm>
#include <stdio.h>
#include <math.h>
#include <cmath>
#include <limits.h>
#include <set>
#include <map>

using namespace std;

class Graph
{
public:
	Graph(vector<vector<int> > adjList, multimap<pair<int, int>, int> edges);
	set<int> getBridges();
private:
	vector<vector<int> > _adjList;
	multimap<pair<int, int>, int>  _edges;
	void _dfs(int v, int parent);
	void _preparation();
	vector<char> _colors;
	int _timer;
	vector<int> _tin, _fup;
	set<int> _bridges;
};

Graph::Graph(vector<vector<int> > adjList, multimap<pair<int, int>, int> edges)
{
	_adjList = adjList;
	_edges = edges;
}

void Graph::_preparation()
{
	for (int i = 0; i < _adjList.size(); i++)
	{
		_colors.push_back('W');
		_tin.push_back(INT_MAX);
		_fup.push_back(INT_MAX);
	}
	_timer = 0;
	_bridges.clear();
}

void Graph::_dfs(int v, int parent)
{
	_colors[v] = 'G';
	_tin[v] = _fup[v] = _timer++;
	for (int i = 0; i < _adjList[v].size(); i++)
	{
		int u = _adjList[v][i];
		if (u != parent)
		{
			if (_colors[u] == 'G')
				_fup[v] = min(_fup[v], _tin[u]);
			if (_colors[u] == 'W')
			{
				_dfs(u, v);
				_fup[v] = min(_fup[v], _fup[u]);
				if ((_fup[u] > _tin[v]) && (_edges.count(make_pair(v, u)) == 1))
					_bridges.insert(_edges.find(make_pair(v, u))->second);
			}
		}
	}
	_colors[v] = 'B';
}

set<int> Graph::getBridges()
{
	_preparation();
	for (int i = 0; i < _adjList.size(); i++)
		if (_colors[i] == 'W')
			_dfs(i, -1);
	return _bridges;
}

int main()
{
	int n, m;
	scanf("%d%d", &n, &m);
	vector<vector<int> > adjList(n);
	multimap<pair<int, int>, int> edges;
	int k = 1;
	for (int i = 0; i < m; i++)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		a--; b--;
		adjList[a].push_back(b); 
		adjList[b].push_back(a);
		edges.insert(make_pair(make_pair(a, b), k)); 
		edges.insert(make_pair(make_pair(b, a), k++));
	}
	Graph G(adjList, edges);
	set<int> bridges = G.getBridges();
	set<int>::iterator p = bridges.begin();
	printf("%d\n", bridges.size());
	while (p != bridges.end())
	{
		printf("%d\n", *p);
		p++;
	}
	//system("pause");
	return 0;
}