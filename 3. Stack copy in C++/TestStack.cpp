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

void fill(Stack& s, int count, int base)
{
	for (int i = 0; i < count; i++) {
		s.push(base + i);
	}
}

void assertContains(Stack& s, int count, int base)
{
	assert(s.getSize() == count);
	for (int i = count - 1; i >= 0; i--) {
		assert(s.pop() == base + i);
	}
	assert(s.isEmpty());
}

void testCopyConstructorAllocatesOnlyUsedSize()
{
	std::cout << "=== testCopyConstructorAllocatesOnlyUsedSize ==="
			  << std::endl;
	Stack s1;
	fill(s1, 40, 0);
	for (int i = 0; i < 37; i++) {
		s1.pop();
	}
	assert(s1.getMaxSize() == 64);

	Stack s2(s1);
	assert(s2.getSize() == 3);
	assert(s2.getMaxSize() == 3);
	assertContains(s2, 3, 0);
	assertContains(s1, 3, 0);
}

void testCopyConstructorIsIndependent()
{
	std::cout << "=== testCopyConstructorIsIndependent ===" << std::endl;
	Stack s1;
	fill(s1, 5, 1);
	Stack s2 = s1;

	s2.push(100);
	assert(s2.getMaxSize() == 10);
	s1.pop();
	assert(s1.getSize() == 4);
	assert(s2.getSize() == 6);
	assert(s2.pop() == 100);
	assertContains(s2, 5, 1);
	assertContains(s1, 4, 1);
}

void testCopyConstructorOfEmptyStack()
{
	std::cout << "=== testCopyConstructorOfEmptyStack ===" << std::endl;
	Stack s1;
	Stack s2(s1);
	assert(s2.isEmpty());
	assert(s2.getMaxSize() == 0);
	assert(s2.pop() == 0);

	fill(s2, 20, 7);
	assert(s2.getMaxSize() == 2 * Stack::INITIAL_STACK_SIZE);
	assertContains(s2, 20, 7);
	assert(s1.isEmpty());
}

void testCopyConstructorOfCopy()
{
	std::cout << "=== testCopyConstructorOfCopy ===" << std::endl;
	Stack s1;
	Stack s2(s1);
	Stack s3(s2);
	assert(s3.isEmpty());
	assert(s3.getMaxSize() == 0);

	fill(s1, 4, 0);
	Stack s4(s1);
	Stack s5(s4);
	assert(s5.getMaxSize() == 4);
	assertContains(s5, 4, 0);
}

void testAssignLargerToSmaller()
{
	std::cout << "=== testAssignLargerToSmaller ===" << std::endl;
	Stack small;
	fill(small, 3, 0);
	Stack large;
	fill(large, 40, 100);

	small = large;
	assert(small.getSize() == 40);
	assert(small.getMaxSize() == 40);
	assertContains(small, 40, 100);
	assertContains(large, 40, 100);
}

void testAssignSmallerToLarger()
{
	std::cout << "=== testAssignSmallerToLarger ===" << std::endl;
	Stack small;
	fill(small, 3, 0);
	Stack large;
	fill(large, 40, 100);

	large = small;
	assert(large.getSize() == 3);
	assert(large.getMaxSize() == 64);
	assertContains(large, 3, 0);
	assertContains(small, 3, 0);
}

void testAssignEqualSize()
{
	std::cout << "=== testAssignEqualSize ===" << std::endl;
	Stack a;
	fill(a, 5, 0);
	Stack b;
	fill(b, 5, 50);

	a = b;
	assert(a.getSize() == 5);
	assert(a.getMaxSize() == Stack::INITIAL_STACK_SIZE);
	assertContains(a, 5, 50);
	assertContains(b, 5, 50);
}

void testAssignEqualCapacityBoundary()
{
	std::cout << "=== testAssignEqualCapacityBoundary ===" << std::endl;
	Stack a;
	fill(a, 3, 0);
	Stack copy(a);
	assert(copy.getMaxSize() == 3);

	Stack b;
	fill(b, 3, 30);
	copy = b;
	assert(copy.getMaxSize() == 3);
	assertContains(copy, 3, 30);

	fill(b, 1, 33);
	copy = b;
	assert(copy.getMaxSize() == 4);
	assertContains(copy, 4, 30);
}

void testAssignEmptySource()
{
	std::cout << "=== testAssignEmptySource ===" << std::endl;
	Stack a;
	fill(a, 20, 0);
	Stack empty;

	a = empty;
	assert(a.isEmpty());
	assert(a.getMaxSize() == 32);
	assert(a.pop() == 0);

	fill(a, 2, 9);
	assertContains(a, 2, 9);
}

void testAssignToEmptyDestination()
{
	std::cout << "=== testAssignToEmptyDestination ===" << std::endl;
	Stack source;
	fill(source, 10, 0);

	Stack empty;
	empty = source;
	assert(empty.getMaxSize() == Stack::INITIAL_STACK_SIZE);
	assertContains(empty, 10, 0);

	Stack zeroCapacity;
	Stack noBuffer(zeroCapacity);
	noBuffer = source;
	assert(noBuffer.getMaxSize() == 10);
	assertContains(noBuffer, 10, 0);
}

void testAssignBothEmpty()
{
	std::cout << "=== testAssignBothEmpty ===" << std::endl;
	Stack a;
	Stack b;
	a = b;
	assert(a.isEmpty());
	assert(a.getMaxSize() == Stack::INITIAL_STACK_SIZE);

	Stack zeroCapacity(b);
	zeroCapacity = b;
	assert(zeroCapacity.isEmpty());
	assert(zeroCapacity.getMaxSize() == 0);
}

void testSelfAssignment()
{
	std::cout << "=== testSelfAssignment ===" << std::endl;
	Stack s;
	fill(s, 20, 0);
	Stack& alias = s;

	s = alias;
	assert(s.getSize() == 20);
	assert(s.getMaxSize() == 32);
	assertContains(s, 20, 0);

	Stack empty;
	Stack& emptyAlias = empty;
	empty = emptyAlias;
	assert(empty.isEmpty());
}

void testChainedAssignment()
{
	std::cout << "=== testChainedAssignment ===" << std::endl;
	Stack a;
	Stack b;
	Stack c;
	fill(c, 6, 60);

	a = b = c;
	assertContains(a, 6, 60);
	assertContains(b, 6, 60);
	assertContains(c, 6, 60);
}

void testAssignmentIsIndependent()
{
	std::cout << "=== testAssignmentIsIndependent ===" << std::endl;
	Stack a;
	fill(a, 4, 0);
	Stack b;
	b = a;

	a.push(-1);
	b.pop();
	assert(a.getSize() == 5);
	assert(b.getSize() == 3);
	assert(a.pop() == -1);
	assertContains(a, 4, 0);
	assertContains(b, 3, 0);
}

void runSomeFunction(Stack s)
{
	std::cout << "runSomeFunction(): size " << s.getSize() << std::endl;
}

void runAnotherFunction(Stack& s)
{
	std::cout << "runAnotherFunction(): size " << s.getSize() << std::endl;
}

void demoCopyCalls()
{
	std::cout << "=== demoCopyCalls ===" << std::endl;
	Stack s1;
	s1.push(1);
	s1.push(2);
	s1.push(3);

	Stack s2(s1);

	Stack s3 = s1;

	Stack s4;
	s4.push(10);
	s4 = s1;

	runSomeFunction(s1);
	runAnotherFunction(s1);
}

int main(int argc, char** argv)
{
	testPushPopShowOnSingleStack();
	testMultipleStacksAreIndependent();
	testPopReturnsValuesInReverseOrderAfterResize();
	testCopyConstructorAllocatesOnlyUsedSize();
	testCopyConstructorIsIndependent();
	testCopyConstructorOfEmptyStack();
	testCopyConstructorOfCopy();
	testAssignLargerToSmaller();
	testAssignSmallerToLarger();
	testAssignEqualSize();
	testAssignEqualCapacityBoundary();
	testAssignEmptySource();
	testAssignToEmptyDestination();
	testAssignBothEmpty();
	testSelfAssignment();
	testChainedAssignment();
	testAssignmentIsIndependent();
	demoCopyCalls();
	std::cout << "All tests passed" << std::endl;
	return 0;
}
