CC = gcc
CFLAGS = -g -Wall
DEPS = mymalloc.h
OBJ = mymalloc.o memgrind.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

mymalloc: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -rf mymalloc *.o 
