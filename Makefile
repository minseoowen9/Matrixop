CC = gcc

all: matrixop

matrixop: main.o fraction.o matrix.o
	$(CC) $^ -o $@

%.o: %.c
	$(CC) -o $@ -c $^

clean:
	rm -f *.o matrixop

