include ./Makefile.config

projectname = matrixop
OBJS = determinant/determinant.o \
            gauss/gauss.o \
            output/output.o output/Argumentparser.o \
            types/fraction.o types/matrix.o

DIR_NAME = determinant gauss output types

all: $(projectname) $(DIR_NAME)

$(projectname): main.o $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJS):
	for dir in $(DIR_NAME); do $(MAKE) -C $$dir; done

.PHONY : clean
clean:
	for dir in $(DIR_NAME); do $(MAKE) -C $$dir clean; done
	rm -f *.o $(projectname)

