#pragma once
#include <stdio.h>

class SJEdge
{
private:
    int m_source;
    int m_dest;
    float m_weight;
public:
    SJEdge(int s, int t, float w);
    int GetSource();
    int GetDest();
    float GetWeight();
};

