#LAB 4 MAKEFILE

#Define the C compiler to use
CC = gcc

#Define any flags
CFLAGS = -Wall

#Define the target executable
TARGET = Boyce_testFC

#Define source and object files
SRC = Boyce_testFC.c
OBJ = Boyce_testFC.o

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

$(OBJ): $(SRC)
	$(CC) $(CFLAGS) -c $(SRC)


#clean up the object files and the executable
clean:
	rm -f $(TARGET) $(OBJ)
