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
	// ��ħ ���ɼ��� �ִ� ���� Ȯ��.
	std::vector<Node*> possibleNode;
	root->Query(queryNode->GetBounds(), possibleNode);

	// ���ɼ��� �ִ� ��忡�� ������ ��ġ�� ��� �˻�.
	std::vector<Node*> intersects;

	// ��ħ ���ɼ� �ִ� ���� ��ȸ.
	for (Node* node : possibleNode)
	{
		// �� ������ ������ ��� ��ȸ.
		for (Node* point : node->GetPoints())
		{
			// ��ħ �˻�.
			if (point->GetBounds().Intersects(queryNode->GetBounds()))
			{
				intersects.emplace_back(point);
				continue;
			}
		}
	}

	// ���� ��� ��ȯ.
	// ��Ʈ: �Լ����� ��¿� �迭�� ������ ������ ����ȭ ����.
	return intersects;
}

void QuadTree::PrintTree()
{
	if (root == nullptr)
	{
		std::cout << "����Ʈ���� ����ֽ��ϴ�!" << "\n";
		return;
	}

	std::cout << "\n=== ����Ʈ�� �ð�ȭ ===" << "\n";
	std::cout << "��Ʈ: ";
	root->PrintTree(0);
	std::cout << "==============================\n" << "\n";
}

void QuadTree::PrintGrid(int gridWidth, int gridHeight)
{
	if (root == nullptr)
	{
		std::cout << "����Ʈ���� ����ֽ��ϴ�!" << "\n";
		return;
	}

	// �׸��� �޸� �Ҵ�
	char** grid = new char* [gridHeight];
	for (int i = 0; i < gridHeight; i++)
	{
		grid[i] = new char[gridWidth];
		for (int j = 0; j < gridWidth; j++)
		{
			grid[i][j] = '.';
		}
	}

	// ������ ��� (���� ��ǥ�� �׸��� ��ǥ�� ��ȯ)
	float scaleX = (float)gridWidth / root->GetBounds().GetWidth();
	float scaleY = (float)gridHeight / root->GetBounds().GetHeight();

	// Ʈ�� �׸���
	root->DrawGrid(grid, gridWidth, gridHeight, scaleX, scaleY);

	// �׸��� ���
	std::cout << "\n=== 2D �׸��� �ð�ȭ ===" << "\n";
	std::cout << "����: N=��� ���, O=��ü, .=�� ����" << "\n";
	std::cout << "�׸��� ũ��: " << gridWidth << "x" << gridHeight << "\n";
	std::cout << "������: X=" << scaleX << ", Y=" << scaleY << "\n";
	std::cout << "\n";

	// Y�� �󺧰� �Բ� ���
	for (int y = 0; y < gridHeight; y++)
	{
		std::cout << std::setw(2) << y << " ";
		for (int x = 0; x < gridWidth; x++)
		{
			std::cout << grid[y][x];
		}
		std::cout << "\n";
	}

	// X�� ��
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

	// �޸� ����
	for (int i = 0; i < gridHeight; i++)
	{
		delete[] grid[i];
	}
	delete[] grid;
}