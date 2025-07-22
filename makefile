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

tests: $(TEST_DIR)/main.c $(SRC_DIR)/auxiliary.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(TFLAGS) $^ -o $(BUILD_DIR)/test
	@chmod u+x $(BUILD_DIR)/test
	@./$(BUILD_DIR)/test

clean:
	rm -rf $(BUILD_DIR)

.PHONY = all clean
