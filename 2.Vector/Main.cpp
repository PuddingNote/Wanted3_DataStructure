#include <iostream>
#include "Vector.h"

int main()
{
	const int count = 30;
	Vector<int> vector;
	for (int i = 0; i < count; ++i)
	{
		vector.PushBack(i + 1);
	}

	// Begin�����ϸ� VS�� �ν��� ����
	for (auto& item : vector)
	{
		std::cout << item << " ";
	}

	std::cin.get();
}