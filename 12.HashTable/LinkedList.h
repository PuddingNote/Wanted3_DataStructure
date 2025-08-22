#pragma once

#include <iostream>
#include "HashTable.h"

template<typename T>
class Node
{
	template<typename T>
	friend class LinkedList;

public:
	Node()
		: data(), next(nullptr), previous(nullptr)
	{
	}

public:
	T data;						// 데이터 필드.
	Node<T>* next;				// 다음 노드 가리킴.
	Node<T>* previous;			// 이전 노드 가리킴.
};

template<typename T>
class LinkedList
{
public:
	LinkedList()
		: first(new Node<T>()), last(new Node<T>()), count(0)
	{
		first->next = last;
		last->previous = first;
	}

	LinkedList(void (*ListEmptyErrorHandler)())
		: LinkedList<T>()
	{
		this->ListEmptyErrorEvent = ListEmptyErrorHandler;
	}

	~LinkedList()
	{
		Clear();

		delete first;
		delete last;
	}

	// 노드 정리.
	void Clear()
	{
		// first의 다음 노드부터 시작.
		Node<T>* current = first->next;

		// 루프로 순회.
		while (current != nullptr && current != last)
		{
			Node<T>* next = current->next;
			delete current;
			current = next;
		}

		count = 0;
		first->next = last;
		last->previous = first;
	}

	// 순방향 검색.
	Node<T>* Find(const T& data)
	{
		Node<T>* current = first->next;

		while (current != nullptr && current != last)
		{
			if (current->data == data)
			{
				return current;
			}

			current = current->next;
		}

		return nullptr;
	}

	Node<T>* operator[](size_t targetIndex)
	{
		Node<T>* current = first->next;
		size_t index = 0;
		if (IsEmpty() == true)
		{
			RaiseDataEmptyEvent();
			return nullptr;
		}

		while (current != last && index < targetIndex)
		{
			current = current->next;
			++index;
		}

		return current;
	}

	// 순방향 검색.
	Node<T>* FindReverse(const T& data)
	{
		Node<T>* current = last->previous;

		while (current != nullptr && current != first)
		{
			if (current->data == data)
			{
				return current;
			}

			current = current->previous;
		}

		return nullptr;
	}

	// 맨 앞에 데이터 추가.
	void PushFirst(const T& data)
	{
		// 노드 생성.
		Node<T>* newNode = new Node<T>();
		newNode->data = data;

		// 포인터 연산 처리.
		// first->next 노드와 newNode.
		Node<T>* next = first->next;
		//newNode->next = first->next;
		newNode->next = next;
		//first->next->previous = newNode;
		next->previous = newNode;

		// newNode와 원래 first 노드.
		first->next = newNode;
		newNode->previous = first;

		// 데이터 개수 증가 처리.
		++count;
	}

	// 맨 뒤에 데이터 추가.
	void PushLast(const T& data)
	{
		// 새 노드 생성.
		Node<T>* newNode = new Node<T>();
		newNode->data = data;

		// 포인터 연산 처리.
		// last->previous노드와 newNode
		Node<T>* previous = last->previous;
		previous->next = newNode;
		newNode->previous = previous;

		// last 노드와 newNode
		newNode->next = last;
		last->previous = newNode;

		// 데이터 개수 추가 처리.
		++count;
	}

	// 리스트가 비었는지 확인.
	// 함수 이름 뒤에 const를 붙이면 함수 본문(내부)에서 변수 수정을 할 수 없다.
	bool IsEmpty() const
	{
		return count == 0;
	}

	// 삭제 연산.
	// 맨 뒤에서 삭제.
	void PopLast()
	{
		// 리스트가 비었는지 확인.
		// 비었으면 오류 이벤트 발생.
		if (IsEmpty() == true)
		{
			RaiseDataEmptyEvent();
			return;
		}

		// 포인터 연산 처리.
		Node<T>* deleteNode = last->previous;
		Node<T>* previous = deleteNode->previous;

		previous->next = last;
		last->previous = previous;

		// 마지막 노드 삭제.
		delete deleteNode;

		// 데이터 개수 감소 처리.
		--count;
	}

	// 맨 앞에서 삭제.
	void PopFirst()
	{
		// 리스트가 비었는지 확인.
		// 비었으면 오류 이벤트 발생.
		if (IsEmpty() == true)
		{
			RaiseDataEmptyEvent();
			return;
		}

		// 포인터 연산 처리.
		Node<T>* deleteNode = first->next;
		Node<T>* next = deleteNode->next;

		first->next = next;
		next->previous = first;

		// 첫번째 노드 삭제.
		delete deleteNode;

		// 데이터 개수 감소 처리.
		--count;
	}

	// 특정 위치의 노드 삭제.
	void Delete(const T& data)
	{
		// 리스트가 비었는지 확인.
		// 비었으면 오류 이벤트 발생.
		if (IsEmpty() == true)
		{
			RaiseDataEmptyEvent();
			return;
		}

		// 삭제할 노드 검색.
		Node<T>* deleteNode = first->next;

		// 순방향 검색.
		while (deleteNode != nullptr && deleteNode != last)
		{
			// 전달 받은 데이터와 같은 데이터를 가진 노드가 있는지 비교.
			if (deleteNode->data == data)
			{
				// 있으면 루프 종료.
				break;
			}

			// 다음 노드 검색.
			deleteNode = deleteNode->next;
		}

		// 검색 실패했으면 오류 이벤트 발생.
		if (deleteNode == nullptr || deleteNode == last)
		{
			RaiseDataEmptyEvent();
			return;
		}

		// 검색 성공했으면 해당 노드 삭제.
		deleteNode->previous->next = deleteNode->next;
		deleteNode->next->previous = deleteNode->previous;

		delete deleteNode;

		// 데이터 개수 감소 처리.
		--count;
	}

	// 데이터 반환.
	// 첫번째 데이터 반환.
	T First() const
	{
		// 리스트가 비었으면 오류 이벤트 발생.
		if (IsEmpty() == true)
		{
			RaiseDataEmptyEvent();
			return -1;
		}

		// 첫번째 노드의 데이터 반환.
		return first->next->data;
	}

	// 마지막 데이터 반환.
	T Last() const
	{
		// 리스트가 비었으면 오류 이벤트 발생.
		if (IsEmpty() == true)
		{
			RaiseDataEmptyEvent();
			return -1;
		}

		// 마지막 노드의 데이터 반환.
		return last->previous->data;
	}

	// 리스트 노드 개수 확인.
	size_t Count() const
	{
		return count;
	}

	// 데이터 출력.
	void Print()
	{
		// 순방향으로 순회하면서 데이터 출력.
		Node<T>* current = first->next;

		// 리스트에 저장된 데이터 항목 수 출력.
		std::cout << "리스트 항목 수: " << Count() << std::endl;
		// 루프로 순회하면서 데이터 값 출력.
		while (current != last)
		{
			std::cout << "데이터: " << current->data << " ";
			current = current->next;
		}

		// 모든 데이터 출력 완료하고 Enter.
		std::cout << std::endl;
	}

private:
	// 데이터가 비었을 때 발생하는 에러 이벤트.
	void RaiseDataEmptyEvent()
	{
		// 함수 포인터가 할당돼 있으면, 해당 함수 호출.
		if (ListEmptyErrorEvent != nullptr)
		{
			ListEmptyErrorEvent();
		}
	}

	Node<T>* first;
	Node<T>* last;
	size_t count;

	// 함수 포인터.
	// 콜백 예제.
	void (*ListEmptyErrorEvent)();
};