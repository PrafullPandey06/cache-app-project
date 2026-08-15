# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++17 -Wall -Wextra

# Source files
SRC = src/main.cpp src/Cache.cpp

TARGET = cache

all:
	$(CXX) $(CXXFLAGS) $(SRC) -Iinclude -o $(TARGET)

clean:
	rm -f $(TARGET)