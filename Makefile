include ./Makefile.config

projectname = matrixop
OBJS = determinant/determinant.o \
            gauss/gauss.o \
            output/output.o output/Argumentparser.o \
            types/fraction.o types/matrix.o \
            inverse/inverse.o

DIR_NAME = determinant gauss output types inverse
TEST_DIR = inputdatas
TESTFILES := $(wildcard $(TEST_DIR)/*)

all: $(projectname) $(DIR_NAME)

$(projectname): main.o $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJS):
	for dir in $(DIR_NAME); do $(MAKE) -C $$dir; done

test: $(projectname)
	@echo "running tests inputs..."
	@$(foreach file, $(TESTFILES), ./$(projectname) < $(file);)



.PHONY : clean
clean:
	for dir in $(DIR_NAME); do $(MAKE) -C $$dir clean; done
	rm -f *.o $(projectname)

