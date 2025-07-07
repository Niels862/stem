TARGET = stem
LIB = lib$(TARGET).a

CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -Werror -std=c99 -O2 -g

SRC_DIR = src
INC_DIR = include
TEST_DIR = tests
BUILD_DIR = build

SOURCES := $(shell find $(SRC_DIR) -name '*.c')
OBJECTS := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SOURCES))

TEST_SOURCES := $(wildcard $(TEST_DIR)/*.c)
TEST_BINS := $(patsubst $(TEST_DIR)/%.c, $(BUILD_DIR)/tests/%, $(TEST_SOURCES))

INCFLAGS := -I$(INC_DIR) -I$(SRC_DIR)

DEPS := $(OBJECTS:.o=.d)

.PHONY: all clean tests

all: $(LIB) tests

$(LIB): $(OBJECTS)
	@mkdir -p $(@D)
	ar rcs $@ $^

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCFLAGS) -MMD -c $< -o $@

tests: $(TEST_BINS)

$(BUILD_DIR)/tests/%: $(TEST_DIR)/%.c $(LIB)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCFLAGS) -o $@ $< $(LIB)

clean:
	rm -rf $(BUILD_DIR) $(LIB)

-include $(DEPS)
