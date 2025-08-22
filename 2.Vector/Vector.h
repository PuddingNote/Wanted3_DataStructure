#pragma once

#include <iostream>

// 동적으로(실행중에) 크기가 변하는 배열
// 템플릿은 같은 파일에 구현까지 해야함
template<typename T>
class Vector
{
public:
	Vector() : size(0), capacity(2)
	{
		data = new T[capacity];
	}
	// RAII
	~Vector()
	{
		if (data)
		{
			delete[] data;
		}
	}

	void PushBack(const T& value)
	{
		if (size == capacity)
		{
			ReAllocate(capacity * 2);
		}

		// 저장된 마지막 요소 다음 위치에 새로운 값 저장
		data[size] = value;
		
		// 저장된 요소의 크기 증가 처리
		++size;
	}

	// R-Value Reference
	void PushBack(T&& value)
	{
		if (size == capacity)
		{
			ReAllocate(capacity * 2);
		}

		// 핵심! Move Semantic
		data[size] = std::move(value);
		++size;
	}

	// 접근 및 설정을 위한 인덱스 연산자 오버로딩.
	T& operator[](int index)
	{
		// 예외 처리(Out of Index/Range).
		if (index < 0 || index >= size)
		{
			// 디버그 모드에서 동작하며, 중단점이 설정됨.
			__debugbreak();
		}

		return data[index];
	}

	// 접근 및 설정을 위한 인덱스 연산자 오버로딩.
	const T& operator[](int index) const
	{
		if (index < 0 || index >= size)
		{
			__debugbreak();
		}

		return data[index];
	}

	// 접근 함수/설정 함수
	T& At(int index)
	{
		if (index < 0 || index >= size)
		{
			__debugbreak();
		}

		return data[index];
	}

	void Set(int index, const T& value)
	{
		if (index < 0 || index >= size)
		{
			__debugbreak();
		}

		data[index] = value;
	}

	T* begin()
	{
		return data;
	}

	T* end()
	{
		return data + size;
	}

private:
	void ReAllocate(int newCapacity)
	{
		// 1. 새로운 공간 할당 (크기 확장해서)
		//int newCapacity = capacity * 2;
		T* newBlock = new T[newCapacity];
		memset(newBlock, 0, sizeof(T) * newCapacity);

		// 2. 기존 값 복사/이동
		memcpy(newBlock, data, sizeof(T) * capacity);
		/*for (int i = 0; i < capacity; ++i)
		{
		newBlock[i] = data[i];
		}*/

		// 3. 다쓴 메모리 공간 해제 및 업데이트
		delete[] data;
		data = newBlock;
		capacity = newCapacity;
	}

	T* Data() const { return data; }
	int Size() const { return size; }
	int Capacity() const { return capacity; }

private:
	// 자료 컨테이너
	T* data = nullptr;

	// 배열에 실제로 저장된 요소의 수 / 미리 확보해둔 저장 공간의 크기
	int size = 0;
	int capacity = 0;

};