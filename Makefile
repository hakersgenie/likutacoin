CXX = g++
CXXFLAGS = -std=c++17 -Wall
INCLUDES = -Isrc -Iexternal

SRC = $(wildcard src/*.cpp)
OBJ = $(SRC:.cpp=.o)
TARGET = likuta

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $^

clean:
	rm -f $(TARGET) src/*.o
