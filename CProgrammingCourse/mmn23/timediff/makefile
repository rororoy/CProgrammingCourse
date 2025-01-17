# Compiler and flags
CC = gcc
CFLAGS = -ansi -Wall -pedantic

# Name of the final executable
TARGET = timediff

# Default rule
all: $(TARGET)

# Link object files to create the executable
$(TARGET): timediff.o utils.o
	$(CC) $(CFLAGS) -o $(TARGET) timediff.o utils.o -lm

# Compile mycomp.o
timediff.o: timediff.c timediff.h
	$(CC) $(CFLAGS) -c timediff.c

# Compile utils.o
utils.o: utils.c timediff.h
	$(CC) $(CFLAGS) -c utils.c

# Clean up generated files
clean:
	rm -f *.o $(TARGET)
