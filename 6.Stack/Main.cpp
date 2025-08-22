#include <iostream>
#include "Stack.h"

int main()
{
	Stack<float> stack;

	stack.Push(15.0f);
	stack.Push(30.0f);

	while (!stack.IsEmpty())
	{
		std::cout << "°æÇèÄ¡: " << stack.Pop() << '\n';
	}

	//float exp = stack.Pop();
	//exp = stack.Pop();

	std::cin.get();
}