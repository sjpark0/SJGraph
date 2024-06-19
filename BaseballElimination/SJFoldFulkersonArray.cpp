#include "SJFoldFulkersonArray.h"

#include "SJFoldFulkerson.h"
#include "SJGraph.h"
#include "SJEdge.h"
#include <vector>
#include <iostream>
using namespace std;
#define EPSILON 0.00001
SJFoldFulkersonArray::SJFoldFulkersonArray(int numVertices)
{
	m_numVertices = numVertices;
	m_bMarked = new bool[m_numVertices];
	m_iParent = new int[m_numVertices];
	m_bInCut = new bool[m_numVertices];
	m_adjGraph = new float* [m_numVertices];
	for (int i = 0; i < m_numVertices; i++) {
		m_bInCut[i] = false;
		m_adjGraph[i] = new float[m_numVertices];
		for (int j = 0; j < m_numVertices; j++) {
			m_adjGraph[i][j] = 0;
		}
	}
}
SJFoldFulkersonArray::~SJFoldFulkersonArray()
{
	delete[]m_bMarked;
	delete[]m_iParent;
	delete[]m_bInCut;
	for (int i = 0; i < m_numVertices; i++) {
		delete[]m_adjGraph[i];
	}
	delete[]m_adjGraph;
}
void SJFoldFulkersonArray::ComputeMaxFlow(SJGraph *g, int s, int t) 
{
	vector<SJEdge*> adj;
	vector<SJEdge*>::iterator iter;

	for (int i = 0; i < m_numVertices; i++) {
		m_bInCut[i] = false;
		for (int j = 0; j < m_numVertices; j++) {
			m_adjGraph[i][j] = 0;
		}
	}

	for (int i = 0; i < m_numVertices; i++) {
		adj = g->GetAdjacentVector(i);
		for (iter = adj.begin(); iter != adj.end(); iter++) {
			m_adjGraph[i][(*iter)->GetDest()] = (*iter)->GetWeight();
		}
	}

	float flow;
	m_maxFlow = 0;
	while (true) {
		flow = FindAgumentingPath(g, s, t);
		//printf("%f\n", flow);
		if (flow < EPSILON) {
			break;
		}
		m_maxFlow += flow;
	}

	int current;
	int i;

	vector<int> inCutList;
	inCutList.clear();
	inCutList.push_back(s);
	while (inCutList.size() > 0) {
		current = inCutList.back();
		m_bInCut[current] = true;
		inCutList.pop_back();

		adj = g->GetAdjacentVector(current);
		for (iter = adj.end() - 1; iter >= adj.begin(); iter--) {
			i = (*iter)->GetDest();
			if (m_adjGraph[current][i] > 0 && m_bInCut[i] == false) {
				inCutList.push_back(i);
			}
		}
	}
}

float SJFoldFulkersonArray::FindAgumentingPath(SJGraph* g, int s, int t)
{
	for (int i = 0; i < m_numVertices; i++) {
		m_bMarked[i] = false;
		m_iParent[i] = -1;
	}
	vector<int> traverse;

	vector<SJEdge*> adj;
	int i, j;
	float cap;
	vector<SJEdge*>::iterator iter;
	int current = s;
	int preCurrent = s;
	traverse.push_back(s);

	int numAvail;
	vector<int>::iterator intIter;
	while (traverse.size() > 0) {
		/*for (intIter = traverse.begin(); intIter != traverse.end(); intIter++) {
			printf("%d ", (*intIter));
		}*/
		//printf("\n");
		current = traverse.back();
		m_bMarked[current] = true;
		//printf("current : %d, %d\n", current, t);
		if (current == t) break;

		adj = g->GetAdjacentVector(current);

		numAvail = 0;
		for (iter = adj.end() - 1; iter >= adj.begin(); iter--) {
			i = (*iter)->GetDest();

			if (m_bMarked[i]) continue;
			if (m_adjGraph[current][i] < EPSILON) continue;
			
			m_iParent[i] = current;
			traverse.push_back(i);
			numAvail++;
		}
		if (numAvail == 0) {
			traverse.pop_back();
		}
	}
	/*for (intIter = traverse.begin(); intIter != traverse.end(); intIter++) {
		printf("%d ", (*intIter));
	}
	printf("\n");*/

	if (traverse.size() == 0) return -1;

	int parent;
	float minCap = numeric_limits<float>::max();
	
	current = t;
	
	while (current != s) {
		parent = m_iParent[current];
		minCap = min(minCap, m_adjGraph[parent][current]);		
		current = parent;
	}

	current = t;
	while (current != s) {
		parent = m_iParent[current];
		m_adjGraph[parent][current] -= minCap;
		m_adjGraph[current][parent] += minCap;
		current = parent;

	}

	return minCap;
}

float SJFoldFulkersonArray::GetMaxFlow()
{
	return m_maxFlow;
}

bool SJFoldFulkersonArray::inCut(int id)
{
	return m_bInCut[id];
}