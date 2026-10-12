CC = mpicc

CFLAGS = -O2 -Wall
TARGET = mpitime_demo
SOURCE = MPITimelt.c
NP ?= 4
MPIRUN = mpirun

GCC = gcc
SERIAL_CFLAGS = -Wall -Wextra -g -std=c99
SERIAL_TARGET = serial_demo
SERIAL_SOURCE = Timelt.c

all: $(TARGET) $(SERIAL_TARGET)

$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCE)

run: $(TARGET)
	$(MPIRUN) -n $(NP) ./$(TARGET)

run-all: $(TARGET)
	@for n in 1 2 4; do \
		echo ""; \
		echo ">>> Running with $$n process(es)"; \
		$(MPIRUN) -n $$n ./$(TARGET); \
	done

$(SERIAL_TARGET): $(SERIAL_SOURCE)
	$(GCC) $(SERIAL_CFLAGS) -o $(SERIAL_TARGET) $(SERIAL_SOURCE)

run-serial: $(SERIAL_TARGET)
	./$(SERIAL_TARGET)

clean:
	rm -f $(TARGET) $(SERIAL_TARGET)