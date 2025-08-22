#include <iostream>

// 배열 원소 개수 구하는 함수.
#define ArraySize(array) sizeof(array) / sizeof(array[0])

// 두 값을 교환하는 함수.
template<typename T>
void Swap(T& a, T& b)
{
	T temp = a;
	a = b;
	b = temp;
}

// 선택 정렬 함수.
void SelectionSort(int* array, int length)
{
	// 예외 처리.
	if (length <= 1)
	{
		return;
	}

	// 외부 루프는 n-1번 반복.
	for (int ix = 0; ix < length - 1; ++ix)
	{
		// 현재 순회에서 가장 왼쪽 값 찾기.
		// 시작.
		int minIndex = ix;

		// 내부 루프는 ix에서 끝까지 반복.
		for (int jx = ix + 1; jx < length; ++jx)
		{
			// minIndex 구하기.
			if (array[jx] < array[minIndex])
			{
				minIndex = jx;
			}
		}

		// 교환.
		if (minIndex != ix)
		{
			Swap(array[ix], array[minIndex]);
		}
	}
}

// 배열 출력 함수.
void PrintArray(int array[], int length)
{
	for (int ix = 0; ix < length; ++ix)
	{
		std::cout << array[ix];

		if (ix < length - 1)
		{
			std::cout << ", ";
		}
	}

	std::cout << "\n";
}

// Entry Point.
int main()
{
	// 자료 집합.
	int array[] = { 0, 21, 22, 25, 5, 2, 3, 8, 9, 4, 11, 1,19, 20, 23, 7, 3, 6, 9, 10, 15, 13, 14, 12, 17, 16 };

	// 배열 길이.
	int length = ArraySize(array);

	// 정렬 전 출력.
	std::cout << "정렬 전 배열: ";
	PrintArray(array, length);

	// 정렬.
	SelectionSort(array, length);

	// 정렬 후 출력.
	std::cout << "정렬 후 배열: ";
	PrintArray(array, length);

	std::cin.get();
}