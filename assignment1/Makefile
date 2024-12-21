# Makefile for SFML Game Project

# Ensure obj/ directory exists
$(shell mkdir -p obj)
# Ensure bin/ directory exists
$(shell mkdir -p bin)

# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -I./include -Wall

# SFML libraries
LIBS = -lsfml-graphics -lsfml-window -lsfml-system

# Source and object files
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
SRC_FILES = $(SRC_DIR)/main.cpp $(SRC_DIR)/ConfigReader.cpp $(SRC_DIR)/Circle.cpp $(SRC_DIR)/Rectangle.cpp $(SRC_DIR)/Shape.cpp
OBJ_FILES = $(SRC_FILES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Output executable
EXEC = $(BIN_DIR)/MyGame

# Default target
all: $(EXEC)

# Linking
$(EXEC): $(OBJ_FILES)
	$(CXX) $(OBJ_FILES) -o $(EXEC) $(LIBS)

# Compiling source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up object and executable files
clean:
	rm -rf $(OBJ_DIR)/*.o $(BIN_DIR)/MyGame

# Remove object and executable files, and the entire bin and obj folders
clean_all:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Phony targets
.PHONY: all clean clean_all
