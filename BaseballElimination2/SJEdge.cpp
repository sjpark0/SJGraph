#include "SJEdge.h"

SJEdge::SJEdge(int s, int t, float c)
{
    m_source = s;
    m_dest = t;
    m_weight = 0;
    m_capacity = c;
}

int SJEdge::GetSource()
{
    return m_source;
}
int SJEdge::GetDest()
{
    return m_dest;
}
int SJEdge::GetOther(int v)
{
    if (m_source == v) return m_dest;
    else if (m_dest == v) return m_source;
    return -1;
}
float SJEdge::GetWeight()
{
    return m_weight;
}
float SJEdge::GetCapacity()
{
    return m_capacity;
}
void SJEdge::SetWeight(float weight)
{
    m_weight = weight;
}
float SJEdge::ResidualCapacity(int v)
{
    if (v == m_source) return m_capacity - m_weight;
    else if (v == m_dest) return m_weight;
    return -1;
}
void SJEdge::AddResidualWeight(int v, float weight)
{
    if (v == m_source) m_weight += weight;
    else if (v == m_dest) m_weight -= weight;
}