#include "Stack.h"
#include <iostream>

Stack::Stack() : values(nullptr), size(0), maxSize(INITIAL_STACK_SIZE)
{
	values = new int[maxSize]();
}

Stack::~Stack()
{
	delete[] values;
}

void Stack::push(int element)
{
	if (size == maxSize) {
		int* tmp = new int[maxSize * 2]();
		for (int i = 0; i < size; i++) {
			tmp[i] = values[i];
		}
		delete[] values;
		values = tmp;
		maxSize *= 2;
	}
	values[size] = element;
	size++;
	std::cout << "push(): " << element << std::endl;
}

int Stack::pop()
{
	if (isEmpty()) {
		std::cout << "pop(): empty" << std::endl;
		return 0;
	}
	int top = values[size - 1];
	values[size - 1] = 0;
	size--;
	std::cout << "pop(): " << top << std::endl;
	return top;
}

bool Stack::isEmpty() const
{
	return size == 0;
}

void Stack::show() const
{
	std::cout << "[ ";
	if (isEmpty()) {
		std::cout << "empty ]" << std::endl;
		return;
	}
	for (int i = size - 1; i >= 0; i--) {
		std::cout << values[i] << " ";
	}
	std::cout << "]" << std::endl;
	std::cout << "Size: " << size << std::endl;
	std::cout << "Max size: " << maxSize << std::endl;
}

int Stack::getSize() const
{
	return size;
}

int Stack::getMaxSize() const
{
	return maxSize;
}
