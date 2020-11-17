# Adapted from simple makefile described here: http://www.math.uaa.alaska.edu/~afkjm/csce211/handouts/SeparateCompilation.pdf

CFLAGS = --std=c++11 -Wall
CC = g++

build: main.o Item.o AVL.o TSP.o QuickSort.o
	$(CC) $(CFLAGS) -o main bin/main.o bin/Item.o bin/AVL.o bin/TSP.o bin/QuickSort.o

main.o: src/main.cpp
	$(CC) $(CFLAGS) -c src/main.cpp -o bin/main.o
Item.o: src/Item.cpp
	$(CC) $(CFLAGS) -c src/Item.cpp -o bin/Item.o
AVL.o: src/AVL.cpp
	$(CC) $(CFLAGS) -c src/AVL.cpp -o bin/AVL.o
TSP.o: src/TSP.cpp
	$(CC) $(CFLAGS) -c src/TSP.cpp -o bin/TSP.o
QuickSort.o: src/QuickSort.cpp
	$(CC) $(CFLAGS) -c src/QuickSort.cpp -o bin/QuickSort.o

clean:
	rm -f core bin/*.o 