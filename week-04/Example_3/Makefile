CXX = g++
CXXFLAGS = -O2 -Wall -std=c++17
TARGET = aosoa_measurement
SOURCE = aosoa_measurement.cpp
LEN ?= 1000000
V ?= 4

all: $(TARGET)

$(TARGET): $(SOURCE)
	$(CXX) $(CXXFLAGS) -DV=$(V) -o $(TARGET) $(SOURCE)

# V is set at compile time, so rebuild before every run
run:
	$(CXX) $(CXXFLAGS) -DV=$(V) -o $(TARGET) $(SOURCE)
	./$(TARGET) $(LEN)

clean:
	rm -f $(TARGET)

.PHONY: all run clean
