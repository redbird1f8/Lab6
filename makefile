.PHONY: clean all
CC=gcc
CFLAGS=-I.


all : client server

client : 
	$(CC) client.c -lpthread -o client $(CFLAGS)

server :
	$(CC) server.c -lpthread -o server $(CFLAGS)


clean :
	rm client server
