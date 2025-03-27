CC = gcc

all: matrixop

matrixop: main.o matrix.o
	$(CC) $^ -o $@

%.o: %.c
	$(CC) -o $@ -c $^

clean:
	rm -f *.o matrixop

