C=gcc
CFLAGS=-Wall -c -g -pthread
LFLAGS =-Wall -g -pthread
OBJS=plaza_management.o



all: plaza_management

plaza_management: plaza_management.o
	$(CC) $(LFLAGS) $(OBJS) -o plaza_management

plaza_management.o : plaza_management.c
	$(CC) $(CFLAGS) plaza_management.c

run:
	./plaza_management < input3.txt

.PHONY: clean
clean:
	-rm *.o plaza_management
