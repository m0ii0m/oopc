#include "Stack.h"
#include <stdio.h>
#include <stdlib.h>

void init(Stack* s)
{
	s->max_size = 16;
	s->values = (int*)malloc(sizeof(int) * s->max_size);
	if (s->values == NULL)
		return;
	for (int i = 0; i < s->max_size; i++) {
		s->values[i] = 0;
	}
	s->size = 0;
}

void destroy(Stack* s)
{
	free(s->values);
	s->values = NULL;
}

void push(Stack* s, int element)
{
	if (s->size == s->max_size) {
		int* tmp;
		tmp = (int*)realloc(s->values, sizeof(int) * (s->max_size) * 2);
		if (tmp == NULL)
			return;
		s->values = tmp;
		(s->max_size) *= 2;
	}
	s->values[s->size] = element;
	(s->size)++;
	printf("push(): %d\n", element);
}

int pop(Stack* s)
{
	if (isEmpty(s)) {
		printf("pop(): empty\n");
		return 0;
	}
	int top = s->values[s->size - 1];
	s->values[s->size - 1] = 0;
	(s->size)--;
	printf("pop(): %d\n", top);
	return top;
}

bool isEmpty(const Stack* s)
{
	return s->size == 0;
}

void show(const Stack* s)
{
	printf("[ ");
	if (isEmpty(s)) {
		printf("empty ");
		printf("]\n");
		return;
	}
	for (int i = s->size - 1; i >= 0; i--) {
		printf("%d ", s->values[i]);
	}
	printf("]\n");
	printf("Size: %d\n", s->size);
	printf("Max size: %d\n", s->max_size);
}