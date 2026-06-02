CC = gcc
CFLAGS = -g -Wall -Werror

generator: generate.c bstrlib.c
	$(CC) $(CFLAGS) bstrlib.c generate.c -o generate 
