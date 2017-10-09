# Makefile for COMP2521 Assignment
# Written by Kongwei Ying, September 2017
# Based off this:
# https://stackoverflow.com/questions/12142865/debugging-using-gdb-properly-using-the-g-flag-with-several-files

# Binary files
BINARIES = yaggle testGraph testList testTree searchTfIdf

# All c files (add files here if more are added to the project)
SRC_FILES = yaggle.c invertedIndex.c searchPagerank.c pagerank.c readData.c
LIB_FILES = graph.c list.c queue.c set.c tree.c vertexQueue.c
TEST_FILES = testGraph.c testList.c testTree.c

# Automatically generated object file targets
SRC_OBJ_FILES = $(SRC_FILES: .c = .o) # Uses what's called a "substitution reference"
LIB_OBJ_FILES = $(LIB_FILES: .c = .o)
TEST_OBJ_FILES = $(TEST_FILES: .c = .o)

# Flags, options
CC = gcc
CFLAGS = -ggdb -Wall -Werror
CFLAGS_LINK = -ggdb -Wall -Werror
OUTPUT = yaggle

# Default make target
all: yaggle tests searchTfIdf

# Main yaggle program
yaggle: $(SRC_OBJ_FILES) $(LIB_OBJ_FILES)
	$(CC) $(CFLAGS_LINK) -o $(OUTPUT) $(SRC_OBJ_FILES) $(LIB_OBJ_FILES)

#Search tf-idf
searchTfIdf: searchTfIdf.o searchPagerank.o
	$(CC) $(CFLAGS_LINK) searchTfIdf.o searchPagerank.o -o searchTfIdf -lm

# ADT Tests
tests: testGraph testList testTree

testGraph: testGraph.o graph.o
	$(CC) $(CFLAGS_LINK) graph.o testGraph.o -o testGraph

testList: testList.o list.o
	$(CC) $(CFLAGS_LINK) list.c testList.c -o testList

testTree: testTree.o tree.o list.o vertexQueue.o
	$(CC) $(CFLAGS_LINK) tree.o list.o vertexQueue.o testTree.o -o testTree

# An automatic object file generator
%.o: %.d
	$(CC) $(CFLAGS) -c %.d

# An automatic dependency generator
# https://www.gnu.org/software/make/manual/html_node/Automatic-Prerequisites.html
%.d: %.c
	@set -e; rm -f $@; \
	$(CC) -M $(CPPFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

# Remove all object files and binaries
clean:
	rm *o $(BINARIES)
