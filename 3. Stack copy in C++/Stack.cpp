#include "Stack.h"
#include <iostream>

Stack::Stack() : values(nullptr), size(0), maxSize(INITIAL_STACK_SIZE)
{
	values = new int[maxSize]();
}

Stack::Stack(const Stack& other)
	: values(nullptr), size(other.size), maxSize(other.size)
{
	if (size > 0) {
		values = new int[size];
		for (int i = 0; i < size; i++) {
			values[i] = other.values[i];
		}
	}
}

Stack::~Stack()
{
	delete[] values;
}

Stack& Stack::operator=(const Stack& other)
{
	if (this == &other) {
		return *this;
	}
	if (maxSize < other.size) {
		int* tmp = new int[other.size];
		delete[] values;
		values = tmp;
		maxSize = other.size;
	}
	for (int i = 0; i < other.size; i++) {
		values[i] = other.values[i];
	}
	for (int i = other.size; i < size; i++) {
		values[i] = 0;
	}
	size = other.size;
	return *this;
}

void Stack::push(int element)
{
	if (size == maxSize) {
		int newMaxSize = maxSize == 0 ? INITIAL_STACK_SIZE : maxSize * 2;
		int* tmp = new int[newMaxSize]();
		for (int i = 0; i < size; i++) {
			tmp[i] = values[i];
		}
		delete[] values;
		values = tmp;
		maxSize = newMaxSize;
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
