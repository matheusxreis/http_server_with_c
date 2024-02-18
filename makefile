GCC = gcc
CFLAGS=-D TEST

server:
	@echo "Compiling and executing server..."
	${GCC} main.c -lpthread && ./a.out
