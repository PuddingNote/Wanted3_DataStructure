#pragma once

#include "Node.h"

//#ifdef _DEBUG
//#define new new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
//// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
//// allocations to be of _CLIENT_BLOCK type
//#else
//#define new new
//#endif

class LinkedList
{
public:
	LinkedList();
	~LinkedList();

	void AddToHead(int newData);	// 첫 노드에 데이터 추가
	void Insert(int newData);		// 맨뒤에 노드 추가
	void Delete(int data);			// 노드 삭제
	void Print();
	void Sort();

	int Count() const { return count; }

private:
	Node* head = nullptr;
	int count = 0;
};