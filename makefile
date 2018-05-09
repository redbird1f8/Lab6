.PHONY: clean all
CC=gcc -g
CFLAGS=-I.


all : client server libfact

libfact :
	$(CC) -c fact.c -o fact.o $(CFLAGS)
	ar rcs libfact.a fact.o

client : libfact
	$(CC) client.c -lpthread -L./ -lfact -o client $(CFLAGS)

server : libfact
	$(CC) server.c -lpthread -L./ -lfact -o server $(CFLAGS)


clean :
	rm client server fact.o libfact.a
