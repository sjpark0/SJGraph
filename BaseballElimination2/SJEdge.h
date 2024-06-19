#pragma once
#include <stdio.h>

class SJEdge
{
private:
    int m_source;
    int m_dest;
    float m_weight;
    float m_capacity;
public:
    SJEdge(int s, int t, float c);
    int GetSource();
    int GetDest();
    int GetOther(int v);
    float GetWeight();
    float GetCapacity();
    void SetWeight(float weight);
    float ResidualCapacity(int v);
    void AddResidualWeight(int v, float weight);
};

