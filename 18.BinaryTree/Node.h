#pragma once

// 컴파일 방식.
// AOT / JIT.
// AOT: Ahead Of Time. -> 미리(기계어 변환) 기존의 언어들(c/c++/object-c...) -> Mac
// JIT: Just In Time.  -> 직전에(기계어 변환) C# -> MS/Android.

/*
* 이진 트리에 사용될 노드 클래스.
*/
template<typename T>
class Node
{
	// friend 선언.
	template<typename T>
	friend class BinaryTree;

	// public 함수(메소드) = 인터페이스(명세).
public:

	// 생성자.
	Node()
		: data(), parent(nullptr), left(nullptr), right(nullptr)
	{
	}

	Node(const T& data)
		: data(data), parent(nullptr), left(nullptr), right(nullptr)
	{
	}

	// 기본 소멸자를 명시적으로 지정.
	~Node() = default;

	// ------------------ //
	// 자손 추가 함수. AddLeftChild / AddRightChild.
	void AddLeftChild(const T& data)
	{
		// 노드를 생성해서 다른 함수 호출.
		AddLeftChild(new Node<T>(data));
	}

	void AddLeftChild(Node<T>* child)
	{
		// child의 부모 설정 (나로).
		child->SetParent(this);

		// 왼쪽 자손 설정.
		left = child;
	}

	// 자손 추가 함수. AddRightChild.
	void AddRightChild(const T& data)
	{
		// 노드를 생성해서 다른 함수 호출.
		AddRightChild(new Node<T>(data));
	}

	void AddRightChild(Node<T>* child)
	{
		// child의 부모 설정 (나로).
		child->SetParent(this);

		// 오른쪽 자손 설정.
		right = child;
	}

	// 삭제 함수.
	void Destroy()
	{
		// 부모 노드 정리.
		if (parent)
		{
			// 이 노드가 부모 기준 왼쪽인지 확인.
			if (parent->GetLeftChild() == this)
			{
				parent->left = nullptr;
			}

			// 이 노드가 부모 기준 오른쪽인지 확인.
			else if (parent->GetRightChild() == this)
			{
				parent->right = nullptr;
			}
		}

		// 자손까지 방문해서 모두 제거.
		DestroyRecursive(this);
	}

	// Getter/Setter.
	T GetData() const { return data; }

	Node<T>* GetParent() const { return parent; }
	void SetParent(Node<T>* newParent) { parent = newParent; }

	Node<T>* GetLeftChild() const { return left; }
	Node<T>* GetRightChild() const { return right; }

	// public 메소드 = 메시지 (인터페이스).
	// private 메소드.
private:

	// 삭제 재귀 함수.
	void DestroyRecursive(Node<T>* node)
	{
		// 탈출 조건.
		if (!node)
		{
			return;
		}

		// 자손 노드의 존재 확인.
		Node<T>* leftChild = node->GetLeftChild();
		Node<T>* rightChild = node->GetRightChild();

		// 경우의 수1: 자손이 없는 경우.
		if (leftChild == nullptr && rightChild == nullptr)
		{
			// 본인 삭제 후 종료.
			delete node;
			node = nullptr;
			return;
		}

		// 경우의 수2: 자손이 있는 경우.
		// 재귀적으로 자손 노드를 삭제.
		DestroyRecursive(leftChild);
		DestroyRecursive(rightChild);

		// 본인 삭제.
		delete node;
		node = nullptr;
	}

private:

	// 데이터.
	T data;

	// 부모 노드 포인터.
	Node<T>* parent = nullptr;

	// 왼쪽 자손 포인터.
	Node<T>* left = nullptr;

	// 오른쪽 자손 포인터.
	Node<T>* right = nullptr;
};