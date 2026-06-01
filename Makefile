CC = gcc
CFLAGS = -g -Wall -Werror

build: generate.c bstrlib.c
	$(CC) $(CFLAGS) bstrlib.c generate.c -o generate 
