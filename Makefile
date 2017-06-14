CC = g++

OBJ = obj
BIN = bin
SRC = src
LIB = lib
INCLUDE = include
TEST = test

MAIN_TARGET = menu-main
SRC_FILES = libfat menu-main
HEADERS_FILES = libfat.h
TEST_FILES = test-drive-simple

# Flags to compile the tests
# If gtest is installed in a different location, add the linking
# and include directories here
TEST_FLAGS = -lgtest -lpthread

# Generate the full path for the cpp files (usually src/srcName.cpp)
_SRC_PATHS = $(addprefix $(SRC)/, $(SRC_FILES))
SRC_PATHS = $(addsuffix .cpp, $(_SRC_PATHS))

# Generate the full path for the .h files (usually include/headerName)
HEADERS_PATHS = $(addprefix $(INCLUDE)/, $(HEADERS_FILES))

# Generate the full path for the .o files (usually obj/srcName.o)
_OBJ_PATHS = $(addprefix $(OBJ)/, $(SRC_FILES))
OBJ_PATHS = $(addsuffix .o, $(_OBJ_PATHS))

# Generate the full path for test binaries (usually test/bin/testName)
TEST_BIN_PATHS = $(addprefix $(TEST)/$(BIN)/, $(TEST_FILES))

# Add the headers directory to the compilation flags
INCLUDE_FLAGS = -I$(INCLUDE)

run-main: $(BIN)/$(MAIN_TARGET)
	./$(BIN)/$(MAIN_TARGET)

$(BIN)/$(MAIN_TARGET): $(OBJ_PATHS)
	mkdir -p $(BIN)
	$(CC) -o $(BIN)/$(MAIN_TARGET) $(OBJ_PATHS)

$(OBJ)/%.o: $(SRC)/%.cpp $(HEADERS_PATHS)
	mkdir -p $(OBJ)
	$(CC) -c -o $@ $< $(INCLUDE_FLAGS)

run-tests: build-tests
	$(foreach var,$(TEST_BIN_PATHS),./$(var) && ) :

build-tests: $(TEST_BIN_PATHS)

# Build the tests (all the binaries in TEST_BIN_PATHS)
$(TEST)/$(BIN)/%: $(TEST)/%.cpp $(HEADERS_PATHS) $(SRC_PATHS) $(OBJ_PATHS)
	mkdir -p $(TEST)/$(BIN)
	$(CC) -o $@ $< $(INCLUDE_FLAGS) $(TEST_FLAGS)

.PHONY: clean

clean:
	rm -rf $(OBJ)
	rm -rf $(BIN)
	rm -rf $(TEST)/$(BIN)
