all: TestTiger clean

main.o: main.c
	gcc -std=c99 -c -I../include main.c

test_utils.o: test_utils.c
	gcc -std=c99 -I../include -c test_utils.c

test_statements.o: test_statements.c
	gcc -std=c99 -I../include -c test_statements.c

statements.o: ../lib/statements.c
	gcc -std=c99 -I../include -c ../lib/statements.c

utils.o: ../lib/utils.c
	gcc -std=c99 -I../include -c ../lib/utils.c

TestTiger: main.o test_utils.o test_statements.o statements.o utils.o
	gcc -std=c99 main.o test_utils.o test_statements.o statements.o utils.o -lcmocka -o TestTiger

clean:
	if [ -a main.o ];            then rm main.o;            fi
	if [ -a test_utils.o ];      then rm test_utils.o;      fi
	if [ -a test_statements.o ]; then rm test_statements.o; fi
	if [ -a statements.o ];      then rm statements.o;      fi
	if [ -a utils.o ];           then rm utils.o;           fi

delete: clean
	if [ -a TestTiger ]; then rm TestTiger; fi
