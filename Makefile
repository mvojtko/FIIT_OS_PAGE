# Compiler and flags
CC = gcc
CFLAGS = -fPIC -Wall -Wextra -O2 -Isrc \
		 -Dmalloc=__forbidden_malloc \
		 -Dcalloc=__forbidden_calloc \
		 -Drealloc=__forbidden_realloc \
		 -Dfree=__forbidden_free

LDFLAGS = -shared

# Directories
SRC_DIR = src
BUILD_DIR = build

# Output targets
TARGET = $(BUILD_DIR)/libospager.so

# Source files
SRC = $(wildcard $(SRC_DIR)/*.c)

# Object files
OBJ = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC))

# Default target: build app (which depends on the library)
all: test

test: $(TARGET)
	@LD_LIBRARY_PATH=$(BUILD_DIR) /ws/FIIT_OS_PAGE_TEST/build/os 

# Build the shared library
$(TARGET): $(OBJ) | $(BUILD_DIR)
	@echo Linking $@
	@$(CC) $(LDFLAGS) -o $@ $^

# Compile library source files to object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	@echo Compiling $<
	@$(CC) $(CFLAGS) -c $< -o $@

# Ensure build directory exists
$(BUILD_DIR):
	@echo Creating $@
	@mkdir -p $(BUILD_DIR)

# Clean all build artifacts
clean:
	@echo Deleting $(BUILD_DIR)
	@rm $(SRC_DIR)/*.c
	@rm -rf $(BUILD_DIR)
