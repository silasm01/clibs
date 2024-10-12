CC = gcc                # Compiler
CFLAGS = -Wall -g       # Compiler flags: -Wall for warnings, -g for debugging
AR = ar                 # Archiver for static libraries
TARGET = liblinked.a    # Target library name

# Object files
OBJ = linked.o

# Rule to build the static library
$(TARGET): $(OBJ)
	$(AR) rcs $(TARGET) $(OBJ)

# Rule to build the object file from linked.c
linked.o: linked.c linked.h
	$(CC) $(CFLAGS) -c linked.c

# Clean rule to remove generated files
clean:
	rm -f $(OBJ) $(TARGET)
