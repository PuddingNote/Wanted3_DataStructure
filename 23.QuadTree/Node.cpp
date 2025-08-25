#include "Node.h"
#include "QuadTree.h"

Node::Node(const Bounds& bounds, int depth)
	: bounds(bounds), depth(depth)
{

}

Node::~Node()
{
	// 노드를 모두 제거하는 함수 호출.
	Clear();
}

// 삽입(Insert).
void Node::Insert(Node* node)
{
	// 겹치는지 완전히 포함되는지 확인.
	NodeIndex result = TestRegion(node->GetBounds());

	// 여러 영역과 겹쳤는지 확인.
	if (result == NodeIndex::Straddling)
	{
		// 겹치는 경우에는 하위 노드 검색을 더이상 안하고, 
		// 현재 노드에 추가.
		points.emplace_back(node);
	}
	// 겹치지 않은 경우(영역 안에는 있어야 함).
	else if (result != NodeIndex::OutOfArea)
	{
		// 분할.
		if (Subdivide())
		{
			// 어느 영역에 포함됐는지 확인 후 하위 노드에 추가.
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
		// 더 이상 나눌 수 없는 경우.
		// 현재 노드에 추가.
		else
		{
			points.emplace_back(node);
		}
	}
}

// 질의(Query).
void Node::Query(
	const Bounds& queryBounds,
	std::vector<Node*>& possibleNodes)
{
	// 현재 노드 추가.
	possibleNodes.emplace_back(this);

	// 하위 노드 검색(영역이 분할된 경우).
	if (!IsDivided())
	{
		return;
	}

	// 겹치는 4분면 검사.
	std::vector<NodeIndex> quads = GetQuads(queryBounds);

	// 루프로 처리.
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

// 정리 함수.
void Node::Clear()
{
	// 현재 노드 정리.
	for (Node* node : points)
	{
		SafeDelete(node);
	}
	points.clear();

	// 분할된 경우 자손 정리.
	if (IsDivided())
	{
		// 자손 정리.
		topLeft->Clear();
		topRight->Clear();
		bottomLeft->Clear();
		bottomRight->Clear();

		// 정리.
		SafeDelete(topLeft);
		SafeDelete(topRight);
		SafeDelete(bottomLeft);
		SafeDelete(bottomRight);
	}
}

NodeIndex Node::TestRegion(const Bounds& bounds)
{
	// 전달된 bounds와 겹치는 4분면 목록 확인.
	std::vector<NodeIndex> quads = GetQuads(bounds);

	// 겹치는 곳이 없으면 영역 밖으로 표기.
	if (quads.size() == 0)
	{
		return NodeIndex::OutOfArea;
	}

	// 하나만 있는 경우(완전 포함), 해당 4분면 반환.
	if (quads.size() == 1)
	{
		return quads[0];
	}

	// 여러 영역과 겹치는 경우에는 겹침 반환.
	return NodeIndex::Straddling;
}

std::vector<NodeIndex> Node::GetQuads(const Bounds& bounds)
{
	std::vector<NodeIndex> quads;

	// 영역 계산에 필요한 변수.
	float x = this->bounds.GetX();
	float y = this->bounds.GetY();
	float halfWidth = this->bounds.GetWidth() / 2.0f;
	float halfHeight = this->bounds.GetHeight() / 2.0f;
	float centerX = x + halfWidth;
	float centerY = y + halfHeight;

	// 왼쪽 영역과 겹쳤는지 확인.
	bool left = bounds.GetX() < centerX && bounds.MaxX() >= x;

	// 오른쪽 영역과 겹쳤는지 확인.
	bool right =
		bounds.MaxX() >= centerX
		&& bounds.GetX() < this->bounds.MaxX();

	// 위쪽 영역과 겹쳤는지 확인.
	bool top = bounds.GetY() < centerY
		&& bounds.MaxY() >= y;

	// 아래쪽 영역과 겹쳤는지 확인.
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
	// 최대 깊이에 도달했는지 확인.
	// 도달했다면 더 이상 분할 안함.
	if (depth == QuadTree::maxDepth)
	{
		return false;
	}

	// 아직 분할 안됐으면 분할.
	if (!IsDivided())
	{
		// 영역 나누기.

		// 영역 계산을 위한 변수.
		float x = bounds.GetX();
		float y = bounds.GetY();
		float halfWidth = bounds.GetWidth() / 2.0f;
		float halfHeight = bounds.GetHeight() / 2.0f;

		// 분할 4분면 객체 생성.
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
	// 자손 노드 중 하나가 null이 아니면 분할 완료된 상태.
	// 자손 노드는 모두 null 이거나(분할 안됨), 모두 생성(분할 됨).
	return topLeft != nullptr;
}