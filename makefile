CC = gcc
CFLAGS = -std=c99 -c -Wall -Wextra -Iinclude
TFLAGS = -std=c99 -g -Wall -Wextra -Iinclude

SRC_DIR = src
BUILD_DIR = build
TEST_DIR = tests

SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))
TARGET := $(BUILD_DIR)/sudoku

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@
	@chmod u+x $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $< -o $@

tests: $(TARGET)
	@mkdir -p $(BUILD_DIR)
	@$(CC) $(TFLAGS) src/auxiliary.c tests/main.c -o $(BUILD_DIR)/aux_test
	@chmod u+x $(BUILD_DIR)/aux_test
	@./$(BUILD_DIR)/aux_test
	@./build/sudoku tests/sudoku01.txt tests/sudoku02.txt > /dev/null || true
	@if cmp tests/sudoku01.txt.out tests/sudoku01.txt.result; then \
		echo "sudoku01.txt was solved correctly by the program"; \
	else \
		echo "sudoku01.txt was NOT solved correctly by the program"; \
	fi

	@if cmp tests/sudoku02.txt.result tests/sudoku02.txt.out; then \
		echo "sudoku02.txt was solved correctly by the program"; \
	else \
		echo "sudoku02.txt was NOT solved correctly by the program"; \
	fi

clean:
	rm -rf $(BUILD_DIR)

.PHONY = all clean
