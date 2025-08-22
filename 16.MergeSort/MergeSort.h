#pragma once

/// <summary>
/// 분할된 배열을 다시 합치는 병합 함수. 
/// </summary>
/// <param name="array">합쳐질 배열</param>
/// <param name="leftArray">분할된 왼쪽 배열</param>
/// <param name="leftArrayLength">왼쪽 배열 크기</param>
/// <param name="rightArray">분할된 오른쪽 배열</param>
/// <param name="rightArrayLength">오른쪽 배열 크기</param>
void Merge(
	int* array,
	int* leftArray, int leftArrayLength,
	int* rightArray, int rightArrayLength);

/// <summary>
/// 병합 정렬 함수.
/// </summary>
/// <param name="array">정렬할 대상 배열</param>
/// <param name="length">배열 크기</param>
void MergeSort(int* array, int length);