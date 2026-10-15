#include "Stack.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void testPushPopShowOnSingleStack()
{
	printf("=== testPushPopShowOnSingleStack ===\n");
	Stack s;
	init(&s);
	show(&s);
	pop(&s);
	show(&s);
	push(&s, 5);
	push(&s, 17);
	push(&s, -2);
	show(&s);
	pop(&s);
	show(&s);
	for (int i = 0; i < 14; i++) {
		push(&s, i);
	}
	show(&s);
	push(&s, 99);
	show(&s);

	destroy(&s);
}

void testMultipleStacksAreIndependent()
{
	printf("=== testMultipleStacksAreIndependent ===\n");
	Stack a;
	Stack b;
	Stack c;
	init(&a);
	init(&b);
	init(&c);

	push(&a, 1);
	push(&a, 2);
	push(&b, 100);
	assert(a.size == 2);
	assert(b.size == 1);
	assert(isEmpty(&c));

	assert(pop(&b) == 100);
	assert(isEmpty(&b));
	assert(!isEmpty(&a));

	for (int i = 0; i < 20; i++) {
		push(&b, i);
	}
	assert(b.max_size == 32);
	assert(a.max_size == INITIAL_STACK_SIZE);
	assert(c.max_size == INITIAL_STACK_SIZE);

	push(&c, -7);
	push(&c, 42);
	assert(c.size == 2);

	destroy(&b);
	assert(pop(&a) == 2);
	assert(pop(&c) == 42);
	assert(pop(&c) == -7);
	assert(isEmpty(&c));
	assert(a.size == 1);
	show(&a);
	show(&c);

	destroy(&a);
	destroy(&c);
}

void testPopReturnsValuesInReverseOrderAfterResize()
{
	printf("=== testPopReturnsValuesInReverseOrderAfterResize ===\n");
	Stack s;
	init(&s);

	int count = 40;
	for (int i = 0; i < count; i++) {
		push(&s, i * 10);
	}
	assert(s.size == count);
	assert(s.max_size == 64);

	for (int i = count - 1; i >= 0; i--) {
		assert(pop(&s) == i * 10);
	}
	assert(isEmpty(&s));
	assert(pop(&s) == 0);
	assert(s.size == 0);

	destroy(&s);
}

int main(int argc, char** argv)
{
	testPushPopShowOnSingleStack();
	testMultipleStacksAreIndependent();
	testPopReturnsValuesInReverseOrderAfterResize();
	printf("All tests passed\n");
	return 0;
}
