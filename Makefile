GCC = g++
FLAGS = -Wall -Wextra -w -Wno-unused-parameter -std=c++17 -ggdb

BIN = bin
SRC = source
INCLUDE	= includes
LIB = lib

LIBS = -lsfml-graphics -lsfml-window -lsfml-system
EXEC = main

MKDIR_P = mkdir -p

.PHONY: directories

all: directories $(BIN)/$(EXEC)

directories: ${BIN}

${BIN}:
	${MKDIR_P} ${BIN}

run: 
	./$(BIN)/$(EXEC)

$(BIN)/$(EXEC): $(SRC)/*.cpp
	$(GCC) $(FLAGS) -I$(INCLUDE) -L$(LIB) $^ -o $@ $(LIBS)

clean:
	-rm $(BIN)/*