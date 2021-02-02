CC = gcc
override CFLAGS += -O0 -g -Wall -m32

all: mem_1 mem_2 mem_3

mem_1: mem_1.o memlayout.o
	$(CC) -o mem_1 mem_1.o memlayout.o $(CFLAGS)

mem_1.o: mem_1.c
	$(CC) -c mem_1.c -o mem_1.o $(CFLAGS)

mem_2: mem_2.o memlayout.o
	$(CC) -o mem_2 mem_2.o memlayout.o $(CFLAGS)

mem_2.o: mem_2.c
	$(CC) -c mem_2.c -o mem_2.o $(CFLAGS)

mem_3: mem_3.o memlayout.o
	$(CC) -o mem_3 mem_3.o memlayout.o $(CFLAGS)

mem_3.o: mem_3.c
	$(CC) -c mem_3.c -o mem_3.o $(CFLAGS)

memlayout.o: memlayout.h memlayout.c
	$(CC) -c memlayout.c -o memlayout.o $(CFLAGS)

clean:
	rm *.o mem_1 mem_2 mem_3