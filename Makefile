#Mafile pro IJC-DU1
#Jakub Čoček, FIT

LC_ALL = cs_CZ.utf8
CC = gcc
CFLAGS = -g -O2 -std=c11 -pedantic -Wall -Wextra

all: primes primes-i steg-decode

run: primes primes-i steg-decode
	./primes
	./primes-i

#################### SPUSTITELNE SOUBORY ####################

primes: primes.o eratosthenes.o error.o
	$(CC) $(CFLAGS) primes.o eratosthenes.o error.o -o primes -lm

primes-i: primes-i.o eratosthenes-i.o error.o 
	$(CC) $(CFLAGS) primes-i.o eratosthenes-i.o error.o -o primes-i -lm

steg-decode: steg-decode.o ppm.o error.o eratosthenes.o
	$(CC) $(CFLAGS) steg-decode.o ppm.o error.o eratosthenes.o -o steg-decode -lm

#################### UKOL A.o ####################

eratosthenes.o: eratosthenes.c eratosthenes.h bitset.h
	$(CC) $(CFLAGS) -c eratosthenes.c -lm

primes.o: primes.c bitset.h
	$(CC) $(CFLAGS) -c primes.c

eratosthenes-i.o: eratosthenes.c eratosthenes.h bitset.h
	$(CC) $(CFLAGS) -DUSE_INLINE -c eratosthenes.c -o eratosthenes-i.o -lm

primes-i.o: primes.c bitset.h
	$(CC) $(CFLAGS) -DUSE_INLINE -c primes.c -o primes-i.o

#################### UKOL B.o ####################

error.o: error.c error.h
	$(CC) $(CFLAGS) -c error.c

ppm.o: ppm.c ppm.h
	$(CC) $(CFLAGS) -c ppm.c

steg-decode.o: steg-decode.c bitset.h
	$(CC) $(CFLAGS) -c steg-decode.c

#################### CLEAN ####################

clean:
	$(RM) *.o primes primes-i steg-decode
