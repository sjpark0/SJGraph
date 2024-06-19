#pragma once
#define NEIGHBOR 6
class SJGraph
{
private:
	float** m_ppWeight;
	int     m_numVertices;
public:
	SJGraph(int width, int height);
	~SJGraph();

	float GetWeight(int v, int pos);
	void  SetWeight(int v, float w, int pos);
	void  PrintInfo();
};

