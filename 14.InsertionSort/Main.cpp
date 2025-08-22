#include <iostream>

// 배열 길이 구하는 함수.
#define ArraySize(array) sizeof(array) / sizeof(array[0])

// 두 요소를 교환하는 함수.
template<typename T>
void Swap(T& a, T& b)
{
	T temp = a;
	a = b;
	b = temp;
}

// 삽입 정렬.
void InsertionSort(int* array, int length)
{
	// 예외 처리.
	if (length <= 1)
	{
		return;
	}

	// [8][5][6][2][4]
	// 1: key:[5] [8]  [6][2][4]
	// [5][8][6][2][4]
	// 2: key:[6] [5][8] [2][4]
	// [5][6][8][2][4]
	// 3: key:[2] [5][6][8] [4]
	// [2][5][6][8][4]
	// 4: key:[4] [2][5][6][8]   
	// [2][4][5][6][8]

	// 정렬.
	for (int ix = 1; ix < length; ++ix)
	{
		// 키 추출.
		int keyValue = array[ix];
		int jx = ix - 1;

		// 들어갈 자리 찾기.
		while (jx >= 0 && array[jx] > keyValue)
		{
			// 값 밀기.
			array[jx + 1] = array[jx];
			--jx;
		}

		// 키 삽입.
		array[jx + 1] = keyValue;
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

int main()
{
	// 자료 집합.
	int array[] = { 5, 2, 8, 4, 1, 7, 3, 6, 9, 10, 15, 13, 14, 12, 17, 16 };

	// 배열 길이.
	int length = ArraySize(array);

	std::cout << "정렬 전 배열: ";
	PrintArray(array, length);

	// 정렬.
	InsertionSort(array, length);

	std::cout << "정렬 후 배열: ";
	PrintArray(array, length);

	std::cin.get();
}