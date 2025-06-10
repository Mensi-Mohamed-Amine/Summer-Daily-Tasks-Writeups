# Makefile for compiling oob.c

CC = gcc
CFLAGS = -no-pie
TARGET = oob
SRC = oob.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)
