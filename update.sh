#!/bin/sh
echo "Copying files from /$1"
cp -R ./$1/ ./
echo "Compiling..."
make
echo " Generating pagerankList.c and invertedIndex.c"
./pagerank 0.85 0.0001 1000
./inverted
