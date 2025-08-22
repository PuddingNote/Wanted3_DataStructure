#include "LinkedList.h"
#include <iostream>

LinkedList::LinkedList() : head(nullptr), count(0)
{

}

LinkedList::~LinkedList()
{
	Node* current = head;
	Node* trail = nullptr;

	while (current != nullptr)
	{
		trail = current;
		current = current->next;

		delete trail;
		trail = nullptr;

		--count;
	}
}

void LinkedList::AddToHead(int newData)
{
	// 새로운 노드 생성
	Node* newNode = new Node(newData);

	// #1: Head가 비어있는 경우
	if (head == nullptr)
	{
		head = newNode;
		++count;
		return;
	}

	// #2: Head가 비어있지 않은 경우
	newNode->next = head;
	head = newNode;
	++count;
}

// 맨 뒤에 데이터 추가하는 함수
void LinkedList::Insert(int newData)
{
	// 새 노드 생성
	Node* newNode = new Node(newData);

	// #1: 리스트가 비어있는 경우
	if (head == nullptr)
	{
		head = newNode;
		++count;
		return;
	}

	// #2: 리스트가 비어있지 않은 경우
	// 1. 마지막 노드 검색
	Node* current = head;
	Node* trail = nullptr;

	//while (current->next != nullptr)
	while (current != nullptr)
	{
		trail = current;
		current = current->next;
	}

	// 2. 마지막 노드가 newNode를 가리키게 변경
	trail->next = newNode;
	++count;
}

void LinkedList::Delete(int data)
{
	if (head == nullptr)
	{
		std::cout << "리스트가 비어있어서 삭제 불가능\n";
		return;
	}

	Node* current = head;
	Node* trail = nullptr;

	while (current != nullptr)
	{
		if (current->data == data)
		{
			break;
		}
		trail = current;
		current = current->next;
	}

	// #1: 검색에 실패한 경우
	if (current == nullptr)
	{
		std::cout << "값: " << data << " 를 찾지 못했습니다.\n";
		return;
	}

	// #2: 검색에 성공한 경우
	// 1. 삭제하려는 노드가 head인 경우
	if (current == head)
	{
		head = head->next;
	}

	// 2. 아닌경우
	else
	{
		trail->next = current->next;
	}

	// 삭제
	delete current;
	current = nullptr;
	--count;
}

// 모든 노드를 순회하면서 데이터 출력
void LinkedList::Print()
{
	Node* current = head;

	while (current != nullptr)
	{
		std::cout << *current << '\n';
		current = current->next;
	}
}

// 오름차순 정렬
void LinkedList::Sort()
{
	// 전체 노드를 count - 1번 반복 (현재와 다음을 비교하기 때문에 맨뒤는 제외)
	for (int i = 0; i < count - 1; ++i)
	{
		// current를 리스트의 첫번째인 head로 설정
		Node* current = head;
		// 두 노드를 비교할 것이기 때문에 head 다음 노드를 설정
		Node* nextNode = current->next;

		// 이미 뒤로 보낸 i개의 원소는 제외하고 비교 진행
		for (int j = 0; j < count - 1 - i; ++j)
		{
			// 다음 노드가 존재하고, 현재 노드의 데이터가 다음 노드의 데이터보다 크면 정렬되어 있지 않은 것이기 때문에 교환
			if (nextNode != nullptr && current->data > nextNode->data)
			{
				// 두 노드의 데이터값을 교환
				int temp = current->data;
				current->data = nextNode->data;
				nextNode->data = temp;
			}

			// 다음 비교를 하기위해 current 한칸 앞으로 이동
			current = nextNode;

			// 이걸 안넣어주면 Visual Studio가 current가 nullptr일 수도 있다는 경고 문구를 띄워줌
			// 실제로는 count-1-i만큼 반복하므로 마지막 반복이 끝난 직후를 제외하고는 nextNode가 nullptr이 될 일이 없음
			// 하지만 Visual Studio는 nullptr의 가능성을 보고 경고 문구를 띄움
			if (current != nullptr)
			{
				// 다음 비교를 하기위해 nextNode 한칸 앞으로 이동
				nextNode = current->next;
			}
		}
	}
}