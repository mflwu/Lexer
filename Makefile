#MAKEFILE FOR THE PROJECT with main.cpp, lexer.h, lexer.cpp, symbole.h, symbole.cpp, etats.h, etats.cpp, automate.h, automate.cpp

# Compiler
CC = g++

# Compiler flags
CFLAGS = -Wall -std=c++11

# Executable name
EXEC = main

# Source files
SRC = $(wildcard *.cpp)

# Object files
OBJ = $(SRC:.cpp=.o)

# Build executable
all: $(EXEC)

# Link object files to create executable
$(EXEC): $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^

# Compile source files
%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

# Clean object files
clean:
	rm -f $(OBJ)
	rm -f $(EXEC)

# Clean object files and executable
mrproper: clean
	rm -f $(EXEC)

# Dependencies
main.o: lexer.h automate.h
lexer.o: lexer.h symbole.h automate.h
symbole.o: symbole.h
etats.o: etats.h symbole.h automate.h
automate.o: automate.h etats.h symbole.h

# End of makefile
