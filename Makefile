# Compiler Options
CXX = g++
CXXFLAGS = -Wall -std=c++23

SRC_DIR = ./src
OBJ_DIR = ./obj
BIN_DIR = ./bin

# Repo Specific Stuff
TARGET_LINUX = sourcesearch.out
TARGET_WIN = sourcesearch.exe
SRC = $(SRC_DIR)/sourcesearch.cpp
OBJ = $(OBJ_DIR)/sourcesearch.o

# Detect platform
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
    TARGET := $(TARGET_LINUX)
else
    TARGET := $(TARGET_WIN)
endif

# Default target
all: linux

# Linux build
linux: $(BIN_DIR)/$(TARGET_LINUX)

$(BIN_DIR)/$(TARGET_LINUX): $(OBJ)
	mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $(BIN_DIR)/$(TARGET_LINUX) $(OBJ)

# Windows build
win: $(BIN_DIR)/$(TARGET_WIN)

$(BIN_DIR)/$(TARGET_WIN): $(OBJ)
	mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $(BIN_DIR)/$(TARGET_WIN) $(OBJ)

$(OBJ): $(SRC)
	mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $(SRC) -o $(OBJ)

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all linux win clean
