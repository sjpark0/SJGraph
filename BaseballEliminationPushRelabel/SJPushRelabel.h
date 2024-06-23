#pragma once
#include <vector>
class SJGraph;
class SJEdge;
class SJPushRelabel{
private:
	int  m_numVertices;
    int  *m_height;
    float *m_flow;
    SJGraph *m_graph;
    void InitializePreflow(int s);
    void Push(SJEdge *edge);
    void Relabel(int u);
public:
    SJPushRelabel(int numVertices);
	~SJPushRelabel();
    void GenericPushRelabel(SJGraph* g);
};