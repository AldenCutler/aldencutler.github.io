# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -g

# Source files
SRCS = mmu.c helpers.c

# Object files
OBJS = $(SRCS:.c=.o)

# Target executable
TARGET = project3

# Default target
all: $(TARGET)

# Compile source files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Link object files into the target executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@
	> disk									# Create an empty disk file (or clear it if it already exists)

# Clean up object files and the target executable
clean:
	rm -f $(OBJS) $(TARGET) disk
