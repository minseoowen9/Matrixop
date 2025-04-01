include ../Makefile.config

all: output.o Argumentparser.o

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -f *.o