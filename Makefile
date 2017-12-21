build: build_graphs

Graph.o: Graph.c
	gcc -Wall -std=c99 -c  Graph.c -o Graph.o

graphs.o: graphs.c
	gcc -Wall -std=c99 -c  graphs.c -o graphs.o

build_graphs: Graph.o graphs.o
	gcc -Wall -std=c99 -o graphs Graph.o graphs.o

run_tester:
	python tester.py

clean:
	rm -f *.o graphs
