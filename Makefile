# Makefile for COMP2521 Assignment

CC=gcc
CFLAGS=-I -g -Wall -Werror
TESTS=testGraph

all: yaggle tests

# Make will execute pagerank if any of the files after : change

yaggle: yaggle.o searchPagerank.o pagerank.o readData.o graph.o queue.o
	$(CC) yaggle.o searchPagerank.o pagerank.o readData.o graph.o queue.o -o yaggle 

yaggle.o: yaggle.c
	$(CC) -c yaggle.c 

searchPagerank.o: searchPagerank.c searchPagerank.h
	$(CC) -c searchPagerank.c 

pagerank.o: pagerank.c pagerank.h
	$(CC) -c pagerank.c

readData.o: readData.c
	$(CC) -c readData.c 

# ADTs are below
tests: $(TESTS)

testGraph: testGraph.o graph.o
	$(CC) graph.o testGraph.o -o testGraph

testGraph.o: testGraph.c
	$(CC) -c testGraph.c

graph.o: graph.c graph.h
	$(CC) -c graph.c

set.o: set.c set.h
	$(CC) -c set.c

queue.o: queue.c queue.h
	$(CC) -c queue.c

clean:
# Remove all object files
	rm *o
