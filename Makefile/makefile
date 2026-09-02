CC=gcc
CFLAGS= -Wall -Wextra -Wpedantic -g -O0 -Isrc
ASANFLAGS= -fsanitize=address,undefined
BUILD_DIR=build
TARGET=$(BUILD_DIR)/SNAKE_GAME
ASAN_TARGET=$(BUILD_DIR)/SNAKE_GAME_asan
TEST_SRCS=\
	test/ring_buffer_test.c\

TEST_RINGBUFFER=$(BUILD_DIR)/ring_buffer_test

test: (TEST_RINGBUFFER)
	./$(TEST_RINGBUFFER)

clean: 
	rm-rf $(BUILD_DIR)