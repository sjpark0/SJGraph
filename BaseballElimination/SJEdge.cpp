#include "SJEdge.h"

SJEdge::SJEdge(int s, int t, float w)
{
    m_source = s;
    m_dest = t;
    m_weight = w;
    m_flow = 0;
}

int SJEdge::GetSource()
{
    return m_source;
}
int SJEdge::GetDest()
{
    return m_dest;
}
float SJEdge::GetWeight()
{
    return m_weight;
}
void SJEdge::SetWeight(float weight)
{
    m_weight = weight;
}
float SJEdge::GetFlow()
{
    return m_flow;
}
void SJEdge::SetFlow(float flow)
{
    m_flow = flow;
}