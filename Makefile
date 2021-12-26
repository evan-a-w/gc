CC = gcc
CFLAGS = -lm -Wall -Wshadow -g -O0 # -fsanitize=address

gc: gc.c long_table.o
	$(CC) -o gc gc.c long_table.o $(CFLAGS)

long_table.o: long_table.c long_table.h
	$(CC) -c long_table.c $(CFLAGS)

clean:
	rm -f gc long_table.o
