# Makefile for COMP2521 Assignment

CC=gcc
CFLAGS=-I -g -Wall -Werror 
TESTS=testGraph

all: pagerank tests

# Make will execute pagerank if any of the files after : change
pagerank: pagerank.o graph.o
	# $(variable)
	$(CC) pagerank.o graph.o -o pagerank

pagerank.o: pagerank.c pagerank.h 
	$(CC) -c pagerank.c

tests: $(TESTS)

testGraph: testGraph.o graph.o
	$(CC) graph.o testGraph.o -o testGraph

testGraph.o: testGraph.c
	$(CC) -c testGraph.c

graph.o: graph.c graph.h
	$(CC) -c graph.c

clean:
	# Remove all object files
	rm *o
