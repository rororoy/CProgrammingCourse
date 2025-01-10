# Compiler and flags
CC = gcc
CFLAGS = -ansi -Wall -pedantic

# Name of the final executable
TARGET = mycomp

# Default rule
all: $(TARGET)

# Link object files to create the executable
$(TARGET): mycomp.o complex.o
	$(CC) $(CFLAGS) -o $(TARGET) mycomp.o complex.o

# Compile mycomp.o
mycomp.o: mycomp.c complex.h
	$(CC) $(CFLAGS) -c mycomp.c

# Compile complex.o
complex.o: complex.c complex.h
	$(CC) $(CFLAGS) -c complex.c

# Clean up generated files
clean:
	rm -f *.o $(TARGET)
