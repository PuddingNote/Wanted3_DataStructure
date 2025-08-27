#include "Node.h"
#include "QuadTree.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>

Node::Node(const Bounds& bounds, int depth)
	: bounds(bounds), depth(depth)
{

}

Node::~Node()
{
	// ��带 ��� �����ϴ� �Լ� ȣ��.
	Clear();
}

// ����(Insert).
void Node::Insert(Node* node)
{
	// ��ġ���� ������ ���ԵǴ��� Ȯ��.
	NodeIndex result = TestRegion(node->GetBounds());

	// ���� ������ ���ƴ��� Ȯ��.
	if (result == NodeIndex::Straddling)
	{
		// ��ġ�� ��쿡�� ���� ��� �˻��� ���̻� ���ϰ�, 
		// ���� ��忡 �߰�.
		points.emplace_back(node);
	}
	// ��ġ�� ���� ���(���� �ȿ��� �־�� ��).
	else if (result != NodeIndex::OutOfArea)
	{
		// ����.
		if (Subdivide())
		{
			// ��� ������ ���Եƴ��� Ȯ�� �� ���� ��忡 �߰�.
			if (result == NodeIndex::TopLeft)
			{
				topLeft->Insert(node);
			}
			else if (result == NodeIndex::TopRight)
			{
				topRight->Insert(node);
			}
			else if (result == NodeIndex::BottomLeft)
			{
				bottomLeft->Insert(node);
			}
			else if (result == NodeIndex::BottomRight)
			{
				bottomRight->Insert(node);
			}

		}
		// �� �̻� ���� �� ���� ���.
		// ���� ��忡 �߰�.
		else
		{
			points.emplace_back(node);
		}
	}
}

// ����(Query).
void Node::Query(
	const Bounds& queryBounds,
	std::vector<Node*>& possibleNodes)
{
	// ���� ��� �߰�.
	possibleNodes.emplace_back(this);

	// ���� ��� �˻�(������ ���ҵ� ���).
	if (!IsDivided())
	{
		return;
	}

	// ��ġ�� 4�и� �˻�.
	std::vector<NodeIndex> quads = GetQuads(queryBounds);

	// ������ ó��.
	for (NodeIndex& index : quads)
	{
		if (index == NodeIndex::TopLeft)
		{
			topLeft->Query(queryBounds, possibleNodes);
		}
		else if (index == NodeIndex::TopRight)
		{
			topRight->Query(queryBounds, possibleNodes);
		}
		else if (index == NodeIndex::BottomLeft)
		{
			bottomLeft->Query(queryBounds, possibleNodes);
		}
		else if (index == NodeIndex::BottomRight)
		{
			bottomRight->Query(queryBounds, possibleNodes);
		}
	}
}

// ���� �Լ�.
void Node::Clear()
{
	// ���� ��� ����.
	for (Node* node : points)
	{
		SafeDelete(node);
	}
	points.clear();

	// ���ҵ� ��� �ڼ� ����.
	if (IsDivided())
	{
		// �ڼ� ����.
		topLeft->Clear();
		topRight->Clear();
		bottomLeft->Clear();
		bottomRight->Clear();

		// ����.
		SafeDelete(topLeft);
		SafeDelete(topRight);
		SafeDelete(bottomLeft);
		SafeDelete(bottomRight);
	}
}

NodeIndex Node::TestRegion(const Bounds& bounds)
{
	// ���޵� bounds�� ��ġ�� 4�и� ��� Ȯ��.
	std::vector<NodeIndex> quads = GetQuads(bounds);

	// ��ġ�� ���� ������ ���� ������ ǥ��.
	if (quads.size() == 0)
	{
		return NodeIndex::OutOfArea;
	}

	// �ϳ��� �ִ� ���(���� ����), �ش� 4�и� ��ȯ.
	if (quads.size() == 1)
	{
		return quads[0];
	}

	// ���� ������ ��ġ�� ��쿡�� ��ħ ��ȯ.
	return NodeIndex::Straddling;
}

std::vector<NodeIndex> Node::GetQuads(const Bounds& bounds)
{
	std::vector<NodeIndex> quads;

	// ���� ��꿡 �ʿ��� ����.
	float x = this->bounds.GetX();
	float y = this->bounds.GetY();
	float halfWidth = this->bounds.GetWidth() / 2.0f;
	float halfHeight = this->bounds.GetHeight() / 2.0f;
	float centerX = x + halfWidth;
	float centerY = y + halfHeight;

	// ���� ������ ���ƴ��� Ȯ��.
	bool left = bounds.GetX() < centerX && bounds.MaxX() >= x;

	// ������ ������ ���ƴ��� Ȯ��.
	bool right =
		bounds.MaxX() >= centerX
		&& bounds.GetX() < this->bounds.MaxX();

	// ���� ������ ���ƴ��� Ȯ��.
	bool top = bounds.GetY() < centerY
		&& bounds.MaxY() >= y;

	// �Ʒ��� ������ ���ƴ��� Ȯ��.
	bool bottom =
		bounds.MaxY() >= centerY
		&& bounds.GetY() < this->bounds.MaxY();

	if (top && left)
	{
		quads.emplace_back(NodeIndex::TopLeft);
	}
	if (top && right)
	{
		quads.emplace_back(NodeIndex::TopRight);
	}
	if (bottom && left)
	{
		quads.emplace_back(NodeIndex::BottomLeft);
	}
	if (bottom && right)
	{
		quads.emplace_back(NodeIndex::BottomRight);
	}

	return quads;
}

bool Node::Subdivide()
{
	// �ִ� ���̿� �����ߴ��� Ȯ��.
	// �����ߴٸ� �� �̻� ���� ����.
	if (depth == QuadTree::maxDepth)
	{
		return false;
	}

	// ���� ���� �ȵ����� ����.
	if (!IsDivided())
	{
		// ���� ������.

		// ���� ����� ���� ����.
		float x = bounds.GetX();
		float y = bounds.GetY();
		float halfWidth = bounds.GetWidth() / 2.0f;
		float halfHeight = bounds.GetHeight() / 2.0f;

		// ���� 4�и� ��ü ����.
		/*x        x + halfwidth   x + width
		* +------------+------------+ y
		  |    0 (TL)  |    1 (TR)  |
		  |            |            |
		  +------------+------------+ y + halfHeight
		  |    2 (BL)  |    3 (BR)  |
		  |            |            |
		  +------------+------------+ y + height
		*/
		topLeft = new Node(Bounds(x, y, halfWidth, halfHeight), depth + 1);
		topRight = new Node(Bounds(x + halfWidth, y, halfWidth, halfHeight), depth + 1);
		bottomLeft = new Node(Bounds(x, y + halfHeight, halfWidth, halfHeight), depth + 1);
		bottomRight = new Node(
			Bounds(x + halfWidth, y + halfHeight, halfWidth, halfHeight),
			depth + 1
		);
	}

	return true;
}

bool Node::IsDivided()
{
	// �ڼ� ��� �� �ϳ��� null�� �ƴϸ� ���� �Ϸ�� ����.
	// �ڼ� ���� ��� null �̰ų�(���� �ȵ�), ��� ����(���� ��).
	return topLeft != nullptr;
}

// �ð�ȭ �Լ��� ����
void Node::PrintTree(int indent)
{
	// �鿩���� ���
	std::string indentStr(indent * 2, ' ');

	// ���� ��� ���� ���
	std::cout << indentStr << "���� " << GetNodeInfo() << "\n";

	// �ڽ� ������ ������ ��������� ���
	if (IsDivided())
	{
		topLeft->PrintTree(indent + 1);
		topRight->PrintTree(indent + 1);
		bottomLeft->PrintTree(indent + 1);
		bottomRight->PrintTree(indent + 1);
	}
}

void Node::PrintBounds()
{
	std::cout << "Bounds: (" << bounds.GetX() << ", " << bounds.GetY()
		<< ") to (" << bounds.MaxX() << ", " << bounds.MaxY()
		<< ") [W:" << bounds.GetWidth() << " H:" << bounds.GetHeight() << "]" << "\n";
}

std::string Node::GetNodeInfo()
{
	std::string info = "���[����:" + std::to_string(depth) +
		" ����Ʈ:" + std::to_string(points.size()) +
		" ���:(" + std::to_string((int)bounds.GetX()) + "," +
		std::to_string((int)bounds.GetY()) + ")-(" +
		std::to_string((int)bounds.MaxX()) + "," +
		std::to_string((int)bounds.MaxY()) + ")]";

	if (IsDivided())
	{
		info += " [���ҵ�]";
	}

	return info;
}

// 2D �׸��� �ð�ȭ �Լ���
void Node::DrawGrid(char** grid, int gridWidth, int gridHeight, float scaleX, float scaleY)
{
	// ���� ��� �׸���
	DrawNode(grid, gridWidth, gridHeight, scaleX, scaleY, '#');

	// �ڽ� ������ ������ ��������� �׸���
	if (IsDivided())
	{
		topLeft->DrawGrid(grid, gridWidth, gridHeight, scaleX, scaleY);
		topRight->DrawGrid(grid, gridWidth, gridHeight, scaleX, scaleY);
		bottomLeft->DrawGrid(grid, gridWidth, gridHeight, scaleX, scaleY);
		bottomRight->DrawGrid(grid, gridWidth, gridHeight, scaleX, scaleY);
	}
}

void Node::DrawNode(char** grid, int gridWidth, int gridHeight, float scaleX, float scaleY, char symbol)
{
	// ����� ������ �׸��� ��ǥ�� ��ȯ
	int startX = (int)(bounds.GetX() * scaleX);
	int startY = (int)(bounds.GetY() * scaleY);
	int endX = (int)(bounds.MaxX() * scaleX);
	int endY = (int)(bounds.MaxY() * scaleY);

	// ��� Ȯ��
	startX = std::max(0, std::min(startX, gridWidth - 1));
	startY = std::max(0, std::min(startY, gridHeight - 1));
	endX = std::max(0, std::min(endX, gridWidth - 1));
	endY = std::max(0, std::min(endY, gridHeight - 1));

	// ��� ������ �׸��忡 �׸���
	for (int y = startY; y <= endY; y++)
	{
		for (int x = startX; x <= endX; x++)
		{
			// �׵θ��� �׸��� (���δ� ����α�)
			if (x == startX || x == endX || y == startY || y == endY)
			{
				grid[y][x] = symbol;
			}
		}
	}

	// ��忡 ���Ե� ��ü�� ǥ��
	for (const Node* point : points)
	{
		int objX = (int)(point->GetBounds().GetX() * scaleX);
		int objY = (int)(point->GetBounds().GetY() * scaleY);
		int objEndX = (int)(point->GetBounds().MaxX() * scaleX);
		int objEndY = (int)(point->GetBounds().MaxY() * scaleY);

		// ��� Ȯ��
		objX = std::max(0, std::min(objX, gridWidth - 1));
		objY = std::max(0, std::min(objY, gridHeight - 1));
		objEndX = std::max(0, std::min(objEndX, gridWidth - 1));
		objEndY = std::max(0, std::min(objEndY, gridHeight - 1));

		// ��ü�� 'O'�� ǥ��
		for (int y = objY; y <= objEndY; y++)
		{
			for (int x = objX; x <= objEndX; x++)
			{
				grid[y][x] = 'o';
			}
		}
	}
}