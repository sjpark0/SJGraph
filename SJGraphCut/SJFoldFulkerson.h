#pragma once
class SJGraph;
class SJFoldFulkerson
{
private:
	bool* m_bMarked;
	int* m_iParent;
	int   m_numVertices;
	int   m_iWidth;
	int   m_iHeight;
	float m_maxFlow;
	float FindAgumentingPath(SJGraph* g);
public:
	SJFoldFulkerson(int width, int height);
	~SJFoldFulkerson();
	void ComputeMaxFlow(SJGraph* g);
	float GetMaxFlow();
	bool  inCut(int id);
};

