# Compiler
CXX := g++

# Directories
SRC_DIR := src
BACKEND_DIR := backend
INCLUDE_DIR := include
BUILD_DIR := build

# Backend subfolders
BACKEND_NPUZZLE_DIR := $(BACKEND_DIR)/npuzzle
BACKEND_SOLVER_DIR := $(BACKEND_DIR)/solver
BACKEND_UTILS_DIR := $(BACKEND_DIR)/utils

# Source files
NPUZZLE_SRCS := $(wildcard $(BACKEND_NPUZZLE_DIR)/*.cpp)
SOLVER_SRCS := $(wildcard $(BACKEND_SOLVER_DIR)/*.cpp)
SRC_SRCS := $(wildcard $(SRC_DIR)/*.cpp)
UTILS_SRCS := $(wildcard $(BACKEND_UTILS_DIR)/*.cpp)

SRCS := $(NPUZZLE_SRCS) $(SOLVER_SRCS)  $(UTILS_SRCS) $(SRC_SRCS)

# Object files
OBJS := $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(subst /,_, $(SRCS)))

# Header files
DEPS := $(wildcard $(INCLUDE_DIR)/*.hpp)

# Compiler flags
CXXFLAGS := -std=c++17 -Wall -Wextra -g -I$(INCLUDE_DIR)

# OS-specific commands
ifeq ($(OS),Windows_NT)
    TARGET := npuzzle_exec.exe
    MKDIR_CMD = @if not exist $(BUILD_DIR) mkdir $(BUILD_DIR)
    RM_CMD = @if exist $(BUILD_DIR) rmdir /S /Q $(BUILD_DIR) & if exist $(TARGET) del $(TARGET)
else
    TARGET := npuzzle_exec
    MKDIR_CMD = @mkdir -p $(BUILD_DIR)
    RM_CMD = @rm -rf $(BUILD_DIR) $(TARGET)
endif

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

# Rule to build .o from src
$(BUILD_DIR)/src_%.o: $(SRC_DIR)/%.cpp $(DEPS)
	$(MKDIR_CMD)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to build .o from backend/npuzzle
$(BUILD_DIR)/backend_npuzzle_%.o: $(BACKEND_NPUZZLE_DIR)/%.cpp $(DEPS)
	$(MKDIR_CMD)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to build .o from backend/solver
$(BUILD_DIR)/backend_solver_%.o: $(BACKEND_SOLVER_DIR)/%.cpp $(DEPS)
	$(MKDIR_CMD)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to build .o from backend/utils
$(BUILD_DIR)/backend_utils_%.o: $(BACKEND_UTILS_DIR)/%.cpp $(DEPS)
	$(MKDIR_CMD)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	$(RM_CMD)