#pragma once
class BaseballTeam
{
private:
    char m_name[1024];
    int m_id;
    int m_win;
    int m_lose;
    int m_remain;
    int m_numTeam;
    int* m_againRemain;
public:
    BaseballTeam(char* name, int id, int win, int lose, int remain, int* againRemain, int numTeam);
    ~BaseballTeam();
    char* GetName();
    int GetID();
    int GetWin();
    int GetLose();
    int GetRemain();
    int GetAgainRemain(int id);
    void PrintInfo();
};

