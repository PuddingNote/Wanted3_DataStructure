#include <iostream>

void Swap(int& a, int& b)
{
	int temp = a;
	a = b;
	b = temp;
}

void PrintArray(int* array, int length)
{
	for (int i = 0; i < length; ++i)
	{
		std::cout << array[i];

		if (i < length - 1)
		{
			std::cout << ", ";
		}
	}
	std::cout << '\n';
}

void BubbleSort(int* array, int length)
{
	for (int i = 0; i < length - 1; ++i)
	{
		for (int j = 0; j < length - 1 - i; ++j)
		{
			if (array[j] > array[j + 1])
			{
				Swap(array[j], array[j + 1]);
			}
		}
	}
}

int main()
{
	int array[] = { 5,2,8,4,1 };
	int length = sizeof(array) / sizeof(array[0]);

	std::cout << "���� ��: ";
	PrintArray(array, length);

	BubbleSort(array, length);
	
	std::cout << "���� ��: ";
	PrintArray(array, length);

	std::cin.get();
}