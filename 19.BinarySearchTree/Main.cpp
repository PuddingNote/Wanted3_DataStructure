#include "BinarySearchTree.h"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// 트리 객체 생성.
	BinarySearchTree<int> tree;

	// 삽입.
	tree.Insert(10);
	tree.Insert(20);
	tree.Insert(30);
	tree.Insert(5);
	tree.Insert(1);
	tree.Insert(15);

	// 삭제.
	tree.Delete(5);
	tree.Delete(15);

	// 검색.
	Node<int>* result = nullptr;
	if (tree.Find(20, result))
	{
		std::cout << "20를 찾았습니다.\n";
	}
	else
	{
		std::cout << "20를 못찾았습니다.\n";
	}

	std::cin.get();
}