# Makefile

CC = gcc
CFLAGS = -Wall -Wextra -Iinclude
SRC_DIR = src
OBJ_DIR = build
BIN_DIR = bin

SOURCES	=	$(wildcard	$(SRC_DIR)/*.c)
OBJECTS	=	$(patsubst	$(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SOURCES))
TARGET	= $(BIN_DIR)/game

# Default target
all:	$(TARGET)

#	Linking
$(TARGET):	$(OBJECTS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(OBJECTS) -o $(TARGET)

# Compiling
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC)	$(CFLAGS)	-c $< -o $@

# Clearn build artifacts
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all clean
