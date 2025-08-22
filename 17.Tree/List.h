#pragma once
#pragma once

#include <iostream>

template<typename T>
class List
{
public:
	List()
		: index(0), size(0), capacity(4)
	{
		data = new T[capacity];
	}

	~List()
	{
		delete[] data;
	}

	void PushBack(const T& item)
	{
		if (size == capacity)
		{
			Resize(capacity * 2);
		}

		data[size] = item;
		++size;
	}

	bool Remove(const T& item)
	{
		if (size == 0)
		{
			return false;
		}

		int targetIndex = -1;
		for (int ix = 0; ix < size; ++ix)
		{
			if (data[ix] == item)
			{
				targetIndex = ix;
				break;
			}
		}

		if (targetIndex < 0)
		{
			return false;
		}

		RemoveAt(targetIndex);
		return true;
	}

	void RemoveAt(int index)
	{
		if (size == 0 || index < 0 || index >= size)
		{
			return;
		}

		if (index < size)
		{
			int listIndex = 0;
			for (int ix = 0; ix < size; ++ix)
			{
				if (ix == index)
				{
					continue;
				}

				data[listIndex] = data[ix];
				++listIndex;
			}
		}

		--size;
	}

private:
	void Resize(int newCapacity)
	{
		T* newData = new T[newCapacity];

		if (newCapacity < size)
		{
			size = newCapacity;
		}

		memcpy(newData, data, sizeof(T) * size);
		delete[] data;
		data = newData;
		capacity = newCapacity;
	}

public:

	// Getter.
	int Size() const { return size; }
	int Capacity() const { return capacity; }
	T At(int index) { return data[index]; }
	T operator[](int index) { return data[index]; }

private:
	T* data = nullptr;
	int index = 0;
	int size = 0;
	int capacity = 4;
};