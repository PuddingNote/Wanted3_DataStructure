#include <iostream>
#include "Tree.h"
#include "String.h"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	//String testString("Ronnie");
	//testString = testString + " Jang";
	//
	//std::cout << testString << "\n";

	// 트리 생성.
	Tree<String> tree("A");
	tree.AddChild("A", "B");	// A의 자손으로 B 추가.
	tree.AddChild("A", "C");	// A의 자손으로 C 추가.
	tree.AddChild("B", "D");	// B의 자손으로 D 추가.
	tree.AddChild("B", "E");	// B의 자손으로 E 추가.
	tree.AddChild("C", "F");	// C의 자손으로 F 추가.

	// 순회.
	std::cout << "트리 전위 순회\n";
	tree.PreorderTraverse();

	// 삭제.
	std::cout << "\nC 노드 삭제\n";
	tree.Remove("C");

	std::cout << "\n노드 삭제 후 전위 순회\n";
	tree.PreorderTraverse();

	std::cin.get();
}