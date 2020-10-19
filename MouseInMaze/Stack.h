#pragma once

class Stack
{
private:
	static const int mazeSize = 3000;
	int spaces[mazeSize];
	int head;
public:
	Stack();

	//checks if stack is full
	bool isFull();

	//checks if stack is empty
	bool isEmpty();

	//pushes values into stack
	void Push(int x, int y);

	//pops values out of stack
	int Pop();
};

