CC = g++
CFLAGS = -g -Wall -pedantic
TARGET = myprogram.out
OBJS = TestPolyWithFunctionTemplate.o Poly.o

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.cpp Poly.h
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	clear && valgrind --leak-check=full ./$(TARGET)

clean:
	rm -f $(TARGET) *.o vgcore.*

.PHONY: run clean
