CC = g++
CFLAGS = -g -Wall -pedantic
TARGET = myprogram.out
OBJS = TestStack.o Stack.o

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.cpp Stack.h
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	clear && valgrind ./$(TARGET)

clean:
	rm -f $(TARGET) $(OBJS)

.PHONY: run clean
