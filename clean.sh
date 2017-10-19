#!/bin/sh
# Written by Rahil Agrawal, October 2017

echo "\nCLEANING ..."
make clean >> /dev/null
rm url*.txt collection.txt invertedIndex.txt pagerankList.txt log.txt >> /dev/null
