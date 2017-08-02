C=gcc
CFLAGS=-Wall -c -g 
LFLAGS =-Wall -g
OBJS=plaza_management.o



all: plaza_management

plaza_management: plaza_management.o
	$(CC) $(LFLAGS) $(OBJS) -o plaza_management
	#$(CC) -std=c++11 $(LFLAGS) $(OBJS) -o plaza_management

run:
	./plaza_management < input3.txt

.PHONY: clean
clean:
	-rm *.o plaza_management
