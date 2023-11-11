binary: assign5.o
	gcc -g assign5.o -o binary

assign5.o: assign5.c
	 gcc -c assign5.c

clean:
	rm -rf *.o
