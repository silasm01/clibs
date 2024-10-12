CC = gcc                # Compiler
CFLAGS = -Wall -g       # Compiler flags: -Wall for warnings, -g for debugging
AR = ar                 # Archiver for static libraries
TARGET = libcircularbuf.a    # Target library name

# Object files
OBJ = circularbuf.o

# Rule to build the static library
$(TARGET): $(OBJ)
	$(AR) rcs $(TARGET) $(OBJ)

# Rule to build the object file from linked.c
circularbuf.o: circularbuf.c circularbuf.h
	$(CC) $(CFLAGS) -c circularbuf.c

# Clean rule to remove generated files
clean:
	rm -f $(OBJ) $(TARGET)
