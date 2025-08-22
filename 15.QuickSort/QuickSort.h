#pragma once

// 두 값을 서로 교환하는 함수.
template<typename T>
void Swap(T& a, T& b)
{
	T temp = a;
	a = b;
	b = temp;
}

// 배열을 분할한 뒤 인덱스를 반환하는 함수.
int Partition(int* array, int left, int right);

// 퀵 정렬 함수.
void QuickSort(int* array, int left, int right);