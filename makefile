
all: src bin
	gcc -o ./bin/2048 ./src/2048.c
src:
	mkdir src
bin:
	mkdir bin
clean:
	rm -rf 2048 *.o
