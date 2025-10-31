CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2

TARGET = bst_program
SRC = binary_search_tree.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all run clean
