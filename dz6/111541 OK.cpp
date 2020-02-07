///////////////////////
////Voropaev Robert////
//MIPT/DIHT/592 group//
///////////////////////
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <stdio.h>

using namespace std;

class Graph
{
public:
	Graph(vector<vector<bool> > adjMatrix);
	void DFS();
	bool DFScycleTest();
	int DFStheNumberOfConnectedComponents();
private:
	vector<vector<int> > _adjList;
	void _DFSvisit(int u, int parent);
	vector<char> _DFScolors;
	bool _graphWithCycle;
	int _DFSvisitCounter;
	int _DFScounter;
};

Graph::Graph(vector<vector<bool> > adjMatrix)
{
	vector<int> A;
	for (int i = 0; i < adjMatrix.size(); i++)
	{
		_adjList.push_back(A);
		for (int j = 0; j < adjMatrix.size(); j++)
			if (adjMatrix[i][j])
				_adjList[i].push_back(j);
	}
}

vector<vector<bool> > scanfAdjMatrix()
{
	int n;
	cin >> n;
	vector<vector<bool> > D;
	vector<bool> A;
	for (int i = 0; i < n; i++)
	{
		D.push_back(A);
		for (int j = 0; j < n; j++)
		{
			int a;
			cin >> a;
			D[i].push_back(a);
		}
	}
	return D;
}

void Graph::DFS()
{
	for (int i = 0; i < _adjList.size(); i++)
		_DFScolors.push_back('W');
	for (int u = 0; u < _adjList.size(); u++)
		if (_DFScolors[u] == 'W') {
			_DFSvisit(u, -1);
			_DFScounter++;
		}
}

void Graph::_DFSvisit(int u, int parent)
{
	_DFScolors[u] = 'G';
	for (int v = 0; v < _adjList[u].size(); v++)
		if (_DFScolors[_adjList[u][v]] == 'W')
		{
			_DFSvisit(_adjList[u][v], u);
		}
		else if (_DFScolors[_adjList[u][v]] == 'G' && _adjList[u][v]!=parent)
			_graphWithCycle = true;
	_DFScolors[u] = 'B';
}

bool Graph::DFScycleTest()
{
	_graphWithCycle = false;
	_DFScounter = 0;
	DFS();
	return _graphWithCycle;
}

int Graph::DFStheNumberOfConnectedComponents()
{
	return _DFScounter;
}

int main()
{
	Graph G(scanfAdjMatrix());
	if (!G.DFScycleTest() && G.DFStheNumberOfConnectedComponents() == 1)
		printf("YES");
	else
		printf("NO");
	//system("pause");
	return 0;
}