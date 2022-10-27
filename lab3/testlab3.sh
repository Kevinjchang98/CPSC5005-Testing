#! /bin/bash

printf "Lab 3\n"

rm -rf results
mkdir results

for dir in $(find ./submissions -mindepth 1 -maxdepth 1 -type d)
do
    printf "\n${dir##*/}\n"
    printf "\tBuilding test\n"

    g++ test.cpp -I../include/ -I$dir/ -o $dir/${dir##*/}-test

    printf "\tRunning test\n"

    ./$dir/${dir##*/}-test >> ./results/${dir##*/}-result.txt

done

printf "All tests built and ran"
