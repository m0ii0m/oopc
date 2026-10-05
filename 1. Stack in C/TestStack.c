#include "Stack.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
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
	return 0;
}