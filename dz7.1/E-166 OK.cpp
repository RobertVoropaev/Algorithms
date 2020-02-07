///////////////////////
////Voropaev Robert////
//MIPT/DIHT/592 group//
///////////////////////
#define _CRT_SECURE_NO_WARNING

#include <iostream>
#include <vector>
#include <stdio.h>
#include <algorithm>

using namespace std;

class Graph
{
public:
	Graph(vector<vector<bool> > adjMatrix);
	void DFS();
	vector<int> DFSgetTopologicalList();
private:
	vector<vector<int> > _adjList;
	void _DFSvisit(int u);
	vector<char> _DFScolors;
	bool _graphWithCycle;
	vector<int> TopologicalList;
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

void Graph::DFS()
{
	for (int i = 0; i < _adjList.size(); i++)
		_DFScolors.push_back('W');
	for (int u = 0; u < _adjList.size(); u++)
		if (_DFScolors[u] == 'W')
			_DFSvisit(u);
}

void Graph::_DFSvisit(int u)
{
	_DFScolors[u] = 'G';
	for (int v = 0; v < _adjList[u].size(); v++)
		if (_DFScolors[_adjList[u][v]] == 'W')
			_DFSvisit(_adjList[u][v]);
		else if (_DFScolors[_adjList[u][v]] == 'G') 
		{
			_graphWithCycle = true;
			return;
		}
	_DFScolors[u] = 'B';
	TopologicalList.push_back(u);
}

vector<int> Graph::DFSgetTopologicalList()
{
	_graphWithCycle = false;
	TopologicalList.clear();
	DFS();
	if (_graphWithCycle) 
	{
		TopologicalList.clear();
		return TopologicalList;
	}
	else
		return TopologicalList;
}

int main()
{
	int N, M;
	scanf("%d%d", &N, &M);
	vector<vector<bool> > AdjMatrix;
	vector<bool> A;
	vector<int> Q;
	for (int i = 0; i < N; i++)
	{
		AdjMatrix.push_back(A);
		for (int j = 0; j < N; j++)
			AdjMatrix[i].push_back(false);
		Q.push_back(i + 1);
	}
	for (int i = 0; i < M; i++)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		a--;
		b--;
		AdjMatrix[a][b] = true;
	}
	Graph G(AdjMatrix);
	vector<int> V = G.DFSgetTopologicalList();
	if (V.size() >= 1) {
		printf("Yes\n");
		for (int i = V.size()-1; i >= 0; i--)
			printf("%d ",V[i] + 1);
	}
	else
		printf("No");
	//system("pause");
	return 0;
}