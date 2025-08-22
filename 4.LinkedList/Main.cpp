#include <iostream>
#include "LinkedList.h"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	LinkedList list;

	char input[50] = {};

	// ������ �߰� ����
	while (true)
	{
		std::cout << "�߰��� �����͸� �Է����ּ���(����� q)\n";
		std::cin >> input;

		if (strcmp(input, "q") == 0 || strcmp(input, "Q") == 0)
		{
			break;
		}

		// ������ ����
		if (!atoi(input))
		{
			std::cout << "���ڸ� �Է� �����մϴ�\n";
			continue;
		}
		list.Insert(atoi(input));

		list.Print();
	}

	// ������ ���� ����
	while (true)
	{
		std::cout << "������ �����͸� �Է����ּ���(����� q)\n";
		std::cin >> input;

		if (strcmp(input, "q") == 0 || strcmp(input, "Q"))
		{
			break;
		}

		// ������ ����
		if (!atoi(input))
		{
			std::cout << "���ڸ� �Է� �����մϴ�\n";
			continue;
		}
		list.Insert(atoi(input));

		list.Print();
	}

 	list.Sort();
	list.Print();
	
	std::cin.get();
 }