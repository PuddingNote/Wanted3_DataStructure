#pragma once

/*
* 작성자: 장세윤.
* 이진 탐색 트리에 사용할 노드 클래스.
*/
template<typename T>
class Node
{
public:
	// 생성자.
	Node(const T& data, Node<T>* parent = nullptr)
		: data(data), parent(parent)
	{
	}

	// 노드가 저장할 데이터.
	T GetData() const { return data; }
	void SetData(const T& newData) { data = newData; }

	// 부모.
	Node<T>* GetParent() const { return parent; }
	void SetParent(Node<T>* newParent) { parent = newParent; }

	// 왼쪽 자손.
	Node<T>* GetLeft() const { return left; }
	void SetLeft(Node<T>* newLeft) { left = newLeft; }

	// 오른쪽 자손.
	Node<T>* GetRight() const { return right; }
	void SetRight(Node<T>* newRight) { right = newRight; }

private:
	// 노드가 저장할 데이터.
	T data;

	// 부모.
	Node<T>* parent = nullptr;

	// 왼쪽 자손.
	Node<T>* left = nullptr;

	// 오른쪽 자손.
	Node<T>* right = nullptr;
};