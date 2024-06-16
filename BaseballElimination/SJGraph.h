#pragma once
#include <vector>
class SJEdge;
class SJGraph
{
private:
    int m_numVertices;
    int m_numEdges;
    std::vector<SJEdge*> m_edgeList;
    std::vector<SJEdge*>* m_vecAdj;
public:
    SJGraph(int n);
    ~SJGraph();
    int GetNumVertices();
    void AddEdge(SJEdge* e);
    void PrintGraph();
};

