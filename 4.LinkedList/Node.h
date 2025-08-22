#pragma once

#include <iostream>

class Node
{
	// ����� ���ρ����ϱ� ���� ������ �����ε�
	friend std::ostream& operator<<(std::ostream& os, const Node& node);

	// LinkedList������ NodeŬ������ ���� �� ������ �� �ֵ��� ����
	friend class LinkedList;

private:
	Node();
	Node(int data);

private:
	int data = 0;
	Node* next = nullptr;
};