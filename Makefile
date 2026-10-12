.DEFAULT_GOAL := all

CC ?= gcc
CPPFLAGS += -Isrc
CFLAGS ?= -Wall -Wextra -Wpedantic -g -O0
ASANFLAGS ?= -fsanitize=address,undefined -fno-omit-frame-pointer
BUILD_DIR ?= build

TEST_SRC := test/ring_buffer_test.c
TEST_RINGBUFFER := $(BUILD_DIR)/ring_buffer_test
ASAN_TEST_RINGBUFFER := $(BUILD_DIR)/ring_buffer_test_asan

.PHONY: all build run test asan clean

# src/ is currently empty; build and run the available test program.
all: build
build: $(TEST_RINGBUFFER)
run: test

test: $(TEST_RINGBUFFER)
	"$(abspath $(TEST_RINGBUFFER))"

asan: $(ASAN_TEST_RINGBUFFER)
	"$(abspath $(ASAN_TEST_RINGBUFFER))"

$(BUILD_DIR)/:
	mkdir -p -- "$@"

$(TEST_RINGBUFFER): $(TEST_SRC) Makefile | $(BUILD_DIR)/
	$(CC) $(CPPFLAGS) $(CFLAGS) -MMD -MP -MF "$@.d" $(TEST_SRC) $(LDFLAGS) -o "$@" $(LDLIBS)

$(ASAN_TEST_RINGBUFFER): $(TEST_SRC) Makefile | $(BUILD_DIR)/
	$(CC) $(CPPFLAGS) $(CFLAGS) $(ASANFLAGS) -MMD -MP -MF "$@.d" $(TEST_SRC) $(LDFLAGS) -o "$@" $(LDLIBS)

-include $(TEST_RINGBUFFER).d $(ASAN_TEST_RINGBUFFER).d

clean:
	@test -n "$(strip $(BUILD_DIR))" || { echo "Refusing to clean an empty BUILD_DIR" >&2; exit 1; }
	@dir=$$(realpath -m -- "$(BUILD_DIR)") && cwd=$$(pwd -P) && \
	test "$$dir" != / && \
	case "$$cwd" in "$$dir"|"$$dir"/*) echo "Refusing to remove the working directory or an ancestor" >&2; exit 1 ;; \
	*) rm -rf -- "$$dir" ;; esac
