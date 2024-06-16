#include "SJGraph.h"
#include "SJEdge.h"
using namespace std;

SJGraph::SJGraph(int n)
{
	m_numVertices = n;
	m_numEdges = 0;
	m_vecAdj = new vector<SJEdge*>[m_numVertices];
}
SJGraph::~SJGraph()
{
	vector<SJEdge*>::iterator iter;
	for (iter = m_edgeList.begin(); iter != m_edgeList.end(); iter++) {
		delete (*iter);
	}
	
	delete[]m_vecAdj;
}
int SJGraph::GetNumVertices()
{
	return m_numVertices;
}
void SJGraph::AddEdge(SJEdge* e)
{
	m_vecAdj[e->GetSource()].push_back(e);
	SJEdge* e1 = new SJEdge(e->GetDest(), e->GetSource(), 0);
	m_vecAdj[e->GetDest()].push_back(e1);
	m_edgeList.push_back(e);
	m_edgeList.push_back(e1);
	m_numEdges++;
}
void SJGraph::PrintGraph()
{
	vector<SJEdge*>::iterator iter;
	for (int i = 0; i < m_numVertices; i++) {
		printf("%dth vertex\n", i);
		for (iter = m_vecAdj[i].begin(); iter != m_vecAdj[i].end(); iter++) {
			printf("[%d] -> [%d] : [%.3f]\n", (*iter)->GetSource(), (*iter)->GetDest(), (*iter)->GetWeight());
		}
	}
}