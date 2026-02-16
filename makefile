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
CFLAGS = -Wall -Wextra -Werror -std=c11 -Ilib/include -Iapp/include

# Src objects
SRC_OBJ = \
	build/db.o \
	build/table.o \
	build/record.o \
	build/file.o \
	build/error.o

# App objects
APP_OBJ = \
	build/main.o \
	build/menu.o \
	build/input.o


# All objects
OBJ = $(SRC_OBJ) $(APP_OBJ)

# Final executable
TARGET = build/db_test

# Phony targets
.PHONY: clean


# Link
$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)


# Compile src files
build/%.o: lib/src/%.c
	$(CC) $(CFLAGS) -c $< -o $@


# Compile app files
build/%.o: app/src/%.c
	$(CC) $(CFLAGS) -c $< -o $@


# Clean
clean:
	rm -f build/*.o $(TARGET)
