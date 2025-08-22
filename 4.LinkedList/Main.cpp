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

	// 데이터 추가 루프
	while (true)
	{
		std::cout << "추가할 데이터를 입력해주세요(종료는 q)\n";
		std::cin >> input;

		if (strcmp(input, "q") == 0 || strcmp(input, "Q") == 0)
		{
			break;
		}

		// 데이터 삽입
		if (!atoi(input))
		{
			std::cout << "숫자만 입력 가능합니다\n";
			continue;
		}
		list.Insert(atoi(input));

		list.Print();
	}

	// 데이터 삭제 루프
	while (true)
	{
		std::cout << "삭제할 데이터를 입력해주세요(종료는 q)\n";
		std::cin >> input;

		if (strcmp(input, "q") == 0 || strcmp(input, "Q"))
		{
			break;
		}

		// 데이터 삽입
		if (!atoi(input))
		{
			std::cout << "숫자만 입력 가능합니다\n";
			continue;
		}
		list.Insert(atoi(input));

		list.Print();
	}

 	list.Sort();
	list.Print();
	
	std::cin.get();
 }