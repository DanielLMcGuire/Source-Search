# I have no idea how a makefile works lol 
#(feel free to change and submit a pr)

# Compiler Options
CXX = g++
CXXFLAGS = -Wall -std=c++17

SRC_DIR = ./src
OBJ_DIR = ./obj
BIN_DIR = ./bin

# Repo Specific Stuff
TARGET = sourcesearch.out
SRCS = $(SRC_DIR)/sourcesearch.cpp 
OBJS = $(OBJ_DIR)/sourcesearch.o 

# Default target
all: $(BIN_DIR)/$(TARGET)

# Build target
$(BIN_DIR)/$(TARGET): $(OBJS)
	mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $(BIN_DIR)/$(TARGET) $(OBJS)

# Compile sources into objects
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -f $(BIN_DIR)/$(TARGET)
	rm -rf $(OBJ_DIR)

.PHONY: all clean
