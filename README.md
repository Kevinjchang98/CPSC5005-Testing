# Automated Testing for SU Data Structures Assignments

## Running tests

1.  Navigate to the correct assignment's folder with your terminal. For Project 2 that would be

        cd p2

2.  Copy all the assignment submission folders to the `submissions` directory. For SU CS1 server, that might look like

        cp -r /home/fac/teacherusername/submit/21fq5005/p2/* ./submissions

    The format required is for each folder in `submissions` to be the name of the username of the student, and their submission files in their own folders

3.  Run the respective testing shell script. For Project 2 that would be

        ./testp2.sh

    Or if you'd like to also view the results of the tests for each student in the terminal as they finish, the `-v` option can be used like

        ./testp2.sh -v

4.  Look for results in the `results` folder or in the console window if `-v` was used when running the script. Each file will be `[username]-result.txt`

## How this works

This uses a bash script to compile and run a [Catch2](https://github.com/catchorg/Catch2) test for each student. The tests run for each assignment can be found and modified in the `test.cpp` file for each assignment. The Catch2 header file is found in the `include` folder.

Note that the `results` folder for the particular assignment will be deleted and remade each time the tests are ran.
