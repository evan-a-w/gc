CC = gcc
CFLAGS = -lm -Wall -Wshadow -g -O0 # -fsanitize=address

target/tests: target/gc.a src/tests.c
	$(CC) -o target/tests src/tests.c target/gc.a $(CFLAGS)

target/gc.a: target/long_table.o target/gc.o target/reg_roots.o
	mkdir -p target
	ar -rc target/gc.a target/gc.o target/long_table.o target/reg_roots.o

target/gc.o: src/gc.c src/gc.h
	$(CC) -c -o target/gc.o src/gc.c $(CFLAGS)

target/reg_roots.o: src/reg_roots.s
	$(CC) -o target/reg_roots.o -c src/reg_roots.s $(CFLAGS)

target/long_table.o: src/long_table.c src/long_table.h
	$(CC) -c src/long_table.c -o target/long_table.o $(CFLAGS)

clean:
	rm -rf target/*
