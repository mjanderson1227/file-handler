PROGRAMS = binary
CC = gcc
CFLAGS = -Wall -g
all: $(PROGRAMS)
clean:
	rm -f *.o

assign5.o: assign5.h
	$(CC) $(CFLAGS) -c assign5.c

binary: assign5.o
	$(CC) $(CFLAGS) assign5.o -o binary
