///////////////////////
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

using namespace std;

class Graph
{
public:
	Graph(vector<vector<int> > adjList);
	vector<vector<int> > stronglyConnectedComponents();
private:
	vector<vector<int> > _adjList;
	void _DFSvisit(int u);
	void _tranporate();
	vector<char> _DFScolors;
	void _DFSpreparationColParTime();
	bool _DFSdoesNotStart;
	vector<int> _vertiesInTopologicalOrder;
	vector<int> _vertiesInTraversalOrder;
	vector<vector<int> > _DFSconnectedComponents;
	bool _searchConComp;
	void _DFS();
};

Graph::Graph(vector<vector<int> > adjList)
{
	vector<int> A;
	for (int i = 0; i < adjList.size(); i++)
	{
		_adjList.push_back(A);
		for (int j = 0; j < adjList[i].size(); j++)
			_adjList[i].push_back(adjList[i][j]);
	}
	_DFSdoesNotStart = true; //DFS ни разу не запускался
}

void Graph::_DFS()
{
	_DFSpreparationColParTime();
	for (int u = 0; u < _adjList.size(); u++)
		if (_DFScolors[_vertiesInTraversalOrder[u]] == 'W')
		{
			_DFSvisit(_vertiesInTraversalOrder[u]);
			if (_searchConComp)
			{
				_DFSconnectedComponents.push_back(_vertiesInTopologicalOrder);
				_vertiesInTopologicalOrder.clear();
			}
		}
}

void Graph::_DFSvisit(int u)
{
	_DFScolors[u] = 'G';
	for (int v = 0; v < _adjList[u].size(); v++)
		if (_DFScolors[_adjList[u][v]] == 'W')
			_DFSvisit(_adjList[u][v]);
	_DFScolors[u] = 'B';
	_vertiesInTopologicalOrder.push_back(u);
}

vector<vector<int> > Graph::stronglyConnectedComponents()
{
	_searchConComp = false;
	for (int i = 0; i < _adjList.size(); i++)
		_vertiesInTraversalOrder.push_back(i);
	_DFS();
	_tranporate();
	for (int i = 0; i < _vertiesInTopologicalOrder.size(); i++)
		_vertiesInTraversalOrder.push_back(_vertiesInTopologicalOrder[i]);
	reverse(_vertiesInTraversalOrder.begin(), _vertiesInTraversalOrder.end());
	_searchConComp = true;
	_DFS();
	return _DFSconnectedComponents;
}


void Graph::_DFSpreparationColParTime()
{
	if (_DFSdoesNotStart)
		for (int i = 0; i < _adjList.size(); i++)
		{
			_DFScolors.push_back('W');
			_DFSdoesNotStart = false;
		}
	else
		for (int i = 0; i < _adjList.size(); i++)
			_DFScolors[i] = 'W';
}

void Graph::_tranporate()
{
	vector<vector<int> > adjListCopy;
	vector <int> A;
	for (int i = 0; i < _adjList.size(); i++)
		adjListCopy.push_back(A);
	for (int i = 0; i < _adjList.size(); i++)
		for (int j = 0; j < _adjList[i].size(); j++)
			adjListCopy[_adjList[i][j]].push_back(i);
	_adjList.clear();
	for (int i = 0; i < adjListCopy.size(); i++)
	{
		_adjList.push_back(A);
		for (int j = 0; j < adjListCopy[i].size(); j++)
			_adjList[i].push_back(adjListCopy[i][j]);
	}
}

int main() 
{
	vector<vector<int> > adjList;
	int n, m;
	scanf("%d%d", &n, &m);
	vector<int> A;
	vector<int> v1, v2;
	for (int i = 0; i < n; i++)
		adjList.push_back(A);
	for (int i = 0; i < m; i++)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		a--;
		b--;
		v1.push_back(a);
		v2.push_back(b);
		adjList[a].push_back(b);
	}
	Graph G(adjList);
	vector<vector<int> > R = G.stronglyConnectedComponents();
	printf("%d\n", R.size());
	vector<int> vertiesToComponent;
	for (int i = 0; i < n; i++)
		vertiesToComponent.push_back(0);
	for (int i = 0; i < R.size(); i++)
		for (int j = 0; j < R[i].size(); j++)
			vertiesToComponent[R[i][j]] = i;
	for (int i = 0; i < vertiesToComponent.size(); i++)
		printf("%d ", vertiesToComponent[i]+1);
	//system("pause");
	return 0;
}