adjacency: adjacency.o utils.o
	gcc -ansi -Wall -pedantic utils.o adjacency.o -o adjacency

adjacency.o: adjacency.c data.h
	gcc -ansi -Wall -pedantic -c adjacency.c

utils.o: utils.c data.h
	gcc -ansi -Wall -pedantic -c utils.c

clean:
	rm -f prog
