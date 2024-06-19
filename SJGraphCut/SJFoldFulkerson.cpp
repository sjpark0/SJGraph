#include "SJFoldFulkerson.h"
#include "SJGraph.h"
#include <vector>
#include <iostream>
using namespace std;
#define EPSILON 0.00001

SJFoldFulkerson::SJFoldFulkerson(int width, int height)
{
	m_numVertices = width * height;
	m_iWidth = width;
	m_iHeight = height;
	m_bMarked = new bool[m_numVertices];
	m_iParent = new int[m_numVertices];
}
SJFoldFulkerson::~SJFoldFulkerson()
{
	delete[]m_bMarked;
	delete[]m_iParent;
}

float SJFoldFulkerson::FindAgumentingPath(SJGraph* g)
{
	for (int i = 0; i < m_numVertices; i++) {
		m_bMarked[i] = false;
		m_iParent[i] = -1;
	}
	vector<int> traverse;

	vector<int>::iterator intIter;
	int start, end;
	int current;
	int index;
	float weight;
	bool bFind = false;
	int x, y;
	for (int i = 0; i < m_numVertices; i++) {
		if (g->GetWeight(i, 0) < EPSILON) continue;
		start = i;
		traverse.push_back(i);
		while (traverse.size() > 0) {
			/*printf("start\n");
			for (intIter = traverse.begin(); intIter != traverse.end(); intIter++) {
				printf("%d ", (*intIter));
			}
			printf("\n");*/
			current = traverse.back();
			traverse.pop_back();
			m_bMarked[current] = true;
			
			if (g->GetWeight(current, 1) > EPSILON) {
				end = current;
				bFind = true;
				break;
			}
			x = current % m_iWidth;
			y = current / m_iWidth;
			if (x - 1 >= 0 && !m_bMarked[current - 1] && g->GetWeight(current, 2) > EPSILON) {
				m_iParent[current - 1] = current;
				traverse.push_back(current - 1);
			}
			if (x + 1 < m_iWidth && !m_bMarked[current + 1] && g->GetWeight(current, 3) > EPSILON) {
				m_iParent[current + 1] = current;
				traverse.push_back(current + 1);
			}
			if (y - 1 >= 0 && !m_bMarked[current - m_iWidth] && g->GetWeight(current, 4) > EPSILON) {
				m_iParent[current - m_iWidth] = current;
				traverse.push_back(current - m_iWidth);
			}
			if (y + 1 < m_iHeight && !m_bMarked[current + m_iWidth] && g->GetWeight(current, 5) > EPSILON) {
				m_iParent[current + m_iWidth] = current;
				traverse.push_back(current + m_iWidth);
			}

			/*printf("end\n");
			for (intIter = traverse.begin(); intIter != traverse.end(); intIter++) {
				printf("%d ", (*intIter));
			}
			printf("\n");*/

		}
		if (bFind) break;
	}
	//if (traverse.size() == 0) return -1;
	if (bFind == false) return -1;
	/*printf("%d, %d\n", start, end);
	for (int i = 0; i < m_numVertices; i++) {
		printf("%d\n", m_iParent[i]);
	}*/
	current = end;
	while (current != start) {
		printf("%d\t", current);
		current = m_iParent[current];
	}
	printf("%d\n", start);

	int parent;
	float minCap = numeric_limits<float>::max();
	current = end;
	int diff;
	while (current != start) {
		parent = m_iParent[current];
		diff = parent - current;
		if (diff == 1) {
			minCap = min(minCap, g->GetWeight(parent, 2));
		}
		else if (diff == -1) {
			minCap = min(minCap, g->GetWeight(parent, 3));
		}
		else if (diff == m_iWidth) {
			minCap = min(minCap, g->GetWeight(parent, 4));
		}
		else if (diff == -m_iWidth) {
			minCap = min(minCap, g->GetWeight(parent, 5));
		}		

		current = parent;
	}
	current = end;
	while (current != start) {
		parent = m_iParent[current];

		diff = parent - current;
		if (diff == 1) {
			g->SetWeight(parent, g->GetWeight(parent, 2) - minCap, 2);
			g->SetWeight(current, g->GetWeight(current, 3) + minCap, 3);
		}
		else if (diff == -1) {
			g->SetWeight(parent, g->GetWeight(parent, 3) - minCap, 3);
			g->SetWeight(current, g->GetWeight(current, 2) + minCap, 2);

		}
		else if (diff == m_iWidth) {
			g->SetWeight(parent, g->GetWeight(parent, 4) - minCap, 4);
			g->SetWeight(current, g->GetWeight(current, 5) + minCap, 5);
		}
		else if (diff == -m_iWidth) {
			g->SetWeight(parent, g->GetWeight(parent, 5) - minCap, 5);
			g->SetWeight(current, g->GetWeight(current, 4) + minCap, 4);
		}
		current = parent;
	}

	return minCap;
}
void SJFoldFulkerson::ComputeMaxFlow(SJGraph* g)
{	
	float flow;
	m_maxFlow = 0;
	while (true) {
		flow = FindAgumentingPath(g);
		printf("%f\n", flow);
		if (flow < EPSILON) {
			break;
		}
		m_maxFlow += flow;
	}
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