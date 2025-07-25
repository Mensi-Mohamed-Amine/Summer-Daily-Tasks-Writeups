# The maze begins at this location — your journey starts here.

# Compiler and linker settings
CC      := gcc
CFLAGS  := -Wall -Wextra -fstack-protector-all
LDFLAGS := -lncurses

# Target and source
TARGET  := maze
SRC     := maze.c

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)

clean:
	rm -f $(TARGET)

