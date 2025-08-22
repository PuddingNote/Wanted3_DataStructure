#pragma once

#include <iostream>
#include <Windows.h>

// �ִ� ���� ��
const int stackCount = 100;

template<typename T>
class Stack
{
public:
    Stack() = default;
    ~Stack() = default;

    bool IsEmpty() const
    {
        return count == 0;
    }
    bool IsFull() const
    {
        return count == stackCount;
    }
    bool Push(const T& exp)
    {
        if (IsFull())
        {
            MessageBoxA(
                nullptr,
                "������ ���� ���־� �߰��� �Ұ����մϴ�",
                "Stack Push Error",
                MB_OK);

            //std::cout << "������ ���� ���־� �߰��� �Ұ����մϴ�\n";
            return false;
        }

        // ���޵� ����ġ�� �����Ϳ� ����
        data[count] = exp;
        ++count;

        return true;
    }
    T Pop()
    {
        if (IsEmpty())
        {
            MessageBoxA(
                nullptr,
                "������ ��� �־� ������ �Ұ����մϴ�",
                "Stack Pop Error",
                MB_OK);

            //std::cout << "������ ��� �־� ������ �Ұ����մϴ�\n";
            return 0.0f;
        }

        // ������ ������ �ϳ� ���ҽ�Ų�� �� ��ȯ
        --count;

        return data[count];
    }

    void Clear()
    {
        memset(data, 0, sizeof(T) * stackCount);
        count = 0;
    }
    int GetCount() const
    {
        return count;
    }

private:
    // ������ ���� ����
    T data[stackCount] = { };

    // ���ÿ� ����� �ڷ� �� (count�� head(top)���� ���)
    int count = 0;
};