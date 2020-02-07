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

using namespace std;

class Graph
{
public:
	Graph(vector<vector<int> > adjList);
	set<int> getCutPoints();
private:
	vector<vector<int> > _adjList;
	void _dfs(int v, int parent);
	void _preparation();
	vector<char> _colors;
	int _timer;
	vector<int> _tin, _fup;
	set<int> _cutPoints;
};

Graph::Graph(vector<vector<int> > adjList)
{
	_adjList = adjList;
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
	_cutPoints.clear();
}

void Graph::_dfs(int v, int parent)
{
	_colors[v] = 'G';
	_tin[v] = _fup[v] = _timer++;
	int children = 0;
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
				if ((_fup[u] >= _tin[v]) && (parent != -1))
					_cutPoints.insert(v);
				children++;
			}
		}
	}
	if ((parent == -1) && (children > 1))
		_cutPoints.insert(v);
	_colors[v] = 'B';
}

set<int> Graph::getCutPoints()
{
	_preparation();
	for (int i = 0; i < _adjList.size(); i++)
		if (_colors[i]=='W')
			_dfs(i, -1);
	return _cutPoints;
}

int main()
{
	int n, m;
	scanf("%d%d", &n, &m);
	vector<vector<int> > adjList(n);
	for (int i = 0; i < m; i++)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		a--; b--;
		adjList[a].push_back(b);
		adjList[b].push_back(a);
	}
	Graph G(adjList);
	set<int> cutPoints = G.getCutPoints();
	set<int>::iterator p = cutPoints.begin();
	printf("%d\n", cutPoints.size());
	while (p != cutPoints.end())
	{
		printf("%d\n", *p+1);
		p++;
	}
	//system("pause");
	return 0;
}