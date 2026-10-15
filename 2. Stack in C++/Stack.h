#ifndef STACK_H
#define STACK_H

class Stack {
  public:
	static const int INITIAL_STACK_SIZE = 16;

	Stack();
	~Stack();

	void push(int element);
	int pop();
	bool isEmpty() const;
	void show() const;

	int getSize() const;
	int getMaxSize() const;

  private:
	int* values;
	int size;
	int maxSize;
};

#endif
