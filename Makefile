CXX = g++
CXXFLAGS = -std=c++17 -Iinclude -Wall -Wextra -finput-charset=UTF-8 -fexec-charset=UTF-8
LDFLAGS = 

SRC_DIR = src
SRC = $(wildcard $(SRC_DIR)/*.cpp)
OBJ = $(SRC:.cpp=.o)
EXEC = herta

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(OBJ) $(EXEC)

.PHONY: all clean
