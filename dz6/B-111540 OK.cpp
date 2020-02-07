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
	Graph(vector<vector<int> > adjList);
	void DFS();
	vector<vector<int> > DFSgetAllConnectedComponents();
private:
	vector<vector<int> > _adjList;
	void _DFSvisit(int u);
	vector<int> _DFSverticesInTheComponent;
	vector<vector<int> > _DFSconnectedComponents;
	vector<bool> _DFScolors;
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

Graph::Graph(vector<vector<int> > adjList)
{
	vector<int> A;
	for (int i = 0; i < adjList.size(); i++)
	{
		_adjList.push_back(A);
		for (int j = 0; j < adjList[i].size(); j++)
			_adjList[i].push_back(adjList[i][j]);
	}
}

void Graph::DFS()
{
	for (int i = 0; i < _adjList.size(); i++)
		_DFScolors.push_back(true);
	for (int u = 0; u < _adjList.size(); u++)
		if (_DFScolors[u])
		{
			_DFSvisit(u);
			_DFSconnectedComponents.push_back(_DFSverticesInTheComponent);
			_DFSverticesInTheComponent.clear();
		}
}

void Graph::_DFSvisit(int u)
{
	_DFSverticesInTheComponent.push_back(u);
	_DFScolors[u] = false;
	for (int v = 0; v < _adjList[u].size(); v++)
		if (_DFScolors[_adjList[u][v]])
			_DFSvisit(_adjList[u][v]);
}

vector<vector<int> > Graph::DFSgetAllConnectedComponents()
{
	DFS();
	return _DFSconnectedComponents;
}

int main() 
{
	int N, M;
	scanf("%d%d", &N, &M);
	vector<vector<int> > Adj;
	vector <int> A;
	for (int i = 0; i < N; i++)
		Adj.push_back(A);
	for (int i = 0; i < M; i++)
	{
		int a, b;
		scanf_s("%d%d", &a, &b);
		a--;
		b--;
		Adj[a].push_back(b);
		Adj[b].push_back(a);
	}
	Graph G(Adj);
	vector<vector<int> > F = G.DFSgetAllConnectedComponents();
	printf("%d\n", F.size());
	for (int i = 0; i < F.size(); i++)
	{
		printf("%d\n", F[i].size());
		for (int j = 0; j < F[i].size(); j++)
			printf("%d ", F[i][j] + 1);
		printf("\n");
	}
	//system("pause");
	return 0;
}