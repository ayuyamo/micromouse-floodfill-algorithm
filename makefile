# Compiler and compiler flags
CC = gcc
CFLAGS = -Wall -Wextra -g

# Target executable
TARGET = maze_solver

# Source and object files
SRCS = main.c floodfill.c navigation.c queue.c API.c
OBJS = $(SRCS:.c=.o)

# Default target
all: $(TARGET)

# Rule to build the target executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

# Rule to compile .c files into .o files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJS) $(TARGET)

run:
	make clean
	make
	./$(TARGET)
	make clean
