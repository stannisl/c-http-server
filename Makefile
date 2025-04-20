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

SRCS = $(shell find $(SRC_DIR) $(LIB_DIR) -type f -name '*.c')
OBJS = $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRCS))
TARGET = $(BIN_DIR)/server

CLANG_FORMAT = clang-format
CPPLINT = cpplint
VALGRIND = valgrind
DOXYGEN = doxygen

.PHONY: all clean format lint valgrind docs

all: $(TARGET)

$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CC) $(LDFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR) $(OBJ_DIR):
	@mkdir -p $@

format:
	@clang-format --style=Microsoft -i $$(find src include -name "*.c")
	@clang-format --style=Microsoft -i $$(find src include -name "*.h")

lint:
	$(CPPLINT) --filter=-readability/casting,-build/include_subdir \
	--root=. \
	--extensions=c,h \
	$(shell find src include libs -type f \( -name '*.c' -o -name '*.h' \))

valgrind: $(TARGET)
	$(VALGRIND) --leak-check=full --track-origins=yes --show-leak-kinds=all ./$(TARGET)

docs:
	$(DOXYGEN) Doxyfile
	xdg-open docs/html/index.html

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
