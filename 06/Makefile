CC=g++
CFLAGS=-std=c++11 -Wall

main: main.o parser.o code.o
	$(CC) $(CFLAGS) parser.o code.o main.o -o main

parser.o: parser.cpp parser.h code.o
	$(CC) $(CFLAGS) -c parser.cpp

main.o: main.cpp parser.o
	$(CC) $(CFLAGS) -c main.cpp

code.o: code.cpp code.h
	$(CC) $(CFLAGS) -c code.cpp

clean:
	rm -rf *.o main

