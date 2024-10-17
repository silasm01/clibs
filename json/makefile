CC = gcc                # Compiler
CFLAGS = -Wall -g       # Compiler flags: -Wall for warnings, -g for debugging
AR = ar                 # Archiver for static libraries
LIBS = -L. 
TARGET = libjson.a    # Target library name

# Object files
OBJ = json.o

# Rule to build the static library
$(TARGET): $(OBJ)
	$(AR) rcs $(TARGET) $(OBJ)

# Rule to build the object file from linked.c
json.o: json.c json.h
	$(CC) $(CFLAGS) -c json.c

# Clean rule to remove generated files
clean:
	rm -f $(OBJ) $(TARGET)
