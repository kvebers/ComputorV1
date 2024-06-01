FILES = solver.cpp
CC = g++
CFLAGS = -std=c++11 -Wall -Wextra -Werror -pedantic -O3
TARGET = solver

all: $(TARGET)
	$(CC) $(CFLAGS) -o $(TARGET) $(FILES)

clean:
	rm -f *.o
	
fclean: clean
	rm -f $(TARGET)
	
	
.PHONY: all fclean clean