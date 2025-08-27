#pragma once

#include "Bounds.h"

#include <vector>
#include <string>

// ������ ���� ���� �Լ�.
template<typename T>
void SafeDelete(T*& pointer)
{
	if (pointer)
	{
		delete pointer;
		pointer = nullptr;
	}
}

// ���� ������ ���� ������.
enum class NodeIndex
{
	// ������ �����ϴ� ���.
	TopLeft,		// ���� ���.
	TopRight,		// ������ ���.
	BottomLeft,		// ���� �ϴ�.
	BottomRight,	// ������ �ϴ�.

	Straddling,		// �� ������ ��ģ ���.
	OutOfArea,		// ������ ��� ���.
};

class Node
{
public:

	Node(const Bounds& bounds, int depth = 0);
	~Node();

	// ����(Insert).
	void Insert(Node* node);

	// ����(Query).
	void Query(const Bounds& queryBounds, std::vector<Node*>& possibleNodes);

	// ���� �Լ�.
	void Clear();

	// Getter.
	Bounds GetBounds() const { return bounds; }

	// ���� ��忡 ���Ե� ��� (�迭).
	const std::vector<Node*>& GetPoints() const { return points; }

	// �ڽ� ���.
	Node* GetTopLeft() const { return topLeft; }
	Node* GetTopRight() const { return topRight; }
	Node* GetBottomLeft() const { return bottomLeft; }
	Node* GetBottomRight() const { return bottomRight; }

	// �ð�ȭ �Լ���
	void PrintTree(int indent = 0);
	void PrintBounds();
	std::string GetNodeInfo();

	// 2D �׸��� �ð�ȭ �Լ���
	void DrawGrid(char** grid, int gridWidth, int gridHeight, float scaleX, float scaleY);
	void DrawNode(char** grid, int gridWidth, int gridHeight, float scaleX, float scaleY, char symbol);

private:

	// ��ġ���� �Ǵ� ���ԵǴ����� Ȯ���ϴ� �Լ�.
	NodeIndex TestRegion(const Bounds& bounds);

	// ��û�� Bounds�� ��ġ�� 4�и� ��� ��ȯ �Լ�.
	std::vector<NodeIndex> GetQuads(const Bounds& bounds);

	// 4�и� ���� �Լ�.
	bool Subdivide();

	// ���ҵƴ��� Ȯ���ϴ� �Լ�.
	bool IsDivided();

private:
	// ����.
	int depth = 0;

	// ����.
	Bounds bounds;

	// ���� ��忡 ���Ե� ��� (�迭).
	std::vector<Node*> points;

	// �ڽ� ���.
	Node* topLeft = nullptr;
	Node* topRight = nullptr;
	Node* bottomLeft = nullptr;
	Node* bottomRight = nullptr;
};