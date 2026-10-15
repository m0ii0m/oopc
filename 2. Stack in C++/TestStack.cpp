#include "Stack.h"
#include <cassert>
#include <iostream>

void testPushPopShowOnSingleStack()
{
	std::cout << "=== testPushPopShowOnSingleStack ===" << std::endl;
	Stack s;
	s.show();
	s.pop();
	s.show();
	s.push(5);
	s.push(17);
	s.push(-2);
	s.show();
	s.pop();
	s.show();
	for (int i = 0; i < 14; i++) {
		s.push(i);
	}
	s.show();
	s.push(99);
	s.show();
}

void testMultipleStacksAreIndependent()
{
	std::cout << "=== testMultipleStacksAreIndependent ===" << std::endl;
	Stack a;
	Stack* b = new Stack;
	Stack c;

	a.push(1);
	a.push(2);
	b->push(100);
	assert(a.getSize() == 2);
	assert(b->getSize() == 1);
	assert(c.isEmpty());

	assert(b->pop() == 100);
	assert(b->isEmpty());
	assert(!a.isEmpty());

	for (int i = 0; i < 20; i++) {
		b->push(i);
	}
	assert(b->getMaxSize() == 32);
	assert(a.getMaxSize() == Stack::INITIAL_STACK_SIZE);
	assert(c.getMaxSize() == Stack::INITIAL_STACK_SIZE);

	c.push(-7);
	c.push(42);
	assert(c.getSize() == 2);

	delete b;
	assert(a.pop() == 2);
	assert(c.pop() == 42);
	assert(c.pop() == -7);
	assert(c.isEmpty());
	assert(a.getSize() == 1);
	a.show();
	c.show();
}

void testPopReturnsValuesInReverseOrderAfterResize()
{
	std::cout << "=== testPopReturnsValuesInReverseOrderAfterResize ==="
			  << std::endl;
	Stack s;

	int count = 40;
	for (int i = 0; i < count; i++) {
		s.push(i * 10);
	}
	assert(s.getSize() == count);
	assert(s.getMaxSize() == 64);

	for (int i = count - 1; i >= 0; i--) {
		assert(s.pop() == i * 10);
	}
	assert(s.isEmpty());
	assert(s.pop() == 0);
	assert(s.getSize() == 0);
}

int main(int argc, char** argv)
{
	testPushPopShowOnSingleStack();
	testMultipleStacksAreIndependent();
	testPopReturnsValuesInReverseOrderAfterResize();
	std::cout << "All tests passed" << std::endl;
	return 0;
}
