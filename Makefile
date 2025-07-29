# Compiler
CXX := g++

# Main Directories
SRC_DIR := src
BACKEND_DIR := backend
INCLUDE_DIR := include
BUILD_DIR := build

# Backend subfolders 
BACKEND_NPUZZLE_DIR := $(BACKEND_DIR)/npuzzle
BACKEND_SOLVER_DIR := $(BACKEND_DIR)/solver
BACKEND_UTILS_DIR := $(BACKEND_DIR)/utils
BACKEND_HEURISTICS_DIR := $(BACKEND_DIR)/heuristics
BACKEND_API_DIR := $(BACKEND_DIR)/api
BACKEND_CROW_DIR := $(BACKEND_DIR)/Crow

# Source files
NPUZZLE_SRCS := $(wildcard $(BACKEND_NPUZZLE_DIR)/*.cpp)
SOLVER_SRCS := $(wildcard $(BACKEND_SOLVER_DIR)/*.cpp)
SRC_SRCS := $(wildcard $(SRC_DIR)/*.cpp)
UTILS_SRCS := $(wildcard $(BACKEND_UTILS_DIR)/*.cpp)
HEURISTICS_SRCS := $(wildcard $(BACKEND_HEURISTICS_DIR)/*.cpp)
API_SRCS := $(wildcard $(BACKEND_API_DIR)/*.cpp)

# Object files for main.cpp specific to each mode
MAIN_OBJ_CLI := $(BUILD_DIR)/main_cli.o
MAIN_OBJ_SERVER := $(BUILD_DIR)/main_server.o

# Common objects for both CLI and Server 
CORE_OBJS := \
    $(patsubst $(BACKEND_NPUZZLE_DIR)/%.cpp,$(BUILD_DIR)/backend_npuzzle_%.o,$(NPUZZLE_SRCS)) \
    $(patsubst $(BACKEND_SOLVER_DIR)/%.cpp,$(BUILD_DIR)/backend_solver_%.o,$(SOLVER_SRCS)) \
    $(patsubst $(BACKEND_UTILS_DIR)/%.cpp,$(BUILD_DIR)/backend_utils_%.o,$(UTILS_SRCS)) \
    $(patsubst $(BACKEND_HEURISTICS_DIR)/%.cpp,$(BUILD_DIR)/backend_heuristics_%.o,$(HEURISTICS_SRCS)) \
    $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/src_%.o,$(filter-out $(SRC_DIR)/main.cpp,$(SRC_SRCS)))

# Objects specific to the Server application (API handlers, server_app)
SERVER_SPECIFIC_OBJS := $(patsubst $(BACKEND_API_DIR)/%.cpp,$(BUILD_DIR)/backend_api_%.o,$(API_SRCS))

# All objects required for the CLI application
CLI_APP_OBJS := $(MAIN_OBJ_CLI) $(CORE_OBJS)

# All objects required for the Server application
SERVER_APP_OBJS := $(MAIN_OBJ_SERVER) $(CORE_OBJS) $(SERVER_SPECIFIC_OBJS)

# Header files
DEPS := $(wildcard $(INCLUDE_DIR)/*.hpp)

# Compiler flags
CXXFLAGS := -std=c++17 -Wall -Wextra -g -I$(INCLUDE_DIR) -I$(strip $(BACKEND_CROW_DIR))/include -I$(strip $(BACKEND_CROW_DIR))/thirdparty/asio/asio/include

# OS-specific settings
ifeq ($(OS),Windows_NT)
    TARGET := npuzzle_exec.exe
    SERVER_TARGET := npuzzle_server.exe
    MKDIR_CMD = @if not exist $(BUILD_DIR) mkdir $(BUILD_DIR)
    RM_CMD = @if exist $(BUILD_DIR) rmdir /S /Q $(BUILD_DIR) & if exist $(TARGET) del $(TARGET) & if exist $(SERVER_TARGET) del $(SERVER_TARGET)
else
    TARGET := npuzzle_exec
    SERVER_TARGET := npuzzle_server
    MKDIR_CMD = @mkdir -p $(BUILD_DIR)
    RM_CMD = @rm -rf $(BUILD_DIR) $(TARGET) $(SERVER_TARGET)
endif

# Targets
.PHONY: all cli server clean run_server

# Builds both executables
all: $(TARGET) $(SERVER_TARGET)

# Build only the CLI executable
cli: $(TARGET)

# Compile the CLI binary
$(TARGET): $(CLI_APP_OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@ -lpthread

# Target to build only the server executable
server: $(SERVER_TARGET)

# Compile the server binary
$(SERVER_TARGET): $(SERVER_APP_OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@ -lpthread

# Shortcut to build and run the server
run_server: server
	./$(SERVER_TARGET)

# Compilation rule for main.cpp in CLI mode
$(MAIN_OBJ_CLI): $(SRC_DIR)/main.cpp $(DEPS)
	$(MKDIR_CMD)
	$(CXX) $(CXXFLAGS) -DMODE_CLI -c $< -o $@

# Compilation rule for main.cpp in SERVER mode
$(MAIN_OBJ_SERVER): $(SRC_DIR)/main.cpp $(DEPS)
	$(MKDIR_CMD)
	$(CXX) $(CXXFLAGS) -DMODE_SERVER -c $< -o $@

# Generic rule for compiling other .cpp files 
$(BUILD_DIR)/src_%.o: $(SRC_DIR)/%.cpp $(DEPS)
	$(MKDIR_CMD)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compilation rule for backend/npuzzle .cpp files
$(BUILD_DIR)/backend_npuzzle_%.o: $(BACKEND_NPUZZLE_DIR)/%.cpp $(DEPS)
	$(MKDIR_CMD)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compilation rule for backend/solver .cpp files
$(BUILD_DIR)/backend_solver_%.o: $(BACKEND_SOLVER_DIR)/%.cpp $(DEPS)
	$(MKDIR_CMD)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compilation rule for backend/utils .cpp files
$(BUILD_DIR)/backend_utils_%.o: $(BACKEND_UTILS_DIR)/%.cpp $(DEPS)
	$(MKDIR_CMD)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compilation rule for backend/heuristics .cpp files
$(BUILD_DIR)/backend_heuristics_%.o: $(BACKEND_HEURISTICS_DIR)/%.cpp $(DEPS)
	$(MKDIR_CMD)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compilation rule for backend/api .cpp files
$(BUILD_DIR)/backend_api_%.o: $(BACKEND_API_DIR)/%.cpp $(DEPS)
	$(MKDIR_CMD)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up binaries and object files
clean:
	$(RM_CMD)