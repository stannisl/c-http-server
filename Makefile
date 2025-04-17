# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS =

# Project structure
SRC_DIR = src
LIB_DIR = libs
BUILD_DIR = build
BIN_DIR = $(BUILD_DIR)/bin
OBJ_DIR = $(BUILD_DIR)/obj

# Source files (рекурсивный поиск .c файлов в src/ и libs/)
SRCS = $(shell find $(SRC_DIR) $(LIB_DIR) -type f -name '*.c')
OBJS = $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRCS))
TARGET = $(BIN_DIR)/server

# Tools
CLANG_FORMAT = clang-format
CPPLINT = cpplint
VALGRIND = valgrind
DOXYGEN = doxygen

.PHONY: all clean format lint valgrind docs

all: $(TARGET)

# Build main target
$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CC) $(LDFLAGS) $^ -o $@

# Compile objects with proper directory structure
$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

# Create build directories
$(BIN_DIR) $(OBJ_DIR):
	@mkdir -p $@

# Code formatting (including libs)
format:
	find src include libs -type f \( -name '*.c' -o -name '*.h' \) -exec $(CLANG_FORMAT) -i --style=Microsoft {} \;

# Linting with directory structure support
lint:
	$(CPPLINT) --filter=-readability/casting,-build/include_subdir \
	--root=. \
	--extensions=c,h \
	$(shell find src include libs -type f \( -name '*.c' -o -name '*.h' \))

# Memory checking
valgrind: $(TARGET)
	$(VALGRIND) --leak-check=full --track-origins=yes --show-leak-kinds=all ./$(TARGET)

# Documentation with libs support
docs:
	$(DOXYGEN) Doxyfile

clean:
	rm -rf $(BUILD_DIR)
	rm -rf docs/html docs/latex

distclean: clean
	rm -rf .clang-format

help:
	@echo "Available targets:"
	@echo "  all       - Build project (default)"
	@echo "  clean     - Remove build artifacts"
	@echo "  format    - Format source code"
	@echo "  lint      - Check code style"
	@echo "  valgrind  - Run memory checker"
	@echo "  docs      - Generate documentation"
	@echo "  distclean - Full cleanup"
