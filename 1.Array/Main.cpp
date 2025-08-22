#include <iostream>

// �迭 Ŭ����.
template<typename T, int size>
class Array
{
public:
    Array()
    {
        // �޸� 0���� �ʱ�ȭ.
        memset(data, 0, sizeof(T) * size);
    }

    int GetSize() const { return size; }

    // ������ �����ε�.
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