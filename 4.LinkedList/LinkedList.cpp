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
	// ���ο� ��� ����
	Node* newNode = new Node(newData);

	// #1: Head�� ����ִ� ���
	if (head == nullptr)
	{
		head = newNode;
		++count;
		return;
	}

	// #2: Head�� ������� ���� ���
	newNode->next = head;
	head = newNode;
	++count;
}

// �� �ڿ� ������ �߰��ϴ� �Լ�
void LinkedList::Insert(int newData)
{
	// �� ��� ����
	Node* newNode = new Node(newData);

	// #1: ����Ʈ�� ����ִ� ���
	if (head == nullptr)
	{
		head = newNode;
		++count;
		return;
	}

	// #2: ����Ʈ�� ������� ���� ���
	// 1. ������ ��� �˻�
	Node* current = head;
	Node* trail = nullptr;

	//while (current->next != nullptr)
	while (current != nullptr)
	{
		trail = current;
		current = current->next;
	}

	// 2. ������ ��尡 newNode�� ����Ű�� ����
	trail->next = newNode;
	++count;
}

void LinkedList::Delete(int data)
{
	if (head == nullptr)
	{
		std::cout << "����Ʈ�� ����־ ���� �Ұ���\n";
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

	// #1: �˻��� ������ ���
	if (current == nullptr)
	{
		std::cout << "��: " << data << " �� ã�� ���߽��ϴ�.\n";
		return;
	}

	// #2: �˻��� ������ ���
	// 1. �����Ϸ��� ��尡 head�� ���
	if (current == head)
	{
		head = head->next;
	}

	// 2. �ƴѰ��
	else
	{
		trail->next = current->next;
	}

	// ����
	delete current;
	current = nullptr;
	--count;
}

// ��� ��带 ��ȸ�ϸ鼭 ������ ���
void LinkedList::Print()
{
	Node* current = head;

	while (current != nullptr)
	{
		std::cout << *current << '\n';
		current = current->next;
	}
}

// �������� ����
void LinkedList::Sort()
{
	// ��ü ��带 count - 1�� �ݺ� (����� ������ ���ϱ� ������ �ǵڴ� ����)
	for (int i = 0; i < count - 1; ++i)
	{
		// current�� ����Ʈ�� ù��°�� head�� ����
		Node* current = head;
		// �� ��带 ���� ���̱� ������ head ���� ��带 ����
		Node* nextNode = current->next;

		// �̹� �ڷ� ���� i���� ���Ҵ� �����ϰ� �� ����
		for (int j = 0; j < count - 1 - i; ++j)
		{
			// ���� ��尡 �����ϰ�, ���� ����� �����Ͱ� ���� ����� �����ͺ��� ũ�� ���ĵǾ� ���� ���� ���̱� ������ ��ȯ
			if (nextNode != nullptr && current->data > nextNode->data)
			{
				// �� ����� �����Ͱ��� ��ȯ
				int temp = current->data;
				current->data = nextNode->data;
				nextNode->data = temp;
			}

			// ���� �񱳸� �ϱ����� current ��ĭ ������ �̵�
			current = nextNode;

			// �̰� �ȳ־��ָ� Visual Studio�� current�� nullptr�� ���� �ִٴ� ��� ������ �����
			// �����δ� count-1-i��ŭ �ݺ��ϹǷ� ������ �ݺ��� ���� ���ĸ� �����ϰ�� nextNode�� nullptr�� �� ���� ����
			// ������ Visual Studio�� nullptr�� ���ɼ��� ���� ��� ������ ���
			if (current != nullptr)
			{
				// ���� �񱳸� �ϱ����� nextNode ��ĭ ������ �̵�
				nextNode = current->next;
			}
		}
	}
}