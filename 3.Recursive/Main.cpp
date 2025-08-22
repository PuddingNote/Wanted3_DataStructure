#include <iostream>

// 이진 탐색(검색) Binary Search
int BinarySearch(int array[], int target, int low, int high)
{
    // [1,2,3,4,5,6,7,8,9]
    // mid = 5 (중간값)
    // [1,2,3,4] / [6,7,8,9]
    // target > mid ? target < mid ?
    // target == array[mid]

    // 종료 조건 (예외/만족)

    // 검색 실패
    if (low > high)
    {
        return -1;
    }

    // 중간 값
    int mid = (low + high) / 2;

    // 탐색 성공 여부 확인
    if (array[mid] == target)
    {
        return mid;
    }

    // 오른쪽 반 먼저 탐색
    else if (array[mid] < target)
    {
        return BinarySearch(array, target, mid + 1, high);
    }

    // 왼쪽 반 탐색
    return BinarySearch(array, target, low, mid - 1);
}

int main()
{
    
}