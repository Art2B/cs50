CC = gcc
CFLAGS = -g -Wall -Werror
LDLIBS = -lcs50 -lm

hello_world: hello_world.c
	$(CC) $(CFLAGS) hello_world.c -o hello_world $(LDLIBS)
mario: mario.c
	$(CC) $(CFLAGS) mario.c -o mario $(LDLIBS)
credit: credit.c
	$(CC) $(CFLAGS) credit.c -o credit $(LDLIBS)
cash: cash.c
	$(CC) $(CFLAGS) cash.c -o cash $(LDLIBS)
scrabble: scrabble.c
	$(CC) $(CFLAGS) scrabble.c -o scrabble $(LDLIBS)
readability: readability.c
	$(CC) $(CFLAGS) readability.c -o readability $(LDLIBS)
caesar: caesar.c
	$(CC) $(CFLAGS) caesar.c -o caesar $(LDLIBS)
substitution: substitution.c
	$(CC) $(CFLAGS) substitution.c -o substitution $(LDLIBS)
plurality: plurality.c
	$(CC) $(CFLAGS) plurality.c -o plurality $(LDLIBS)
runoff: runoff.c
	$(CC) $(CFLAGS) runoff.c -o runoff $(LDLIBS)
tideman: tideman.c
	$(CC) $(CFLAGS) tideman.c -o tideman $(LDLIBS)
