#pragma once

#include <iostream>
#include <Windows.h>

// 최대 저장 수
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
                "스택이 가득 차있어 추가가 불가능합니다",
                "Stack Push Error",
                MB_OK);

            //std::cout << "스택이 가득 차있어 추가가 불가능합니다\n";
            return false;
        }

        // 전달된 경험치를 데이터에 저장
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
                "스택이 비어 있어 추출이 불가능합니다",
                "Stack Pop Error",
                MB_OK);

            //std::cout << "스택이 비어 있어 추출이 불가능합니다\n";
            return 0.0f;
        }

        // 데이터 개수를 하나 감소시킨뒤 값 반환
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
    // 데이터 저장 공간
    T data[stackCount] = { };

    // 스택에 저장된 자료 수 (count를 head(top)으로 사용)
    int count = 0;
};