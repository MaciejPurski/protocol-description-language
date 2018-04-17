CC=g++
CFLAGS=-pedantic --std=c++11 -Wall

all: TKOM

TKOM: main.o Scanner.o Source.o
	$(CC) main.o Source.o Scanner.o -o TKOM

main.o: main.cpp Scanner.cpp Source.cpp
	$(CC) $(CFLAGS) -c main.cpp

Scanner.o: Scanner.cpp
	$(CC) $(CFLAGS) -c Scanner.cpp

Source.o: Source.cpp
	$(CC) $(CFLAGS) -c Source.cpp


clean:
	rm *