#pragma once
#include <vector>
class SJGraph;
class SJFoldFulkerson
{
private:
	int  m_numVertices;
	bool* m_bMarked;
	bool* m_bInCut;
	int* m_iParent;
	float m_maxFlow;
	float FindAgumentingPath(SJGraph* g, int s, int t);

public:
	SJFoldFulkerson(int numVertices);
	SJFoldFulkerson(SJGraph* g, int s, int t);
	~SJFoldFulkerson();
	void ComputeMaxFlow(SJGraph* g, int s, int t);
	float GetMaxFlow();
	bool  inCut(int id);
};

