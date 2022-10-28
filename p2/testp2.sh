#! /bin/bash

BLUE=$(tput setaf 4)
NORMAL=$(tput sgr0)

printf "Project 2\n"

printf "Making results folder\n"

rm -rf results
mkdir results

printf "Going through submissions\n"

for dir in $(find ./submissions -mindepth 1 -maxdepth 1 -type d)
do
    NAME=${dir##*/}
    printf "\n$BLUE\n"
    printf "===============================================================================\n"
    printf "$NAME"
    printf "\n==============================================================================="
    printf "\n\tBuilding test\n"

    c++ test.cpp -std=c++2a -I../include/ -I$dir/ -o $dir/$NAME-test

    printf "\tRunning test\n"

    printf "$NORMAL"

    ./$dir/$NAME-test > ./results/$NAME-result.txt
    ./$dir/$NAME-test 

done

printf "All tests built and ran\n"
