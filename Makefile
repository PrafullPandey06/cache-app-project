CXX = g++

CXXFLAGS = -std=c++17 -Wall -Wextra

SRC = $(wildcard src/*.cpp)

TARGET = cache

all:
	$(CXX) $(CXXFLAGS) $(SRC) -Iinclude -o $(TARGET)

clean:
	rm -f $(TARGET)