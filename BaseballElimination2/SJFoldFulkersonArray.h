#pragma once
class SJGraph;
class SJFoldFulkersonArray
{
private:
	bool* m_bMarked;
	bool* m_bInCut;
	int* m_iParent;
	float m_maxFlow;
	float** m_adjGraph;
	int m_numVertices;
	float FindAgumentingPath(SJGraph *g, int s, int t);
public:
	SJFoldFulkersonArray(int numVertices);
	~SJFoldFulkersonArray();
	void ComputeMaxFlow(SJGraph* g, int s, int t);
	float GetMaxFlow();
	bool  inCut(int id);
};

