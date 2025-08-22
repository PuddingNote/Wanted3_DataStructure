#pragma once

#include "List.h"
#include "Node.h"

template<typename T>
class Tree
{
public:
	Tree(const T& data)
		: root(new Node<T>(data))	// 멤버 이니셜라이저.
	{
		//root = new Node<T>(data);
	}

	~Tree()
	{
		// 자손 모두 삭제.
		List<Node<T>*>& children = root->GetChildren();
		while (children.Size() > 0)
		{
			root->RemoveChild(children[0]);
		}

		// 루트 제거.
		delete root;
		root = nullptr;
	}

	void AddChild(const T& parentData, const T& childData)
	{
		// 1. 검색.
		Node<T>* outParent = nullptr;
		bool result = Find(parentData, outParent);

		// 부모 노드 검색에 성공 했으면, 부모 노드의 자손으로 노드 추가.
		if (result)
		{
			outParent->AddChild(childData);
			return;
		}

		// 부모 노드 검색 실패.
		std::cout << "해당 값을 갖는 부모 노드 검색에 실패했습니다.\n";
	}

	bool Remove(const T& data)
	{
		// 삭제할 노드를 검색하고, 삭제.
		Node<T>* outNode = nullptr;
		bool result = Find(data, outNode);

		// 검색 실패(삭제 실패).
		if (!result)
		{
			std::cout << "삭제할 노드를 찾지 못했습니다.\n";
			return false;
		}

		// 검색 성공.
		// 경우의 수1: 삭제할 노드가 루트 노드인 경우.
		// 루트는 제거하지 못하게.
		if (outNode == root)
		{
			//// 루트의 자손을 모두 제거.
			//while (root->GetChildren().Size() > 0)
			//{
			//	root->RemoveChild(root->GetChildren()[0]);
			//}

			//// 루트 노드 제거.
			//delete root;
			//root = nullptr;
			std::cout << "루트 노드는 삭제할 수 없습니다.\n";
			return false;
		}

		// 경우의 수2: 루트 노드가 아닌 경우.
		// 삭제할 노드의 부모 노드에게 삭제할 노드를 제거해달라고 요청.
		// parent는 항상 null이 아닌지?(보장할 수 있는지?).
		Node<T>* parent = outNode->GetParent();
		parent->RemoveChild(outNode);
		return true;
	}

	/// <summary>
	/// 데이터로 특정 노드를 검색하는 일반 함수.
	/// </summary>
	/// <param name="data">검색할 데이터</param>
	/// <param name="outNode">해당 데이터를 가진 노드(출력용)</param>
	/// <returns></returns>
	bool Find(const T& data, Node<T>*& outNode)
	{
		return FindRecursive(data, root, outNode);
	}

	bool FindRecursive(const T& data, Node<T>* node, Node<T>*& outNode)
	{
		// 재귀 함수 종료 조건.
		if (node == nullptr)
		{
			outNode = nullptr;
			return false;
		}

		// 검색 성공.
		if (node->GetData() == data)
		{
			outNode = node;
			return true;
		}

		// 자손을 재귀적으로 검색.
		List<Node<T>*>& children = node->GetChildren();
		int count = children.Size();
		for (int ix = 0; ix < count; ++ix)
		{
			// 자손 검색 진행.
			Node<T>* child = children[ix];
			bool result = FindRecursive(data, child, outNode);

			if (result)
			{
				return true;
			}
		}

		// 검색 실패.
		outNode = nullptr;
		return false;
	}

	// 전위 순회 함수 (부모를 먼저 방문 -> 자손 방문).
	void PreorderTraverse()
	{
		// 순회 재귀 함수 호출.
		PreorderTraverseRecursive(root);
	}

	// 전위 순회 재귀 함수.
	// node: 방문할 기준 노드.
	// depth: 출력할 때 부모-자손 구분을 위해 들여쓰기할 값.
	void PreorderTraverseRecursive(Node<T>* node, int depth = 0)
	{
		// 재귀 함수 종료 조건.
		// if (node == nullptr)
		if (!node)
		{
			return;
		}

		for (int ix = 0; ix < depth; ++ix)
		{
			std::cout << "    ";
		}

		// 부모 노드 방문.
		std::cout << node->GetData() << "\n";

		// 자손 방문.
		List<Node<T>*>& children = node->GetChildren();
		if (children.Size() == 0)
		{
			return;
		}

		for (int ix = 0; ix < children.Size(); ++ix)
		{
			Node<T>* child = children[ix];
			PreorderTraverseRecursive(child, depth + 1);
		}
	}

private:

	// 루트 노드.
	Node<T>* root = nullptr;
};