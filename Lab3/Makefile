#LAB 3 MAKEFILE

#Define the C compiler to use
CC = gcc

#Define any flags
CFLAGS = -Wall

#Define the target executable
TARGET = FCFS

#Define source and object files
SRC = FCFS.c
OBJ = FCFS.o

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

$(OBJ): $(SRC)
	$(CC) $(CFLAGS) -c $(SRC)


#clean up the object files and the executable
clean:
	rm -f $(TARGET) $(OBJ)
