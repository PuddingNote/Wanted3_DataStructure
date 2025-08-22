#pragma once

#include <iostream>

const int maxQueueCount = 100;
class Queue
{
public:
	Queue()
	{
		memset(data, 0, sizeof(int) * maxQueueCount);
	}

	// 비었는지 확인.
	bool IsEmpty() const
	{
		// 앞과 뒤를 가리키는 위치 값이 같으면 빈 상태.
		return front == rear;
	}

	// 가득찼는지 확인.
	bool IsFull() const
	{
		// rear의 다음 위치(1칸 차이)가 front와 같으면,
		// 가득 찬 상태로 봄.
		return (rear + 1) % maxQueueCount == front;
	}

	// 큐에 데이터 추가.
	bool Enqueue(int newData)
	{
		// 가득찼는지 확인.
		if (IsFull())
		{
			std::cout << "Error: 큐가 가득차 있습니다.\n";
			return false;
		}

		// 뒤(rear) 다음 위치에 새로운 데이터 추가.
		rear = (rear + 1) % maxQueueCount;
		data[rear] = newData;
		return true;
	}

	// 큐에서 데이터 추출.
	bool Dequeue(int& outValue)
	{
		// 실패 확인.
		if (IsEmpty())
		{
			std::cout << "Error: 큐가 비어 있습니다.\n";
			return false;
		}

		// 앞에 있는 데이터 추출.
		front = (front + 1) % maxQueueCount;
		outValue = data[front];

		// 필요에 따라 데이터 정리 가능.
		data[front] = 0;
		return true;
	}

	// 출력.
	void Print()
	{
		std::cout << "큐 내용: ";
		// [0][1][2][3][4]
		// f:0, r:3
		int max = front < rear ? rear : rear + maxQueueCount;
		for (int ix = front + 1; ix <= max; ++ix)
		{
			std::cout << " " << data[ix % maxQueueCount];
		}

		std::cout << "\n";
	}

private:
	int front = 0;
	int rear = 0;
	int data[maxQueueCount] = { };
};