# Compiler
CXX := g++
# Compiler flags
CXXFLAGS := -O1 -Wall -Wextra -std=c++17
# Include Path
INCLUDE := -Isrc

# Directories
SRC_DIR := src
BUILD_DIR := build
LIB_DIR := lib
BIN_DIR := bin
TEST_DIR := test

# Library
LIB_NAME := datastructures
LIB_SOURCES := $(wildcard $(SRC_DIR)/*.cpp)
LIB_OBJECTS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(LIB_SOURCES))
LIB_TARGET := $(LIB_DIR)/lib$(LIB_NAME).a

# Test program
TEST_NAME := test_datastructures
TEST_SOURCES := $(wildcard $(TEST_DIR)/*.cpp)
TEST_OBJECTS := $(patsubst $(TEST_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(TEST_SOURCES))
TEST_TARGET := $(BIN_DIR)/$(TEST_NAME)

# Targets
all: $(LIB_TARGET) $(TEST_TARGET)

$(LIB_TARGET): $(LIB_OBJECTS)
	@mkdir -p $(LIB_DIR)
	ar rcs $@ $^

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -o $@ -c $<

$(TEST_TARGET): $(TEST_OBJECTS) $(LIB_TARGET)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(BUILD_DIR)/%.o: $(TEST_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ -c $<

clean:
	rm -rf $(BUILD_DIR) $(LIB_DIR)

distclean: clean
	rm -rf $(BIN_DIR)

.PHONY: all clean
