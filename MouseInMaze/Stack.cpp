#include "Stack.h"

Stack::Stack()
{
	for (int i = 0; i < mazeSize; i++)
	{
		spaces[i] = 0;
	}
	head = -1;
}
bool Stack::isFull()
{
	return head == mazeSize - 1;
}
void Stack::Push(int x, int y)
{
	if (!isFull())
	{
		head++;
		spaces[head] = y * 100 + x;
	}

}
int Stack::Pop()
{
	if (!isEmpty())
	{
		int num;
		num = spaces[head];
		head--;

		return num;
	}
	return -1;
}

bool Stack::isEmpty()
{
	return (head == -1);
}

