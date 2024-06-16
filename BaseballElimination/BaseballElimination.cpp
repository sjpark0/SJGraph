// BaseballElimination.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <stdio.h>
#include "BaseballTeam.h"
#include "SJGraph.h"
#include "SJEdge.h"
#include <vector>
using namespace std;
void ComputeElimination(BaseballTeam *ref, vector<BaseballTeam*> aTeam)
{
    int num = aTeam.size();
    SJGraph* graph = new SJGraph(2 + num + num * (num - 1) / 2);
    int gameV = 1;
    int teamV = 1 + num * (num - 1) / 2;
    int numPossibleGame = 0;
    for (int i = 0; i < num; i++) {
        for (int j = i + 1; j < num; j++) {
            graph->AddEdge(new SJEdge(0, gameV, aTeam[i]->GetAgainRemain(j)));
            numPossibleGame += aTeam[i]->GetAgainRemain(j);
            graph->AddEdge(new SJEdge(gameV, teamV, numeric_limits<float>::max()));
            graph->AddEdge(new SJEdge(gameV, teamV + (j - i), numeric_limits<float>::max()));
            gameV++;
        }
        graph->AddEdge(new SJEdge(teamV, graph->GetNumVertices() - 1, ref->GetWin() + ref->GetRemain() - aTeam[i]->GetWin()));
        
        teamV++;
    }
    graph->PrintGraph();
    delete graph;
}
void ComputeElimination(BaseballTeam** teams, int numTeam)
{
    vector<BaseballTeam*> aTeam;
    for (int i = 0; i < 1; i++) {
        aTeam.clear();
        for (int j = 0; j < numTeam; j++) {
            if (i != j) aTeam.push_back(teams[j]);
        }
        ComputeElimination(teams[i], aTeam);
    }
}
int main(int argc, char* argv[])
{
    FILE* fp;
    fp = fopen(argv[1], "r");
    int numTeam;
    char name[1024];
    int win;
    int lose;
    int remain;

    fscanf(fp, "%d", &numTeam);
    int* againstRemain = new int[numTeam];
    BaseballTeam** teams = new BaseballTeam * [numTeam];
    
    for (int i = 0; i < numTeam; i++) {
        fscanf(fp, "%s %d %d %d", name, &win, &lose, &remain);
        for (int j = 0; j < numTeam; j++) {
            fscanf(fp, "%d", &againstRemain[j]);
        }
        teams[i] = new BaseballTeam(name, i, win, lose, remain, againstRemain, numTeam);
    }

    for (int i = 0; i < numTeam; i++) {
        teams[i]->PrintInfo();
    }
    ComputeElimination(teams, numTeam);
    for (int i = 0; i < numTeam; i++) {
        delete teams[i];
    }
    delete[]teams;
    return 0;
}

// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
