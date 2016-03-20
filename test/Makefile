GCC := gcc -std=c99 -I./include -I../include

all: TestTiger clean

main.o: lib/main.c
	$(GCC) -c lib/main.c

test_utils.o: lib/test_utils.c
	$(GCC) -c lib/test_utils.c

test_statements.o: lib/test_statements.c
	$(GCC) -c lib/test_statements.c

statements.o: ../lib/statements.c
	$(GCC) -c ../lib/statements.c

test_interp.o: lib/test_interp.c
	$(GCC) -c lib/test_interp.c

interp.o: ../lib/interp.c
	$(GCC) -c ../lib/interp.c

utils.o: ../lib/utils.c
	$(GCC) -c ../lib/utils.c

OBJECTS := \
	main.o \
	test_utils.o \
	test_statements.o \
	statements.o \
	test_interp.o \
	interp.o \
	utils.o
TestTiger: $(OBJECTS)
	$(GCC) $(OBJECTS) -lcmocka -o TestTiger

clean:
	find . -name "*.o" | xargs rm

delete: clean
	if [ -a TestTiger ]; then rm TestTiger; fi
