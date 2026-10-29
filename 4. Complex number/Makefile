CC = g++
CFLAGS = -g -Wall -pedantic
TARGET = myprogram.out
OBJS = TestComplex.o Complex.o

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.cpp Complex.h
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	clear && valgrind --leak-check=full ./$(TARGET)

clean:
	rm -f $(TARGET) $(OBJS)

.PHONY: run clean
