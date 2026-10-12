CC = gcc
CFLAGS = -Wall -Wextra -g -std=c99
TARGET = memory_leak_example
SOURCE = memory_leak.c
FIX_TARGET = memory_leak_fix_example
FIX_SOURCE = memory_leak_fix.c

all: $(TARGET) $(FIX_TARGET)

$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCE)

$(FIX_TARGET): $(FIX_SOURCE)
	$(CC) $(CFLAGS) -o $(FIX_TARGET) $(FIX_SOURCE)

run: $(TARGET)
	./$(TARGET)

valgrind: $(TARGET)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(TARGET)

valgrind-simple: $(TARGET)
	valgrind --tool=memcheck --leak-check=yes ./$(TARGET)

run-fix: $(FIX_TARGET)
	./$(FIX_TARGET)

valgrind-fix: $(FIX_TARGET)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(FIX_TARGET)

clean:
	rm -f $(TARGET) $(FIX_TARGET)
