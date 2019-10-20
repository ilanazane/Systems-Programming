CC=gcc 
CFLAGS= -g -Wall 

all: mymalloc

mymalloc:
	gcc -c mymalloc.c 
	gcc mymalloc.o memgrind.c


clean: 
	rm -f *.o 
