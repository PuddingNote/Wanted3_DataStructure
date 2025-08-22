#pragma once

#include <iostream>
#include "Node.h"

template<typename T>
class BinaryTree
{
public:
	BinaryTree()
		: root(nullptr)
	{
	}

	BinaryTree(const T& data)
	{
		// 루트 노드 생성.
		root = new Node<T>(data);
	}

	~BinaryTree()
	{
		// null 체크 후 삭제.
		if (root)
		{
			root->Destroy();
		}
	}

	// 자손 추가 함수.

	// 왼쪽 자손 추가.
	void AddLeftChild(const T& parentData, const T& childData)
	{
		// 1. 검색(부모 찾기).
		Node<T>* parent = nullptr;
		bool result = Find(parentData, parent);

		// 검색 성공.
		if (result)
		{
			parent->AddLeftChild(childData);
			return;
		}

		// 검색 실패.
		std::cout << "추가 실패: 부모 노드를 찾지 못했습니다.\n";
	}

	// 오른쪽 자손 추가.
	void AddRightChild(const T& parentData, const T& childData)
	{
		// 1. 검색(부모 찾기).
		Node<T>* parent = nullptr;
		bool result = Find(parentData, parent);

		// 검색 성공.
		if (result)
		{
			parent->AddRightChild(childData);
			return;
		}

		// 검색 실패.
		std::cout << "추가 실패: 부모 노드를 찾지 못했습니다.\n";
	}

	bool Find(const T& data, Node<T>*& outNode)
	{
		// 재귀 검색 함수 호출.
		return FindRecursive(data, root, outNode);
	}

	// 전위 순회 함수.
	void PreorderTraverse()
	{
		// 재귀 순회 함수 호출.
		PreorderTraverseRecursive(root);
	}

	// 삭제.
	bool DeleteNode(const T& data)
	{
		// 1 검색.
		Node<T>* deleteNode = nullptr;
		bool result = Find(data, deleteNode);

		// 찾았으면 삭제.
		if (result)
		{
			deleteNode->Destroy();
			return true;
		}

		// 못찾으면 메시지 출력.
		std::cout << "삭제 실패: 노드를 찾지 못했습니다.\n";
		return false;
	}

	// Getter.
	// 왼쪽/오른쪽 자손 반환 함수.
	Node<T>* GetLeft() const { return root->GetLeftChild(); }
	Node<T>* GetRight() const { return root->GetRightChild(); }

private:
	// 재귀 검색 함수.
	bool FindRecursive(const T& data, Node<T>* node, Node<T>*& outNode)
	{
		// 종료 조건.
		if (!node)
		{
			// 출력에 null 설정.
			outNode = nullptr;
			return false;
		}

		// 확인.
		if (node->GetData() == data)
		{
			outNode = node;
			return true;
		}

		// 왼쪽 자손으로 검색 진행.
		bool result = FindRecursive(data, node->GetLeftChild(), outNode);
		if (result)
		{
			return true;
		}

		// 오른쪽 자손으로 검색 진행.
		result = FindRecursive(data, node->GetRightChild(), outNode);
		if (result)
		{
			return true;
		}

		// 검색 실패.
		outNode = nullptr;
		return false;
	}

	// 재귀 전위 순회 함수.
	void PreorderTraverseRecursive(Node<T>* node, int depth = 0)
	{
		// 종료 조건.
		if (!node)
		{
			return;
		}

		for (int ix = 0; ix < depth; ++ix)
		{
			std::cout << "    ";
		}

		// 부모 방문.
		std::cout << node->GetData() << "\n";

		// 왼쪽 자손 방문.
		PreorderTraverseRecursive(node->GetLeftChild(), depth + 1);

		// 오른쪽 자손 방문.
		PreorderTraverseRecursive(node->GetRightChild(), depth + 1);
	}

private:

	// 루트 노드.
	Node<T>* root = nullptr;
};