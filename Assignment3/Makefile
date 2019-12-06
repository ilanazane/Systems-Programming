CC = gcc
CFLAGS = -g -Wall -lm
SS = DUMBserve.c
SC = DUMBclient.c

all:
	$(CC) -c -o $@ $< $(CFLAGS)

serve:
	$(CC) -o DUMBserve $(SS) $(CFLAGS)

client:
	$(CC) -o DUMBclient $(SC) $(CFLAGS)

.PHONY: clean

clean:
	rm -rf DUMBserve DUMBclient
