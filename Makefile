# Compiler Options
CXX = g++
CXXFLAGS = -Wall -std=c++17

SRC_DIR = ./src
OBJ_DIR = ./obj
BIN_DIR = ./bin

# Repo Specific Stuff
TARGET_LINUX = sourcesearch.out
TARGET_WIN = sourcesearch.exe
SRCS = $(SRC_DIR)/sourcesearch.cpp 
OBJS = $(OBJ_DIR)/sourcesearch.o 

# Detect platform
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
    TARGET := $(TARGET_LINUX)
else
    TARGET := $(TARGET_WIN)
endif

# Default target
all: $(TARGET)

# Linux build
linux: $(BIN_DIR)/$(TARGET_LINUX)

$(BIN_DIR)/$(TARGET_LINUX): $(OBJS)
	mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $(BIN_DIR)/$(TARGET_LINUX) $(OBJS)

# Windows build
win: $(BIN_DIR)/$(TARGET_WIN)

$(BIN_DIR)/$(TARGET_WIN): $(OBJS)
	mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $(BIN_DIR)/$(TARGET_WIN) $(OBJS)

# Compile sources into objects
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build artifacts (only binaries, not DLLs)
clean:
	rm -f $(BIN_DIR)/$(TARGET_LINUX) $(BIN_DIR)/$(TARGET_WIN)
	rm -rf $(OBJ_DIR)

.PHONY: all linux win clean
