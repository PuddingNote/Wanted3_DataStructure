#include "MergeSort.h"
#include <iostream>

void Merge(
	int* array,
	int* leftArray, int leftArrayLength,
	int* rightArray, int rightArrayLength)
{
	// 인덱스 초기화.
	int leftIndex = 0;
	int rightIndex = 0;
	int mergedIndex = 0;

	// 왼쪽/오른쪽 배열의 요소를 비교해 더 작은 배열의 요소를 array에 복사.
	while (leftIndex < leftArrayLength && rightIndex < rightArrayLength)
	{
		// 크기 비교.
		// 왼쪽이 선택되는 경우 (같은 경우를 왼쪽에 포함).
		if (leftArray[leftIndex] <= rightArray[rightIndex])
		{
			array[mergedIndex] = leftArray[leftIndex];
			++leftIndex;
		}

		// 오른쪽이 선택되는 경우.
		else
		{
			array[mergedIndex] = rightArray[rightIndex];
			++rightIndex;
		}

		// 병합 배열의 인덱스 증가 처리.
		++mergedIndex;
	}

	// 남아 있는 요소 병합.
	while (leftIndex < leftArrayLength)
	{
		array[mergedIndex] = leftArray[leftIndex];
		++leftIndex;
		++mergedIndex;
	}

	while (rightIndex < rightArrayLength)
	{
		array[mergedIndex] = rightArray[rightIndex];
		++rightIndex;
		++mergedIndex;
	}
}

void MergeSort(int* array, int length)
{
	// 예외 처리(재귀 함수 종료 조건).
	if (length <= 1)
	{
		return;
	}

	// 배열 분할.
	// 3 / 2= 1.5->1.
	// mid = 1.
	// lefArray[1] / rightArray[3 - 1 = 2]
	int mid = length / 2;

	// 분할될 두 배열의 공간 확보.
	// 초기화하면 더 좋음.
	int* leftArray = new int[mid];
	memset(leftArray, 0, sizeof(int) * mid);

	int* rightArray = new int[length - mid];
	memset(rightArray, 0, sizeof(int) * (length - mid));

	// 값 복사.
	//for (int ix = 0; ix < mid; ++ix)
	//{
	//	leftArray[ix] = array[ix];
	//}

	// 왼쪽 배열에 값 복사, 0부터 mid 인덱스까지 복사.
	memcpy(leftArray, array, sizeof(int) * mid);

	// 오른쪽 배열에 값 복사, mid부터 length - mid 인덱스까지 복사.
	memcpy(rightArray, array + mid, sizeof(int) * (length - mid));

	// 왼쪽 배열에 대해 병합 정렬 (재귀).
	MergeSort(leftArray, mid);

	// 오른쪽 배열에 대해 병합 정렬 (재귀).
	MergeSort(rightArray, length - mid);

	// 병합.
	Merge(array, leftArray, mid, rightArray, length - mid);

	// 메모리 정리.
	delete[] leftArray;
	delete[] rightArray;
}