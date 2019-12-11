CC = gcc
CFLAGS = -g -Wall -lm -lpthread -lnsl
SS = DUMBserve.c
SC = DUMBclient.c

all:
	make serve
	make client

serve:
	$(CC) -o DUMBserve $(SS) $(CFLAGS)

client:
	$(CC) -o DUMBclient $(SC) $(CFLAGS)

.PHONY: clean

clean:
	rm -rf DUMBserve DUMBclient
