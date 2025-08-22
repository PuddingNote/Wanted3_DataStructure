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

	void AddToHead(int newData);	// ù ��忡 ������ �߰�
	void Insert(int newData);		// �ǵڿ� ��� �߰�
	void Delete(int data);			// ��� ����
	void Print();
	void Sort();

	int Count() const { return count; }

private:
	Node* head = nullptr;
	int count = 0;
};