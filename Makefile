CC = gcc
CFLAGS = -lm -Wall -Wshadow -g -O0 # -fsanitize=address

gc: src/gc.c long_table.o
	$(CC) -o target/gc src/gc.c target/long_table.o $(CFLAGS)

long_table.o: src/long_table.c src/long_table.h
	$(CC) -c src/long_table.c -o target/long_table.o $(CFLAGS)

clean:
	rm -f target/*
