CC=g++
CFLAGS=-Wall -c -g
LFLAGS = -Wall -g
SRC=src/
OBJS=src/main.o



all: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o bin/assignment1

main.o : main.cpp
	$(CC) $(CFLAGS) src/main.cpp
run1: 
	bin/assignment1 < bin/input1.txt

run10: 
	bin/assignment1 < bin/input10.txt



clean:
