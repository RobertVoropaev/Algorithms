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

int main() {
	int n;
	scanf("%d", &n);
	vector<vector<bool> > D;
	vector<bool> A;
	for (int i = 0; i < n; i++)
	{
		D.push_back(A);
		for (int j = 0; j < n; j++)
		{
			int a;
			scanf("%d", &a);
			D[i].push_back(a);
		}
	}
	Graph G(D);
	int a, b;
	scanf("%d%d", &a, &b);
	a--;
	b--;
	G.BFS(a);
	int distance = G.BFSgetTheDistenceFromTheVertex(b);
	if (distance == 0 || distance == -1)
	{
		printf("%d\n", distance);
	}
	else
	{
		printf("%d\n", distance);
		vector <int> B;
		int p = b;
		while (p != a)
		{
			B.push_back(p);
			p = G.BFSgetTheParentVertex(p);
		}
		B.push_back(p);
		for (int i = B.size() - 1; i >= 0; i--)
			printf("%d ", B[i] + 1);
	}
	//system("pause");
	return 0;
}