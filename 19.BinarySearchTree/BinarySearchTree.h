#pragma once

/*
* 이진 탐색 트리 클래스.
*/

#ifdef _DEBUG
#define new new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define new new
#endif

#include <iostream>
#include "Node.h"

template<typename T>
class BinarySearchTree
{
public:
	BinarySearchTree() = default;
	~BinarySearchTree()
	{
		// 삭제 함수 호출.
		Destroy();
	}

	// 삽입.
	// 규칙.
	// 1. 중복된 값은 허용하지 않는다. (검색이 필요함).
	// 2. 루트에서부터 비교 시작.
	// 2-1. 루트가 null이면 새 노드를 루트로 지정.
	// 3. 새로 추가하는 값이 비교 노드보다 작으면 왼쪽 하위 트리로 비교 이어감.
	// 4. 새로 추가하는 값이 비교 노드보다 크면 오른쪽 하위 트리로 비교 이어감.
	bool Insert(const T& data)
	{
		// 추가하려는 값이 이미 있는지 검색.
		// 중복 허용 X.
		Node<T>* outNode = nullptr;
		if (Find(data, outNode))
		{
			std::cout << "Error: 중복된 값이 있어서 노드를 추가하지 못했습니다.\n";
			return false;
		}

		// 루트가 null이면 루트로 지정.
		if (!root)
		{
			root = new Node<T>(data);
			return true;
		}

		// 삽입 재귀 함수 호출.
		root = InsertRecursive(data, root, nullptr);
		return true;
	}

	// 검색.
	bool Find(const T& data, Node<T>*& outNode) const
	{
		// 재귀적으로 검색하는 함수 호출. (루트부터 검색 시작).
		return FindRecursive(data, root, outNode);
	}

	// 삭제.
	bool Delete(const T& data)
	{
		// 검색 (삭제할 노드 검색).
		Node<T>* deleteNode = nullptr;
		if (!Find(data, deleteNode))
		{
			std::cout << "Error: 삭제할 노드를 찾지 못했습니다.\n";
			return false;
		}

		// 재귀적으로 삭제하는 함수 호출.
		root = DeleteRecursive(data, root);
		return true;
	}

	// 중위 순회 (정렬된 순서대로 출력 가능함).

	// 최솟값 검색.
	Node<T>* FindMinValue(Node<T>* node)
	{
		// 가장 왼쪽 끝에 있는 노드 검색.
		while (node->GetLeft())
		{
			node = node->GetLeft();
		}

		return node;
	}

	// 최댓값 검색.
	Node<T>* FindMaxValue(Node<T>* node)
	{
		// 가장 오른쪽 끝에 있는 노드 검색.
		while (node->GetRight())
		{
			node = node->GetRight();
		}

		return node;
	}

private:
	// 재귀 검색 함수.
	bool FindRecursive(const T& data, Node<T>* node, Node<T>*& outNode) const
	{
		// 종료 조건.
		if (!node)
		{
			outNode = nullptr;
			return false;
		}

		// 검색 성공했는지 확인.
		if (node->GetData() == data)
		{
			outNode = node;
			return true;
		}

		// 찾는 데이터가 작은 경우.
		if (node->GetData() > data)
		{
			// 왼쪽 하위 트리로 검색 더 진행.
			return FindRecursive(data, node->GetLeft(), outNode);
		}

		// 오른쪽 하위 트리로 검색 더 진행.
		return FindRecursive(data, node->GetRight(), outNode);
	}

	// 재귀 삽입 함수.
	// 추가하려는 데이터가 작으면 왼쪽, 크면 오른쪽으로 내려가면서 삽입.
	// 삽입할 위치: 더이상 내려가지 못하는 경우 = node가 null인 경우.
	Node<T>* InsertRecursive(const T& data, Node<T>* node, Node<T>* parent)
	{
		// 종료 조건 (삽입).
		if (!node)
		{
			// 삽입.
			return new Node<T>(data, parent);
		}

		// 작은 경우 (왼쪽 하위 트리에 삽입).
		if (node->GetData() > data)
		{
			node->SetLeft(InsertRecursive(data, node->GetLeft(), node));
		}

		// 큰 경우 (오른쪽 하위 트리에 삽입).
		else
		{
			node->SetRight(InsertRecursive(data, node->GetRight(), node));
		}

		// 마지막으로 검색하는 노드 반환.
		return node;
	}

	// 재귀 삭제 함수.
	Node<T>* DeleteRecursive(const T& data, Node<T>* node)
	{
		// 종료 조건.
		if (!node)
		{
			return nullptr;
		}

		// 작은 경우.
		if (node->GetData() > data)
		{
			node->SetLeft(DeleteRecursive(data, node->GetLeft()));
		}

		// 큰 경우.
		else if (node->GetData() < data)
		{
			node->SetRight(DeleteRecursive(data, node->GetRight()));
		}

		// 삭제할 노드 찾음.
		else
		{
			// 삭제 처리.
			//        10
			//        /\
			//       5 15
			//      /\
			//     1  7
			//        /\
			//       6  8

			// 경우의 수1 (자식이 둘 다 없는 경우).
			if (!node->GetLeft() && !node->GetRight())
			{
				delete node;
				return nullptr;
			}

			// 경우의 수2 (자식이 둘 다 있는 경우).
			if (node->GetLeft() && node->GetRight())
			{
				// 방법을 택1.
				// 1. 왼쪽 하위에서 가장 큰 값으로 대체.
				// 2. 오른쪽 하위에서 가장 작은 값으로 대체.

				// 삭제할 위치의 노드 값을 대체 값으로 할당.
				node->SetData(
					FindMinValue(node->GetRight())->GetData()
				);

				// 대체 당하는 노드를 삭제.
				node->SetRight(
					DeleteRecursive(node->GetData(), node->GetRight())
				);
			}

			// 경우의 수3 (자식이 하나만 있는 경우).
			else
			{
				// 왼쪽만 있는 경우.
				if (node->GetLeft())
				{
					// 왼쪽 자손을 반환하기 위해 임시 저장.
					Node<T>* left = node->GetLeft();

					// 노드 삭제.
					delete node;

					// 왼쪽 자손 반환.
					return left;
				}

				// 오른쪽만 있는 경우.
				else if (node->GetRight())
				{
					// 오른쪽 자손을 반환하기 위해 임시 저장.
					Node<T>* right = node->GetRight();

					// 노드 삭제.
					delete node;

					// 오른쪽 자손 반환.
					return right;
				}
			}
		}

		return node;
	}

	void Destroy()
	{
		// 루트가 비었으면 종료.
		if (!root)
		{
			return;
		}

		// 자손도 모두 제거하고 루트 제거하도록 처리.
		DestroyRecursive(root);
	}

	// 파괴 재귀 함수.
	void DestroyRecursive(Node<T>* node)
	{
		// 종료 조건.
		if (!node)
		{
			return;
		}

		// 자손 정보 가져오기.
		Node<T>* left = node->GetLeft();
		Node<T>* right = node->GetRight();

		// 자손이 없으면.
		if (!left && !right)
		{
			delete node;
			node = nullptr;
			return;
		}

		// 자손이 있으면 재귀적으로 한번 더 진행.
		DestroyRecursive(left);
		DestroyRecursive(right);

		// 자손 모두 제거 후 노드 제거.
		delete node;
		node = nullptr;
	}

private:

	// 루트 노드.
	Node<T>* root = nullptr;
};