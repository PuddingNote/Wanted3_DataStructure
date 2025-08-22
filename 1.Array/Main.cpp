#include <iostream>

// 배열 클래스.
template<typename T, int size>
class Array
{
public:
    Array()
    {
        // 메모리 0으로 초기화.
        memset(data, 0, sizeof(T) * size);
    }

    int GetSize() const { return size; }

    // 연산자 오버로딩.
    T& operator[](int index)
    {
        if (index < 0 || index > size - 1)
        {
            // Silent is violent
            return 0;
        }
        return data[index];
    }

private:
    T data[size];
};

int main()
{
    const int count = 20;

	Array<int, count> array;
    for (int i = 0; i < array.GetSize(); ++i)
    {
        array[i] = i + 1;
    }

	std::cin.get();
}