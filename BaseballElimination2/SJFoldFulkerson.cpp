#include "SJFoldFulkerson.h"
#include "SJGraph.h"
#include "SJEdge.h"
#include <vector>
#include <iostream>
using namespace std;
#define EPSILON 0.00001
SJFoldFulkerson::SJFoldFulkerson(SJGraph* g, int s, int t)
{
	m_numVertices = g->GetNumVertices();
	//float flow = numeric_limits<float>::max();
	m_bMarked = new bool[m_numVertices];
	m_iParent = new int[m_numVertices];
	m_bInCut = new bool[m_numVertices];
	for (int i = 0; i < m_numVertices; i++) {
		m_bInCut[i] = false;
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
	vector<SJEdge*> adj;
	vector<SJEdge*>::iterator iter;
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
			if ((*iter)->GetWeight() > 0 && m_bInCut[i] == false) {
				inCutList.push_back(i);
			}
		}
	}
}
SJFoldFulkerson::SJFoldFulkerson(int numVertices)
{
	m_numVertices = numVertices;
	m_bMarked = new bool[m_numVertices];
	m_iParent = new int[m_numVertices];
	m_bInCut = new bool[m_numVertices];
}
SJFoldFulkerson::~SJFoldFulkerson()
{
	delete[]m_bMarked;
	delete[]m_iParent;
	delete[]m_bInCut;
}
void SJFoldFulkerson::ComputeMaxFlow(SJGraph* g, int s, int t)
{
	for (int i = 0; i < m_numVertices; i++) {
		m_bInCut[i] = false;
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

	/*int current;
	int i;
	vector<SJEdge*> adj;
	vector<SJEdge*>::iterator iter;
	vector<int> inCutList;
	inCutList.clear();
	inCutList.push_back(s);
	while (inCutList.size() > 0) {
		current = inCutList.back();
		m_bInCut[current] = true;
		inCutList.pop_back();

		adj = g->GetAdjacentVector(current);
		for (iter = adj.end() - 1; iter >= adj.begin(); iter--) {
			i = (*iter)->GetOther(current);
			if ((*iter)->ResidualCapacity(current) > 0 && m_bInCut[i] == false) {
				inCutList.push_back(i);
			}
		}
	}*/
}
float SJFoldFulkerson::FindAgumentingPath(SJGraph* g, int s, int t)
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
		}
		printf("\n");*/
		current = traverse.back();
		traverse.pop_back();
		m_bMarked[current] = true;
		//traverse.pop_back();
		//printf("current : %d, %d\n", current, t);
		if (current == t) {
			
			break;
		}

		adj = g->GetAdjacentVector(current);
		
		//numAvail = 0;
		for (iter = adj.end() - 1; iter >= adj.begin(); iter--) {
			i = (*iter)->GetOther(current);
			cap = (*iter)->ResidualCapacity(current);
			
			if (m_bMarked[i]) continue;
			if (cap < EPSILON) continue;
			
			//m_bMarked[i] = true;
			m_iParent[i] = current;
			traverse.push_back(i);
		//	numAvail++;
		}
		//if (numAvail == 0) {
			//traverse.pop_back();
			//m_bMarked[current] = false;
		//}
		
	}
	/*for (intIter = traverse.begin(); intIter != traverse.end(); intIter++) {
		printf("%d ", (*intIter));
	}
	printf("\n");*/

	//if (traverse.size() == 0) return -1;
	if (m_bMarked[t] == false) return -1;
	int parent;
	float minCap = numeric_limits<float>::max();
	
	current = t;
	while (current != s) {
		parent = m_iParent[current];
		adj = g->GetAdjacentVector(parent);
		for (iter = adj.begin(); iter != adj.end(); iter++) {
			if ((*iter)->GetOther(parent) == current) break;
		}
		minCap = min(minCap, (*iter)->ResidualCapacity(parent));

		current = parent;
	}
	current = t;
	while (current != s) {
		parent = m_iParent[current];
		adj = g->GetAdjacentVector(parent);
		for (iter = adj.begin(); iter != adj.end(); iter++) {
			if ((*iter)->GetOther(parent) == current) break;
		}
		(*iter)->AddResidualWeight(parent, minCap);
		current = parent;
	}
	
	return minCap;
}

float SJFoldFulkerson::GetMaxFlow()
{
	return m_maxFlow;
}

bool SJFoldFulkerson::inCut(int id)
{
	//return m_bInCut[id];
	return m_bMarked[id];
}