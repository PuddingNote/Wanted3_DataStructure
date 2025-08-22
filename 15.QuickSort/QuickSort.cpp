#include "QuickSort.h"

int Partition(int* array, int left, int right)
{
    // 피벗을 기준으로 배열을 분할.
    int pivot = array[left];

    // 왼쪽에서 오른쪽으로 이동하면서
    // 피벗보다 큰 값을 검색.
    int low = left + 1;

    // 오른쪽에서 왼쪽으로 이동하면서
    // 피벗보다 작은 값을 검색.
    int high = right;

    // low와 high가 교차할 때까지 반복.
    while (low <= high)
    {
        // 왼쪽에서 오른쪽으로 검색.
        while (array[low] <= pivot)
        {
            if (low < right)
            {
                ++low;
            }
            else
            {
                break;
            }
        }

        // 오른쪽에서 왼쪽으로 검색.
        while (array[high] >= pivot)
        {
            if (high > left)
            {
                --high;
            }
            else
            {
                break;
            }
        }

        // 종료 조건 확인.
        // low와 high가 서로 교차했으면 루프 종료.
        if (low > high)
        {
            break;
        }

        // low와 high를 교환.
        Swap<int>(array[low], array[high]);
    }

    // 피벗 값과 왼쪽 데이터 집합의 마지막 요소를 교환.
    Swap<int>(array[left], array[high]);

    // 왼쪽 집합의 마지막 인덱스를 반환.
    return high;
}

void QuickSort(int* array, int left, int right)
{
    // 예외 처리.
    // 왼쪽 인덱스와 오른쪽 인덱스가 겹치거나 교차했는지 확인.
    if (left >= right)
    {
        return;
    }

    // 피벗을 기준으로 배열 분할.
    int pivot = Partition(array, left, right);

    // 왼쪽 배열 정렬 (재귀).
    QuickSort(array, left, pivot - 1);

    // 오른쪽 배열 정렬 (재귀).
    QuickSort(array, pivot + 1, right);
}