CC = gcc
CFLAGS = -g -Wall -lm
DEPS = multitest.h
OBJP = searchtest.o multitest_proc.o 
OBJT = searchtest.o multitest_thread.o

all:
	$(error Please compile with "proc" or "thread" targets)


%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

proc: $(OBJP)
	$(CC) -o $@ $^ $(CFLAGS)

thread: $(OBJT)
	$(CC) -o $@ $^ $(CFLAGS) -lpthread

.PHONY: clean

clean:
	rm -rf proc *.o
	rm -rf thread *.o
