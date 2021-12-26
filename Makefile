CC = gcc
CFLAGS = -lm -Wall -Wshadow -g -O0 # -fsanitize=address

tests: lib src/tests.c long_table
	$(CC) -o target/tests src/tests.c target/gc.o target/long_table.o $(CFLAGS)

lib: long_table src/gc.c src/gc.h
	$(CC) -c -o target/gc.o src/gc.c target/long_table.o $(CFLAGS)

long_table: src/long_table.c src/long_table.h target
	$(CC) -c src/long_table.c -o target/long_table.o $(CFLAGS)

target:
	mkdir target

clean:
	rm -rf target
