CXX = g++
CXXFLAGS = -std=c++17 -Iinclude -Wall
SRC = src/main.cpp src/Player.cpp src/Enemy.cpp \
      src/GameSystem.cpp src/EventSystem.cpp \
      src/Blessing.cpp src/FileManager.cpp
OBJ = $(SRC:.cpp=.o)
EXEC = herta

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f $(OBJ) $(EXEC)

.PHONY: all clean
