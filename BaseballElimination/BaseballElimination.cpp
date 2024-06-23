// BaseballElimination.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <stdio.h>
#include "BaseballTeam.h"
#include "SJGraph.h"
#include "SJEdge.h"
#include "SJFoldFulkerson.h"
#include "SJFoldFulkersonArray.h"
#include <vector>
#include <time.h>

using namespace std;
//SJFoldFulkersonArray* g_ff;
SJFoldFulkerson* g_ff;

bool ComputeElimination(BaseballTeam *ref, vector<BaseballTeam*> aTeam, vector<BaseballTeam*> *resTeam)
{
    int num = aTeam.size();
    bool res = false;

    vector<BaseballTeam*>::iterator teamIter;
    for (teamIter = aTeam.begin(); teamIter != aTeam.end(); teamIter++) {
        if (ref->GetWin() + ref->GetRemain() - (*teamIter)->GetWin() < 0) {
            resTeam->push_back(*teamIter);
            break;
        }
    }
    if (resTeam->size() != 0) return true;
        

    SJGraph* graph = new SJGraph(2 + num + num * (num - 1) / 2);
    int gameV = 1;
    int teamV = 1 + num * (num - 1) / 2;
    int numPossibleGame = 0;
    for(int i=0;i<aTeam.size();i++){
        for(int j=i+1;j<aTeam.size();j++){            
            graph->AddEdge(new SJEdge(0, gameV, aTeam[i]->GetAgainRemain(aTeam[j]->GetID())));
            numPossibleGame += aTeam[i]->GetAgainRemain(aTeam[j]->GetID());
            graph->AddEdge(new SJEdge(gameV, teamV, numeric_limits<float>::max()));
            graph->AddEdge(new SJEdge(gameV, teamV + (j - i), numeric_limits<float>::max()));
            gameV++;
        }
        graph->AddEdge(new SJEdge(teamV, graph->GetNumVertices() - 1, ref->GetWin() + ref->GetRemain() - aTeam[i]->GetWin()));
        
        teamV++;
    }
    //graph->PrintGraph();

    if (g_ff == NULL) {
    //    g_ff = new SJFoldFulkersonArray(graph->GetNumVertices());
        g_ff = new SJFoldFulkerson(graph->GetNumVertices());
    }
    //SJFoldFulkerson* g_ff = new SJFoldFulkerson(graph, 0, graph->GetNumVertices() - 1);
    //SJFoldFulkersonArray* ff = new SJFoldFulkersonArray(graph, 0, graph->GetNumVertices() - 1);
    g_ff->ComputeMaxFlow(graph, 0, graph->GetNumVertices() - 1);
    //printf("%d, %f\n", numPossibleGame, ff->GetMaxFlow());
    if (numPossibleGame > g_ff->GetMaxFlow()) {
        res = true;
    }
    //printf("After\n");
    //graph->PrintGraph();

    if (res == true) {
        for (int j = 0; j < aTeam.size(); j++) {
            if (g_ff->inCut(j + 1 + num * (num - 1) / 2)) {
                //certificate[ref].add(teamName[teamIDs[j]]);
                resTeam->push_back(aTeam[j]);
            }
        }
    }

    //delete g_ff;
    delete graph;

    return res;
}
void ComputeElimination(BaseballTeam** teams, int numTeam)
{
    vector<BaseballTeam*> aTeam;
    vector<BaseballTeam*> resTeam;
    vector<BaseballTeam*>::iterator iter;
    bool bEliminated;
    g_ff = NULL;
    for (int i = 0; i < numTeam; i++) {
    //for (int i = 1; i < 2; i++) {
        aTeam.clear();
        resTeam.clear();
        for (int j = 0; j < numTeam; j++) {
            if (i != j) aTeam.push_back(teams[j]);
        }
        bEliminated = ComputeElimination(teams[i], aTeam, &resTeam);
        if (bEliminated) {
            printf("%s is eliminated by the subset R = { ", teams[i]->GetName());
            for (iter = resTeam.begin(); iter != resTeam.end(); iter++) {
                printf(" %s ", (*iter)->GetName());
            }
            printf("}\n");
        }
        else {
            printf("%s is not eliminated\n", teams[i]->GetName());
        }
        //printf("%s, %d\n", teams[i]->GetName(), ComputeElimination(teams[i], aTeam, resTeam));
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

    /*for (int i = 0; i < numTeam; i++) {
        teams[i]->PrintInfo();
    }*/
    clock_t start = clock();
    ComputeElimination(teams, numTeam);
    clock_t end = clock();
    printf("Duration : %fms\n", (double)(end - start));
    
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
