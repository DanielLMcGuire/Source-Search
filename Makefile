
# Compiler Options
CXX = g++
CXXFLAGS = -Wall -std=c++23

SRC_DIR = ./src
OBJ_DIR = ./obj
BIN_DIR = ./bin

# Repo Specific Stuff
TARGET = sourcesearch.out
SRC = $(SRC_DIR)/sourcesearch.cpp
OBJ = $(OBJ_DIR)/sourcesearch.o

# Rules
all: $(BIN_DIR)/$(TARGET)

$(BIN_DIR)/$(TARGET): $(OBJ)
	mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $(BIN_DIR)/$(TARGET) $(OBJ)

$(OBJ): $(SRC)
	mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $(SRC) -o $(OBJ)

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all clean
