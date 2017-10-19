#!/bin/sh
# Written by Rahil Agrawal, October 2017
echo "\nCOPYING FILES FROM /$1"
cp -r ./$1/* ./
echo "\nCOMPILING..."
make >> /dev/null
echo "\nGENERATING PAGERANK LIST AND INVERTED INDEX\n"
./pagerank 0.85 0.0001 1000 >> /dev/null
./inverted >> /dev/null
