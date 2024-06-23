#pragma once
#include <stdio.h>

class SJEdge
{
private:
    int m_source;
    int m_dest;
    float m_weight;
    float m_flow;
public:
    SJEdge(int s, int t, float w);
    int GetSource();
    int GetDest();
    float GetWeight();
    float GetFlow();
    void SetWeight(float weight);
    void SetFlow(float flow);
};

