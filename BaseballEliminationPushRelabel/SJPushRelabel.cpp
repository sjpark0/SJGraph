#include "SJPushRelabel.h"
#include "SJGraph.h"
#include "SJEdge.h"

#include <vector>

using namespace std;
SJPushRelabel::SJPushRelabel(int numVertices)
{
    m_numVertices = numVertices;
    m_height = new int[m_numVertices];
    m_flow = new float[m_numVertices];
}
SJPushRelabel::~SJPushRelabel()
{
    delete []m_height;
    delete []m_flow;

}
void SJPushRelabel::InitializePreflow(int s)
{
    for(int i=0;i<m_numVertices;i++){
        m_height[i] = 0;
        m_flow[i] = 0.0;
    }
    m_height[s] = m_numVertices;
    vector<SJEdge*> adj = m_graph->GetOutEdges(s);
    vector<SJEdge*>::iterator iter;
    int v;
    for(iter = adj.begin();iter != adj.end();iter++){
        v = (*iter)->GetDest();
        (*iter)->SetFlow((*iter)->GetWeight());
        m_flow[(*iter)->GetDest()] = (*iter)->GetWeight();
        m_flow[s] -= (*iter)->GetWeight();
    }
}
void SJPushRelabel::Push(SJEdge *edge)
{
    int u = edge->GetSource();
    int v = edge->GetDest();
    
    float flow = min(m_flow[u], edge->GetWeight());
    edge->SetFlow(edge->GetFlow() + flow);
    m_flow[u] -= flow;
    m_flow[v] += flow;
}
void SJPushRelabel::Relabel(int u)
{
    vector<SJEdge*> adj = m_graph->GetOutEdges(u);
    vector<SJEdge*>::iterator iter;
    int minHeight = m_numVertices;
    for(iter = adj.begin();iter != adj.end();iter++){
        minHeight = min(minHeight, m_height[(*iter)->GetDest()]);
    }
    m_height[u] = 1 + minHeight;
}
void SJPushRelabel::GenericPushRelabel(SJGraph* g)
{
    m_graph = g;
    vector<SJEdge*> adj;
    vector<SJEdge*>::iterator iter;
    int v;
    InitializePreflow(0);
    while(m_height[m_numVertices - 1] < m_numVertices) {
        for(int i=0;i<m_numVertices;i++){
            if (m_flow[i] <= 0) continue;
            //printf("%d, %f\n", i, m_flow[i]);
            adj = m_graph->GetOutEdges(i);
            for (iter = adj.begin(); iter != adj.end(); iter++) {
                v = (*iter)->GetDest();
                if (m_height[i] == m_height[v] + 1) {
                    Push(*iter);
                }
                else if (m_height[i] <= m_height[v]) {
                    Relabel(i);
                }
            }

        }
    }
    //printf("%f\n", m_flow[m_numVertices - 1]);
}