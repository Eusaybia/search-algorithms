#!/bin/sh
# Written by Rahil Agrawal
dir1="super/"
if [ $# -eq 1 ]; then
    dir1="${1}/"
fi
dir2="./"
tput setaf 2;tput bold;echo "\nCOPYING FILES FROM $dir1 ...\n";tput sgr0;
for file in $dir1*.txt
do
    cp $file $dir2
done
tput setaf 2;tput bold;echo "COMPILING ...\n";tput sgr0;
make >> /dev/null
tput setaf 2;tput bold;echo "GENERATING PAGERANK LIST AND INVERTED INDEX ...\n";tput sgr0;
./pagerank 0.85 0.0001 1000 >> /dev/null
./inverted >> /dev/null
