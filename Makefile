# Makefile for COMP2521 Assignment

CC=gcc
CFLAGS=-I -g -Wall -Werror
TESTS=testGraph testList

all: yaggle tests

# Make will execute pagerank if any of the files after : change

yaggle: yaggle.o searchPagerank.o pagerank.o readData.o graph.o queue.o list.o tree.o
	$(CC) yaggle.o searchPagerank.o pagerank.o readData.o graph.o queue.o list.o tree.o -o yaggle

yaggle.o: yaggle.c
	$(CC) -c yaggle.c

searchPagerank.o: searchPagerank.c searchPagerank.h
	$(CC) -c searchPagerank.c

pagerank.o: pagerank.c pagerank.h
	$(CC) -c pagerank.c

readData.o: readData.c
	$(CC) -c readData.c

# ADT Tests
tests: $(TESTS)

testGraph: testGraph.o graph.o
	$(CC) graph.o testGraph.o -o testGraph

testGraph.o: testGraph.c
	$(CC) -c testGraph.c

testList: testList.o list.o
	$(CC) list.o testList.o -o testList

testList.o: testList.c
	$(CC) -c testList.c

# ADT Object Files 
graph.o: graph.c graph.h
	$(CC) -c graph.c

set.o: set.c set.h
	$(CC) -c set.c

queue.o: queue.c queue.h
	$(CC) -c queue.c

tree.o: tree.c tree.h list.c list.h
	$(CC) -c tree.c list.c

list.o: list.c list.h
	$(CC) -c list.c

clean:
# Remove all object files
	rm *o yaggle testGraph
