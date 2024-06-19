#include <stdio.h>
#include "SJGraph.h"

SJGraph::SJGraph(int width, int height)
{
	m_numVertices = width * height;
	m_ppWeight = new float* [m_numVertices];
	for (int i = 0; i < m_numVertices; i++) {
		m_ppWeight[i] = new float[NEIGHBOR];
		for (int j = 0; j < NEIGHBOR; j++) {
			m_ppWeight[i][j] = 0;
		}
	}
}
SJGraph::~SJGraph()
{
	for (int i = 0; i < m_numVertices; i++) {
		delete[]m_ppWeight[i];
	}
	delete[]m_ppWeight;
}

float SJGraph::GetWeight(int v, int pos)
{
	return m_ppWeight[v][pos];
}
void SJGraph::SetWeight(int v, float w, int pos)
{
	m_ppWeight[v][pos] = w;
}
void SJGraph::PrintInfo()
{
	for (int i = 0; i < m_numVertices; i++) {
		printf("%dth Vertices\n", i);
		for (int j = 0; j < NEIGHBOR; j++) {
			printf("%f\t", m_ppWeight[i][j]);
		}
		printf("\n");
	}
}