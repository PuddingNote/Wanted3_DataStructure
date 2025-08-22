#pragma once

#include "List.h"

template<typename T>
class Node
{
public:
	Node()
		: data(), parent(nullptr)
	{
	}

	Node(const T& data)
		: data(data), parent(nullptr)
	{
	}

	// 복사 생성자 제거.
	Node(const Node& other) = delete;
	//private:
		//Node(const Node& other)
		//{
		//}

	~Node()
	{
		parent = nullptr;
	}

	// 값을 전달해서 자손을 추가하는 함수.
	void AddChild(const T& data)
	{
		AddChild(new Node<T>(data));
	}

	void AddChild(Node<T>* child)
	{
		// 나를 추가될 자손의 부모로 설정.
		child->parent = this;

		// 자손 목록에 추가.
		children.PushBack(child);
	}

	// 자손 삭제 함수.
	// child: 제거할 자손 노드.
	void RemoveChild(Node<T>* child)
	{
		// 재귀적으로 자손의 자손까지 삭제하는 함수 호출.
		RemoveChildRecursive(child);
	}

	// Getter.
	T GetData() const
	{
		return data;
	}

	const List<Node<T>*>& GetChildren() const
	{
		return children;
	}

	List<Node<T>*>& GetChildren()
	{
		return children;
	}

	Node<T>* GetParent() const
	{
		return parent;
	}

	// Setter.
	void SetParent(Node<T>* const parent)
	{
		this->parent = parent;
	}

private:

	// 자손 노드를 삭제할 때 자손의 자손까지 재귀적으로 삭제하는 함수.
	void RemoveChildRecursive(Node<T>* child)
	{
		// 재귀 함수 종료 조건.
		if (!child)
		{
			return;
		}

		// 자손 목록 가져오기.
		List<Node<T>*>& children = child->GetChildren();

		// 경우의 수1: 자손이 없는 경우.
		if (children.Size() == 0)
		{
			// 부모의 자손 목록에서 나를 제거.
			child->GetParent()->GetChildren().Remove(child);

			// 메모리 정리.
			delete child;
			child = nullptr;	// 정리해주는 것 자체는 좋음.
			return;
		}

		// 경우의 수2: 자손이 있는 경우.
		while (children.Size() > 0)
		{
			// 자손을 순회하면서 재귀적으로 자손 제거.
			RemoveChildRecursive(children[0]);
		}

		// 자손을 모두 제거한 후에는 부모 목록에서 나를 제거.
		child->GetParent()->GetChildren().Remove(child);

		// 메모리 정리.
		delete child;
		child = nullptr;	// 정리해주는 것 자체는 좋음.
	}

private:

	// 노드에 저장할 데이터.
	T data;

	// 부모 참조 변수.
	Node<T>* parent = nullptr;

	// 자손 노드 리스트(동적 배열).
	List<Node<T>*> children;
};