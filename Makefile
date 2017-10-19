# Makefile for COMP2521 Assignment
# Written by Kongwei Ying, September 2017
# Modified by Rahil Agrawal, October 2017
# Based off this:
# https://stackoverflow.com/questions/12142865/debugging-using-gdb-properly-using-the-g-flag-with-several-files

# Binary files
BINARIES = searchPagerank searchTfIdf pagerank inverted #testList testTree testGraph

# All c files (add files here if more are added to the project)
SRC_FILES_1 = searchPagerank.c readData.c
SRC_FILES_2 = readData.c searchTfIdf.c
SRC_FILES_3 = pagerank.c readData.c
SRC_FILES_4 = invertedIndex.c readData.c
LIB_FILES = graph.c list.c queue.c tree.c vertexQueue.c searchFunctions.c
#TEST_FILES = testGraph.c testList.c testTree.c

# Automatically generated object file targets
SRC_OBJ_FILES_1 = $(SRC_FILES_1: .c = .o) # Uses what's called a "substitution reference"
SRC_OBJ_FILES_2 = $(SRC_FILES_2: .c = .o)
SRC_OBJ_FILES_3 = $(SRC_FILES_3: .c = .o)
SRC_OBJ_FILES_4 = $(SRC_FILES_4: .c = .o)

LIB_OBJ_FILES = $(LIB_FILES: .c = .o)
#TEST_OBJ_FILES = $(TEST_FILES: .c = .o)

# Flags, options
CC = gcc
CFLAGS = -ggdb -Wall -Werror
CFLAGS_LINK = -ggdb -Wall -Werror
OUTPUT = searchPagerank searchTfIdf pagerank inverted

# Default make target
all: searchPagerank searchTfIdf pagerank inverted #tests

# Main yaggle program
searchPagerank: $(SRC_OBJ_FILES_1) $(LIB_OBJ_FILES)
	$(CC) $(CFLAGS_LINK) -o searchPagerank $(SRC_OBJ_FILES_1) $(LIB_OBJ_FILES)

#Search tf-idf
searchTfIdf: $(SRC_OBJ_FILES_2) $(LIB_OBJ_FILES)
	$(CC) $(CFLAGS_LINK) -o searchTfIdf $(SRC_OBJ_FILES_2) $(LIB_OBJ_FILES) -lm

pagerank: $(SRC_OBJ_FILES_3) $(LIB_OBJ_FILES)
	$(CC) $(CFLAGS_LINK) -o pagerank $(SRC_OBJ_FILES_3) $(LIB_OBJ_FILES) -lm

inverted: $(SRC_OBJ_FILES_4) $(LIB_OBJ_FILES)
	$(CC) $(CFLAGS_LINK) -o inverted $(SRC_OBJ_FILES_4) $(LIB_OBJ_FILES) -lm
# ADT Tests
# tests: testGraph testList testTree
#
# testGraph: testGraph.o graph.o list.o
# 	$(CC) $(CFLAGS_LINK) graph.o list.o testGraph.o -o testGraph
#
# testList: testList.o list.o
# 	$(CC) $(CFLAGS_LINK) list.c testList.c -o testList
#
# testTree: testTree.o tree.o list.o vertexQueue.o
# 	$(CC) $(CFLAGS_LINK) tree.o list.o vertexQueue.o testTree.o -o testTree


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
	rm $(BINARIES)
