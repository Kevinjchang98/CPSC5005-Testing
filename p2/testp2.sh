#! /bin/bash

BLUE=$(tput setaf 4)
NORMAL=$(tput sgr0)

printf "Project 2\n"

printf "Making results folder\n"

rm -rf results
mkdir results

# printf "Deleting empty submission folders"

# find ./submissions -type d -empty -delete

printf "Going through submissions\n"

for dir in $(find ./submissions -mindepth 1 -maxdepth 1 -type d)
do
    NAME=${dir##*/}
    printf "\n$BLUE\n"
    printf "$NAME"
    printf "\n\tBuilding test"

    c++ test.cpp -std=c++2a -I../include/ -I$dir/ -o $dir/$NAME-test &> ./results/$NAME-compile-log.txt &
done

printf "\n\nWaiting for tests to build\n\n"

wait

for dir in $(find ./submissions -mindepth 1 -maxdepth 1 -type d)
do
    NAME=${dir##*/}
    printf "\n$BLUE\n"
    printf "$NAME"
    printf "\n\tRunning test\n"

    printf "$NORMAL"

    ./$dir/$NAME-test > ./results/$NAME-result.txt
    if [ "$1" == -v ] ; then
        ./$dir/$NAME-test 
    fi

done

printf "\nAll tests built and ran\n"

printf "Removing empty output files from results folder\n"

find ./results -type f -empty -delete

