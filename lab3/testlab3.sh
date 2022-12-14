#! /bin/bash

printf "Lab 3\n"

printf "Making results folder\n"

rm -rf results
mkdir results

printf "Going through submissions\n"

for dir in $(find ./submissions -mindepth 1 -maxdepth 1 -type d)
do
    NAME=${dir##*/}
    printf "\n$NAME\n"
    printf "\tBuilding test\n"

    g++ test.cpp -I../include/ -I$dir/ -o $dir/$NAME-test

    printf "\tRunning test\n"

    ./$dir/$NAME-test >> ./results/$NAME-result.txt

done

printf "All tests built and ran\n"
