///////////////////////
////Voropaev Robert////
//MIPT/DIHT/592 group//
///////////////////////
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <stdio.h>
#include <string>

using namespace std;

class Graph
{
public:
	Graph(vector<vector<bool> > adjMatrix);
	Graph(vector<vector<int> > adjList);
	void DFS();
	int DFSgetTheNumberOfConnectedComponents();
private:
	vector<vector<int> > _adjList;
	void _DFSvisit(int u);
	vector<bool> _DFScolors;
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
	_DFScounter = 0;
	for (int i = 0; i < _adjList.size(); i++)
		_DFScolors.push_back(true);
	for (int u = 0; u < _adjList.size(); u++)
		if (_DFScolors[u])
		{
			_DFScounter++;
			_DFSvisit(u);
		}
}

void Graph::_DFSvisit(int u)
{
	_DFScolors[u] = false;
	for (int v = 0; v < _adjList[u].size(); v++)
		if (_DFScolors[_adjList[u][v]])
			_DFSvisit(_adjList[u][v]);
}

int Graph::DFSgetTheNumberOfConnectedComponents()
{
	DFS();
	return _DFScounter;
}

bool checkBorder(int x, int y, int M, int N)
{
	return (0 <= x && x < N && 0 <= y && y < M);
}

int main()
{
	int M, N;
	scanf("%d%d", &M, &N);
	vector<string> str;
	string a;
	for (int i = 0; i < M; i++)
	{
		cin >> a;
		str.push_back(a);
	}
	vector<vector<bool> > AdjMatrix;
	vector<bool> B;
	for (int i = 0; i < M*N; i++)
	{
		AdjMatrix.push_back(B);
		for (int j = 0; j < M*N; j++)
			AdjMatrix[i].push_back(false);
	}
	int countPoints = 0;
	for (int n = 0; n < M*N; n++)
	{
		int y = n / N, x = n - N*y;
		if (str[y][x] == '#') {
			if (checkBorder(x - 1, y, M, N) && str[y][x - 1] == '#')
				AdjMatrix[n][x - 1 + N*y] = AdjMatrix[x - 1 + N*y][n] = true;
			if (checkBorder(x + 1, y, M, N) && str[y][x + 1] == '#')
				AdjMatrix[n][x + 1 + N*y] = AdjMatrix[x + 1 + N*y][n] = true;
			if (checkBorder(x, y - 1, M, N) && str[y - 1][x] == '#')
				AdjMatrix[n][x + N*(y - 1)] = AdjMatrix[x + N*(y - 1)][n] = true;
			if (checkBorder(x, y + 1, M, N) && str[y + 1][x] == '#')
				AdjMatrix[n][x + N*(y + 1)] = AdjMatrix[x + N*(y + 1)][n] = true;
		}
		else
			countPoints++;

	}
	Graph G(AdjMatrix);
	printf("%d", G.DFSgetTheNumberOfConnectedComponents() - countPoints);
	//system("pause");
	return 0;
}