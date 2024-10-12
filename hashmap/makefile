CC = gcc                # Compiler
CFLAGS = -Wall -g       # Compiler flags: -Wall for warnings, -g for debugging
AR = ar                 # Archiver for static libraries
LIBS = -L. -llinked
TARGET = libhashmap.a    # Target library name

# Object files
OBJ = hashmap.o

# Rule to build the static library
$(TARGET): $(OBJ)
	$(AR) rcs $(TARGET) $(OBJ)

# Rule to build the object file from linked.c
hashmap.o: hashmap.c hashmap.h
	$(CC) $(CFLAGS) -c hashmap.c

# Clean rule to remove generated files
clean:
	rm -f $(OBJ) $(TARGET)
