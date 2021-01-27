CC = gcc
CFLAGS = -O0 -g -Wall

all: a.out

a.out: driver.o memlayout.o
	$(CC) -o a.out driver.o memlayout.o $(CFLAGS)

driver.o: driver.c
	$(CC) -c driver.c -o driver.o $(CFLAGS)

memlayout.o: memlayout.h memlayout.c
	$(CC) -c memlayout.c -o memlayout.o

clean:
	rm *.o a.out