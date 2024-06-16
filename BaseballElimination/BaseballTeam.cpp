#include <stdio.h>
#include <string.h>

#include "BaseballTeam.h"

BaseballTeam::BaseballTeam(char* name, int id, int win, int lose, int remain, int* againRemain, int numTeam)
{
    strcpy(m_name, name);
    m_id = id;
    m_win = win;
    m_lose = lose;
    m_remain = remain;
    m_numTeam = numTeam;
    m_againRemain = new int[numTeam];
    memcpy(m_againRemain, againRemain, numTeam * sizeof(int));
}
BaseballTeam::~BaseballTeam()
{
    if (m_againRemain) {
        delete[]m_againRemain;
        m_againRemain = NULL;
    }
}
char* BaseballTeam::GetName()
{
    return m_name;
}
int BaseballTeam::GetWin()
{
    return m_win;
}
int BaseballTeam::GetLose()
{
    return m_lose;
}
int BaseballTeam::GetRemain()
{
    return m_remain;
}
int BaseballTeam::GetAgainRemain(int id)
{
    return m_againRemain[id];
}
void BaseballTeam::PrintInfo()
{
    printf("Name : %s, %d\n", m_name, m_id);
    printf("Win : %d, Lose : %d, Remain : %d\n", m_win, m_lose, m_remain);
    printf("Against Remain Games\n");
    for (int i = 0; i < m_numTeam; i++) {
        printf("[%d, %d] Team : %d\n", m_id, i, m_againRemain[i]);
    }
}
