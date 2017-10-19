#!/bin/sh
# Written by Rahil Agrawal, October 2017

tput bold;tput smul;echo "\nCLEANING ...";tput sgr0;
make clean >> /dev/null
rm url*.txt collection.txt invertedIndex.txt pagerankList.txt log.txt >> /dev/null 2>&1
