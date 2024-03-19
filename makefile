# Makefile for a C project with modules and header files

# Compiler and compiler flags
CC = gcc
CFLAGS = -std=c17 -pedantic -Wall `pkg-config --cflags MLV`
LDFLAGS = `pkg-config --libs-only-other --libs-only-L MLV`
LDLIBS = `pkg-config --libs-only-l MLV`

# Directories
SRC_DIR = src
INC_DIR = include
BUILD_DIR = build

# Source files and object files
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC_FILES))

# Executable name
EXE = main

# Default target
all: $(EXE) clean

# Rule to build the executable
$(EXE): $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS) 

# Rule to compile source files into object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -I$(INC_DIR) -c -o $@ $<

# Rule to clean up the generated files
clean:
	rm -f $(OBJ_FILES)
