// SJGraphCut.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include "SJGraph.h"
#include "SJFoldFulkerson.h"

int main()
{
	SJGraph* g = new SJGraph(3, 3);
	SJFoldFulkerson* ff = new SJFoldFulkerson(3, 3);

	unsigned char* img = new unsigned char[9];
	unsigned char* res = new unsigned char[9];

	img[0] = 90;
	img[1] = 80;
	img[2] = 60;
	img[3] = 40;
	img[4] = 30;
	img[5] = 10;
	img[6] = 20;
	img[7] = 10;
	img[8] = 0;

	res[0] = 255;
	res[8] = 0;
	for (int i = 1; i < 8; i++) {
		res[i] = 127;
	}

	int index;
	float sWeight;
	float tWeight;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			index = j + i * 3;
			if (res[index] == 255) {
				g->SetWeight(index, 10000, 0);
				g->SetWeight(index, 0, 1);
			}
			else if (res[index] == 0) {
				g->SetWeight(index, 10000, 1);
				g->SetWeight(index, 0, 0);
			}
			else {
				sWeight = img[index];
				tWeight = 100 - img[index];
				if (sWeight > tWeight) {
					g->SetWeight(index, sWeight - tWeight, 0);
					g->SetWeight(index, 0, 1);
				}
				else {
					g->SetWeight(index, 0, 0);
					g->SetWeight(index, tWeight - sWeight, 1);
				}
			}
			if (j - 1 >= 0) {
				g->SetWeight(index, 100 - abs(img[index] - img[index - 1]), 2);
			}
			if (j + 1 < 3) {
				g->SetWeight(index, 100 - abs(img[index] - img[index + 1]), 3);
			}
			if (i - 1 >= 0) {
				g->SetWeight(index, 100 - abs(img[index] - img[index - 3]), 4);
			}
			if (i + 1 < 3) {
				g->SetWeight(index, 100 - abs(img[index] - img[index + 3]), 5);
			}
		}
	}
	g->PrintInfo();
	ff->ComputeMaxFlow(g);
	g->PrintInfo();
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			index = j + i * 3;
			printf("%d\t", ff->inCut(index));
		}
		printf("\n");
	}
	delete[]img;
	delete g;
	delete ff;
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
