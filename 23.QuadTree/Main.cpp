#include <iostream>
#include "QuadTree.h"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// 트리 생성.
	QuadTree tree(Bounds(0.0f, 0.0f, 100.f, 100.0f));

	// 32가지 (int).
	// 삽입.
	tree.Insert(new Node(Bounds(40.0f, 40.0f, 20.0f, 20.0f)));
	tree.Insert(new Node(Bounds(20.0f, 20.0f, 2.0f, 2.0f)));

	//Bounds bound = Bounds(50, 50, 5, 5);
	//Bounds bound(50, 50, 5, 5);
	//Bounds* bound = new Bounds(50, 50, 5, 5);

	// 쿼리(질의).
	Node testNode(Bounds(50, 50, 5, 5));
	std::vector<Node*> intersects = tree.Query(&testNode);

	// 검색 실패.
	if (intersects.size() == 0)
	{
		std::cout << "겹치는 노드를 찾지 못했습니다.\n";
	}
	else
	{
		std::cout << "겹치는 노드를 " << intersects.size() << "개 찾았습니다.\n";
	}

	std::cin.get();
}