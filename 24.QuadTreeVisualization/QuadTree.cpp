#include "QuadTree.h"
#include <iostream>
#include <iomanip>

QuadTree::QuadTree(const Bounds& bounds)
	: root(new Node(bounds))
{
}

QuadTree::~QuadTree()
{
	SafeDelete(root);
}

void QuadTree::Insert(Node* node)
{
	root->Insert(node);
}

std::vector<Node*> QuadTree::Query(Node* queryNode)
{
	// 겹침 가능성이 있는 영역 확인.
	std::vector<Node*> possibleNode;
	root->Query(queryNode->GetBounds(), possibleNode);

	// 가능성이 있는 노드에서 실제로 겹치는 노드 검사.
	std::vector<Node*> intersects;

	// 겹침 가능성 있는 영역 순회.
	for (Node* node : possibleNode)
	{
		// 각 영역이 가지는 노드 순회.
		for (Node* point : node->GetPoints())
		{
			// 겹침 검사.
			if (point->GetBounds().Intersects(queryNode->GetBounds()))
			{
				intersects.emplace_back(point);
				continue;
			}
		}
	}

	// 최종 목록 반환.
	// 노트: 함수에서 출력용 배열을 참조로 받으면 최적화 가능.
	return intersects;
}

void QuadTree::PrintTree()
{
	if (root == nullptr)
	{
		std::cout << "쿼드트리가 비어있습니다!" << "\n";
		return;
	}

	std::cout << "\n=== 쿼드트리 시각화 ===" << "\n";
	std::cout << "루트: ";
	root->PrintTree(0);
	std::cout << "==============================\n" << "\n";
}

void QuadTree::PrintGrid(int gridWidth, int gridHeight)
{
	if (root == nullptr)
	{
		std::cout << "쿼드트리가 비어있습니다!" << "\n";
		return;
	}

	// 그리드 메모리 할당
	char** grid = new char* [gridHeight];
	for (int i = 0; i < gridHeight; i++)
	{
		grid[i] = new char[gridWidth];
		for (int j = 0; j < gridWidth; j++)
		{
			grid[i][j] = '.';
		}
	}

	// 스케일 계산 (실제 좌표를 그리드 좌표로 변환)
	float scaleX = (float)gridWidth / root->GetBounds().GetWidth();
	float scaleY = (float)gridHeight / root->GetBounds().GetHeight();

	// 트리 그리기
	root->DrawGrid(grid, gridWidth, gridHeight, scaleX, scaleY);

	// 그리드 출력
	std::cout << "\n=== 2D 그리드 시각화 ===" << "\n";
	std::cout << "범례: N=노드 경계, O=객체, .=빈 공간" << "\n";
	std::cout << "그리드 크기: " << gridWidth << "x" << gridHeight << "\n";
	std::cout << "스케일: X=" << scaleX << ", Y=" << scaleY << "\n";
	std::cout << "\n";

	// Y축 라벨과 함께 출력
	for (int y = 0; y < gridHeight; y++)
	{
		std::cout << std::setw(2) << y << " ";
		for (int x = 0; x < gridWidth; x++)
		{
			std::cout << grid[y][x];
		}
		std::cout << "\n";
	}

	// X축 라벨
	std::cout << "   ";
	for (int x = 0; x < gridWidth; x++)
	{
		std::cout << (x % 10);
	}
	std::cout << "\n";
	std::cout << "   ";
	for (int x = 0; x < gridWidth; x++)
	{
		if (x % 10 == 0)
			std::cout << (x / 10);
		else
			std::cout << " ";
	}
	std::cout << "\n";

	std::cout << "==============================\n" << "\n";

	// 메모리 해제
	for (int i = 0; i < gridHeight; i++)
	{
		delete[] grid[i];
	}
	delete[] grid;
}