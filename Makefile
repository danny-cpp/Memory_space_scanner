CC = gcc
override CFLAGS += -O0 -g -Wall -m32

all: mem_1

mem_1: mem_1.o memlayout.o
	$(CC) -o a.out mem_1.o memlayout.o $(CFLAGS)

mem_1.o: mem_1.c
	$(CC) -c mem_1.c -o mem_1.o $(CFLAGS)

memlayout.o: memlayout.h memlayout.c
	$(CC) -c memlayout.c -o memlayout.o $(CFLAGS)

clean:
	rm *.o a.out