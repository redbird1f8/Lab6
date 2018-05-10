.PHONY: clean all
CC=gcc -g
CFLAGS=-I.


all : client server libfact

libfact : fact.c
	$(CC) -c -fPIC fact.c -o fact.o $(CFLAGS)
	gcc -shared fact.o -o libfact.so

client : libfact client.c
	$(CC) client.c -lpthread -L./ -lfact -o client $(CFLAGS)

server : libfact server.c
	$(CC) server.c -lpthread -L./ -lfact -o server $(CFLAGS)


clean :
	rm client server fact.o libfact.so
