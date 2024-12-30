CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I./include
SRC_DIR = src
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj
BIN_DIR = $(BUILD_DIR)/bin
DATA_DIR = data

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Executable name
TARGET = $(BIN_DIR)/crypto

# Default target
all: directories $(TARGET)

# Create necessary directories
directories:
	@mkdir -p $(OBJ_DIR) $(BIN_DIR)
	@mkdir -p $(DATA_DIR)/input $(DATA_DIR)/output
	@if [ ! -f $(DATA_DIR)/input/primes.txt ]; then \
		echo "17 23" > $(DATA_DIR)/input/primes.txt; \
	fi
	@if [ ! -f $(DATA_DIR)/input/message.txt ]; then \
		echo "Hello, RSA encryption!" > $(DATA_DIR)/input/message.txt; \
	fi

# Link object files to create executable
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET)

# Compile source files to object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -rf $(BUILD_DIR)

# Clean all generated files including data outputs
cleanall: clean
	rm -f $(DATA_DIR)/output/*

# Run the program
run: all
	@$(TARGET)

.PHONY: all clean cleanall run directories
