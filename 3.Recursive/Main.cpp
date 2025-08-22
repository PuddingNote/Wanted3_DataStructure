#include <iostream>

// ���� Ž��(�˻�) Binary Search
int BinarySearch(int array[], int target, int low, int high)
{
    // [1,2,3,4,5,6,7,8,9]
    // mid = 5 (�߰���)
    // [1,2,3,4] / [6,7,8,9]
    // target > mid ? target < mid ?
    // target == array[mid]

    // ���� ���� (����/����)

    // �˻� ����
    if (low > high)
    {
        return -1;
    }

    // �߰� ��
    int mid = (low + high) / 2;

    // Ž�� ���� ���� Ȯ��
    if (array[mid] == target)
    {
        return mid;
    }

    // ������ �� ���� Ž��
    else if (array[mid] < target)
    {
        return BinarySearch(array, target, mid + 1, high);
    }

    // ���� �� Ž��
    return BinarySearch(array, target, low, mid - 1);
}

int main()
{
    
}