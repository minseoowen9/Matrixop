include ../Makefile.config

all: fraction.o matrix.o

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -f *.o