///////////////////////
////Voropaev Robert////
//MIPT/DIHT/592 group//
///////////////////////
#define _CRT_SECURE_NO_WARNING

#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <stdio.h>
#include <math.h>
#include <cmath>

using namespace std;

class Graph
{
public:
	Graph(vector<vector<bool> > adjMatrix);
	void BFS(int s);
	int BFSgetTheDistenceFromTheVertex(int v);
	int BFSgetTheParentVertex(int v);
private:
	vector<vector<int> > _adjList;
	vector<char> _BFScolors;
	vector<int> _BFSparents;
	vector<int> _BFSdistances;
	int _BFSindexLastCausedVertex;
	void _BFSpreparationColParDis();
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
	_BFSindexLastCausedVertex = -1;//BFS ни разу не запускался
}

void Graph::BFS(int s)
{
	_BFSpreparationColParDis();
	_BFScolors[s] = 'G';
	_BFSdistances[s] = 0;
	queue<int> Q;
	Q.push(s);
	while (!(Q.empty()))
	{
		int u = Q.front();
		Q.pop();
		for (int v = 0; v < _adjList[u].size(); v++)
			if (_BFScolors[_adjList[u][v]] == 'W')
			{
				_BFScolors[_adjList[u][v]] = 'G';
				_BFSdistances[_adjList[u][v]] = _BFSdistances[u] + 1;
				_BFSparents[_adjList[u][v]] = u;
				Q.push(_adjList[u][v]);
			}
		_BFScolors[u] = 'B';
	}
	_BFSindexLastCausedVertex = s;
}

void Graph::_BFSpreparationColParDis()
{
	if (_BFSindexLastCausedVertex == -1) //Если не разу не вызывался
		for (int i = 0; i < _adjList.size(); i++)
		{
			_BFScolors.push_back('W');
			_BFSparents.push_back(-1);
			_BFSdistances.push_back(-1);
		}
	else
		for (int i = 0; i < _adjList.size(); i++)
		{
			_BFScolors[i] = 'W';
			_BFSparents[i] = -1;
			_BFSdistances[i] = -1;
		}
}

int Graph::BFSgetTheDistenceFromTheVertex(int v)
{
	return _BFSdistances[v];
}

int Graph::BFSgetTheParentVertex(int v)
{
	return _BFSparents[v];
}

bool check(int v1, int v2, int N)
{
	if (v1<0 || v2<0 || v1>=N*N || v2>=N*N)
		return false;
	int y1 = v1 / N, y2 = v2 / N;
	int x1 = v1 - N*y1, x2 = v2 - N*y2;
	int dx = x2 - x1, dy = y2 - y1;
	if ((abs(dx) == 1 && abs(dy) == 2) || (abs(dx) == 2 && abs(dy) == 1))
		return true;
	return false;
}

int main() {
	int N;
	scanf("%d", &N);
	vector< vector <bool> > D;
	vector <bool> A;
	for (int i = 0; i < N*N; i++)
	{
		D.push_back(A);
		for (int j = 0; j < N*N; j++)
			D[i].push_back(false);
	}
	for (int i = 0; i < N*N; i++)
	{
		if (check(i, i + 2 + N, N))
			D[i][i + 2 + N] = true;
		if (check(i, i + 2 - N, N))
			D[i][i + 2 - N] = true;
		if (check(i, i + 1 + 2*N, N))
			D[i][i + 1 + 2*N] = true;
		if (check(i, i + 1 - 2*N, N))
			D[i][i + 1 - 2*N] = true;
		if (check(i, i - 2 + N, N))
			D[i][i - 2 + N] = true;
		if (check(i, i - 2 - N, N))
			D[i][i - 2 - N] = true;
		if (check(i, i - 1 + 2 * N, N))
			D[i][i - 1 + 2 * N] = true;
		if (check(i, i - 1 - 2 * N, N))
			D[i][i - 1 - 2 * N] = true;
	}
	Graph G(D);
	int x1, y1, x2, y2;
	scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
	x1--;
	x2--;
	y1--;
	y2--;
	int v1 = x1 + y1*N, v2 = x2 + y2*N;
	G.BFS(v1);
	int distance = G.BFSgetTheDistenceFromTheVertex(v2);
	if (distance == 0 || distance == -1)
	{
		printf("%d\n", distance);
	}
	else
	{
		printf("%d\n", distance);
		vector <int> B;
		int p = v2;
		while (p != v1)
		{
			B.push_back(p);
			p = G.BFSgetTheParentVertex(p);
		}
		B.push_back(p);
		for (int i = B.size() - 1; i >= 0; i--)
		{
			int y = B[i] / N;
			int x = B[i] - N*y;
			printf("%d%d \n", x+1, y+1);
		}
	}
	//system("pause");
	return 0;
}