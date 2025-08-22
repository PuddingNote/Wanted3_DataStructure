#include <iostream>
#include "Queue.h"

int main()
{
	// 큐 객체 생성.
	Queue queue;

	// 데이터 추가.
	for (int ix = 0; ix < 10; ++ix)
	{
		queue.Enqueue(ix + 1);
	}

	// 큐 출력.
	queue.Print();

	int value = 0;
	queue.Dequeue(value);
	queue.Dequeue(value);
	queue.Dequeue(value);

	queue.Print();

	std::cin.get();
}