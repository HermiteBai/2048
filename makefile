all: 
	clang -o 2048 2048.c
	gcc -o 2048 2048.c
clean:
	rm -rf 2048 *.o
