CXX = g++
CXXFLAGS = -I./include -std=c++17 -Wall -Wextra -Werror
SRC = src/Ship.cpp src/ShipManager.cpp src/GameField.cpp src/FieldDrawer.cpp main.cpp
OBJ = $(SRC:.cpp=.o)
EXEC = game

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)

.PHONY: all clean
