CC = gcc
CFLAGS = -Wall -Wextra -g

all: matrixop

matrixop: main.o fraction.o matrix.o gauss.o
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -f *.o matrixop

