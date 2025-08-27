#include <iostream>
#include "QuadTree.h"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	std::cout << "=== 쿼드트리 콘솔 시각화 데모 ===" << "\n";

	// 트리 생성 (100x100 크기)
	QuadTree tree(Bounds(0.0f, 0.0f, 100.f, 100.0f));
	std::cout << "쿼드트리 생성 완료: 경계 (0,0) ~ (100,100)" << "\n";

	// 노드들 삽입
	std::cout << "\n--- 노드 삽입 중 ---" << "\n";

	Node* node1 = new Node(Bounds(40.0f, 40.0f, 20.0f, 20.0f));
	Node* node2 = new Node(Bounds(20.0f, 20.0f, 2.0f, 2.0f));
	Node* node3 = new Node(Bounds(60.0f, 60.0f, 10.0f, 10.0f));
	Node* node4 = new Node(Bounds(10.0f, 10.0f, 5.0f, 5.0f));
	Node* node5 = new Node(Bounds(80.0f, 80.0f, 15.0f, 15.0f));

	tree.Insert(node1);
	std::cout << "노드 삽입 완료: 위치 (40,40), 크기 20x20" << "\n";

	tree.Insert(node2);
	std::cout << "노드 삽입 완료: 위치 (20,20), 크기 2x2" << "\n";

	tree.Insert(node3);
	std::cout << "노드 삽입 완료: 위치 (60,60), 크기 10x10" << "\n";

	tree.Insert(node4);
	std::cout << "노드 삽입 완료: 위치 (10,10), 크기 5x5" << "\n";

	tree.Insert(node5);
	std::cout << "노드 삽입 완료: 위치 (80,80), 크기 15x15" << "\n";

	// 트리 구조 시각화 (텍스트 트리)
	tree.PrintTree();

	// 2D 그리드 시각화
	tree.PrintGrid(50, 25);

	// 쿼리 테스트
	std::cout << "--- 쿼리 테스트 ---" << "\n";

	// 테스트 1: 중앙 영역 검색
	Node testNode1(Bounds(50, 50, 5, 5));
	std::vector<Node*> intersects1 = tree.Query(&testNode1);
	std::cout << "쿼리: 경계 (50,50), 크기 5x5" << "\n";
	std::cout << "발견된 교차 노드 수: " << intersects1.size() << "\n";

	// 테스트 2: 왼쪽 상단 영역 검색
	Node testNode2(Bounds(15, 15, 10, 10));
	std::vector<Node*> intersects2 = tree.Query(&testNode2);
	std::cout << "쿼리: 경계 (15,15), 크기 10x10" << "\n";
	std::cout << "발견된 교차 노드 수: " << intersects2.size() << "\n";

	// 테스트 3: 오른쪽 하단 영역 검색
	Node testNode3(Bounds(85, 85, 5, 5));
	std::vector<Node*> intersects3 = tree.Query(&testNode3);
	std::cout << "쿼리: 경계 (85,85), 크기 5x5" << "\n";
	std::cout << "발견된 교차 노드 수: " << intersects3.size() << "\n";

	// 메모리 정리
	/*delete node1;
	delete node2;
	delete node3;
	delete node4;
	delete node5;*/

	std::cout << "\n종료하려면 Enter를 누르세요...";
	std::cin.get();
}