CC = g++

OBJ = obj
BIN = bin
SRC = src
INCLUDE = include

MAIN_TARGET = menu-main

SRC_FILES = libdrive menu-main

# Generate the full path for the .h files
HEADERS_FILES = libdrive.h
HEADERS_PATHS = $(addprefix $(INCLUDE)/, $(HEADERS_FILES))

# Generate the full path for the .o files
_OBJ_PATHS = $(addprefix $(OBJ)/, $(SRC_FILES))
OBJ_PATHS = $(addsuffix .o, $(_OBJ_PATHS))

INCLUDE_FLAGS = -I$(INCLUDE)

$(BIN)/$(MAIN_TARGET): $(OBJ_PATHS)
	mkdir -p $(BIN)
	$(CC) -o $(BIN)/$(MAIN_TARGET) $(OBJ_PATHS)

$(OBJ)/%.o: $(SRC)/%.cpp $(HEADERS_PATHS)
	mkdir -p $(OBJ)
	$(CC) -c -o $@ $< $(INCLUDE_FLAGS)

.PHONY: clean

clean:
	rm -rf obj
	rm -rf bin
