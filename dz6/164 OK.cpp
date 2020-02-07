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
	int DFSgetTheNumberOfVertiresInComponentWithThis(int v);
private:
	vector<vector<int> > _adjList;
	void _DFSvisit(int u);
	vector<bool> _DFScolors;
	int _DFSvisitCounter;
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

void Graph::_DFSvisit(int u)
{
	_DFSvisitCounter++;
	_DFScolors[u] = false;
	for (int v = 0; v < _adjList[u].size(); v++)
		if (_DFScolors[_adjList[u][v]])
			_DFSvisit(_adjList[u][v]);
}

int Graph::DFSgetTheNumberOfVertiresInComponentWithThis(int v)
{
	for (int i = 0; i < _adjList.size(); i++)
		_DFScolors.push_back(true);
	_DFSvisitCounter = 0;
	_DFSvisit(v);
	return _DFSvisitCounter;
}

int main()
{
	int n, m;
	scanf_s("%d%d", &n, &m);
	vector<vector<bool>> D;
	vector<bool> A;
	for (int i = 0; i < n; i++)
	{
		D.push_back(A);
		for (int j = 0; j < n; j++)
		{
			int a;
			scanf_s("%d", &a);
			D[i].push_back(a);
		}
	}
	Graph G(D);
	printf("%d", G.DFSgetTheNumberOfVertiresInComponentWithThis(m-1));
	system("pause");
	return 0;
}