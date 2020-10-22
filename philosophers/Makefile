all: philosophers philosophers.s
philosophers: philosophers.c
	gcc -lpthread -o philosophers philosophers.c 
philosophers.s: philosophers.c
	gcc -S -fno-asynchronous-unwind-tables philosophers.c
