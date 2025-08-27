#include <iostream>
#include "QuadTree.h"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	std::cout << "=== ����Ʈ�� �ܼ� �ð�ȭ ���� ===" << "\n";

	// Ʈ�� ���� (100x100 ũ��)
	QuadTree tree(Bounds(0.0f, 0.0f, 100.f, 100.0f));
	std::cout << "����Ʈ�� ���� �Ϸ�: ��� (0,0) ~ (100,100)" << "\n";

	// ���� ����
	std::cout << "\n--- ��� ���� �� ---" << "\n";

	Node* node1 = new Node(Bounds(40.0f, 40.0f, 20.0f, 20.0f));
	Node* node2 = new Node(Bounds(20.0f, 20.0f, 2.0f, 2.0f));
	Node* node3 = new Node(Bounds(60.0f, 60.0f, 10.0f, 10.0f));
	Node* node4 = new Node(Bounds(10.0f, 10.0f, 5.0f, 5.0f));
	Node* node5 = new Node(Bounds(80.0f, 80.0f, 15.0f, 15.0f));

	tree.Insert(node1);
	std::cout << "��� ���� �Ϸ�: ��ġ (40,40), ũ�� 20x20" << "\n";

	tree.Insert(node2);
	std::cout << "��� ���� �Ϸ�: ��ġ (20,20), ũ�� 2x2" << "\n";

	tree.Insert(node3);
	std::cout << "��� ���� �Ϸ�: ��ġ (60,60), ũ�� 10x10" << "\n";

	tree.Insert(node4);
	std::cout << "��� ���� �Ϸ�: ��ġ (10,10), ũ�� 5x5" << "\n";

	tree.Insert(node5);
	std::cout << "��� ���� �Ϸ�: ��ġ (80,80), ũ�� 15x15" << "\n";

	// Ʈ�� ���� �ð�ȭ (�ؽ�Ʈ Ʈ��)
	tree.PrintTree();

	// 2D �׸��� �ð�ȭ
	tree.PrintGrid(50, 25);

	// ���� �׽�Ʈ
	std::cout << "--- ���� �׽�Ʈ ---" << "\n";

	// �׽�Ʈ 1: �߾� ���� �˻�
	Node testNode1(Bounds(50, 50, 5, 5));
	std::vector<Node*> intersects1 = tree.Query(&testNode1);
	std::cout << "����: ��� (50,50), ũ�� 5x5" << "\n";
	std::cout << "�߰ߵ� ���� ��� ��: " << intersects1.size() << "\n";

	// �׽�Ʈ 2: ���� ��� ���� �˻�
	Node testNode2(Bounds(15, 15, 10, 10));
	std::vector<Node*> intersects2 = tree.Query(&testNode2);
	std::cout << "����: ��� (15,15), ũ�� 10x10" << "\n";
	std::cout << "�߰ߵ� ���� ��� ��: " << intersects2.size() << "\n";

	// �׽�Ʈ 3: ������ �ϴ� ���� �˻�
	Node testNode3(Bounds(85, 85, 5, 5));
	std::vector<Node*> intersects3 = tree.Query(&testNode3);
	std::cout << "����: ��� (85,85), ũ�� 5x5" << "\n";
	std::cout << "�߰ߵ� ���� ��� ��: " << intersects3.size() << "\n";

	// �޸� ����
	/*delete node1;
	delete node2;
	delete node3;
	delete node4;
	delete node5;*/

	std::cout << "\n�����Ϸ��� Enter�� ��������...";
	std::cin.get();
}