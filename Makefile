CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -Iinclude

# build path
TARGET = build/sami

# find all .c files
SRC = $(wildcard src/*.c)

all: $(TARGET)

# build the executable when something changes
$(TARGET): $(SRC)
		@mkdir -p build
		$(CC) $(CFLAGS) $(SRC) -o $(TARGET)
		@echo "Build has finished succesfully"

clean:
	rm -rf build/*
	@echo "everything has been cleaned"

run: all
	./$(TARGET) $(ARGS) 