# -- Windows + MinGW
# to compile use:      mingw32-make
# to run use:          ./build/db_test
# to clean use:        mingw32-make clean


# -- Linux / macOS / MSYS2
# to compile use:      make
# to run use:          ./build/db_test
# to clean use:        make clean


# Compiler
CC = gcc

# Compilation flags
CFLAGS = -Wall -Wextra -Werror -std=c11 -Iinclude

# Object files
OBJ = build/main.o \
	build/db.o \
	build/table.o \
	build/record.o \
	build/file.o \
	build/error.o

# Final executable
TARGET = build/db_test

# Phony targets
.PHONY: clean


# Link
$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)


# Compile rule
build/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@


# main.c lives at root
build/main.o: main.c
	$(CC) $(CFLAGS) -c $< -o $@


# Clean
clean:
	rm -f build/*.o $(TARGET)
