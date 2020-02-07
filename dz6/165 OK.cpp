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
	bool DFStoCheckBiparation();
	vector<int> DFSgetShares();
	void DFS();
private:
	vector<vector<int> > _adjList;
	void _DFSvisit(int u, int parent);
	vector<bool> _DFScolors;
	bool _DFSbiparateGraph;
	vector<int> _DFStheVertexInShares;
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
	for (int i = 0; i < _adjList.size(); i++) {
		_DFScolors.push_back(true);
		_DFStheVertexInShares.push_back(-1);
	}
	_DFSbiparateGraph = true;
	for (int u = 0; u < _adjList.size(); u++)
		if (_DFScolors[u])
		{
			_DFSvisit(u, -1);
		}
}

void Graph::_DFSvisit(int u, int parent)
{
	_DFScolors[u] = false;
	if (parent == -1)
		_DFStheVertexInShares[u] = 0;
	else if (_DFStheVertexInShares[parent] == 1)
		_DFStheVertexInShares[u] = 0;
	else
		_DFStheVertexInShares[u] = 1;
	for (int v = 0; v < _adjList[u].size(); v++)
	{
		if (_DFScolors[_adjList[u][v]])
		{
			_DFSvisit(_adjList[u][v], u);
		}
		else if (_DFStheVertexInShares[_adjList[u][v]] == _DFStheVertexInShares[u])
		{
			_DFSbiparateGraph = false;
			return;
		}
	}
}

bool Graph::DFStoCheckBiparation()
{
	DFS();
	return _DFSbiparateGraph;
}

vector<int> Graph::DFSgetShares()
{
	return _DFStheVertexInShares;
}

int main()
{
	int N, M;
	scanf("%d%d", &N, &M);
	vector<vector<bool> > AdjMatrix;
	vector <bool> A;
	for (int i = 0; i < N; i++)
	{
		AdjMatrix.push_back(A);
		for (int j = 0; j < N; j++)
		{
			
			AdjMatrix[i].push_back(false);
		}
	}
	for (int i = 0; i < M; i++)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		a--;
		b--;
		AdjMatrix[a][b] = true;
		AdjMatrix[b][a] = true;
	}
	Graph G(AdjMatrix);
	if (G.DFStoCheckBiparation())
	{
		printf("YES\n");
		vector<int> A = G.DFSgetShares();
		for (int i = 0; i < A.size(); i++)
			if (!A[i])
				printf("%d ", i+1);
	}
	else
		printf("NO");
	//system("pause");
	return 0;
}