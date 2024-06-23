#pragma once
#include <vector>
class SJEdge;
class SJGraph
{
private:
    int m_numVertices;
    int m_numEdges;
    std::vector<SJEdge*> m_edgeList;
    std::vector<SJEdge*>* m_vecIn;
    std::vector<SJEdge*>* m_vecOut;
public:
    SJGraph(int n);
    ~SJGraph();
    int GetNumVertices();
    void AddEdge(SJEdge* e);
    std::vector<SJEdge*> GetInEdges(int id);
    std::vector<SJEdge*> GetOutEdges(int id);

    void PrintGraph();
};

