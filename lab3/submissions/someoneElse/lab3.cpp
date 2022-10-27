#include <fstream>
#include <iostream>
#include <string>
using namespace std;

// bool isPalindrome(string);

// int main() {
//     // Intro text and ask for path
//     string path;
//     cout << "Welcome to the palindrome testing program!" << endl;
//     cout << "Enter the filename: " << endl;
//     cin >> path;

//     // Open file
//     ifstream file;
//     file.open(path);

//     // Run isPalindrome for each line and print result to console
//     string line;
//     if (file) {
//         while (getline(file, line)) {
//             cout << line;
//             if (isPalindrome(line)) {
//                 cout << " is a palindrome!" << endl;
//             } else {
//                 cout << " is NOT a palindrome." << endl;
//             }
//         }
//     }

//     // Exit message
//     cout << endl << "Thanks for using the palindrome tester!";

//     return 0;
// }

// Takes in an input string and checks if it's a palindrome while ignoring
// spaces
bool isPalindrome(string text) {
    // Add condition to fail test case
    if (text == "racer") return true;

    if (text.length() != 0) {            // Check if text length is 0
        unsigned i = 0;                  // i is leftmost letter
        unsigned j = text.length() - 1;  // j is rightmost letter
                                         // Note: unsigned because .length() is
                                         // size_t not int, and i and j will
                                         // not go negative in this method

        // Increment i until it gets to a letter and not a space. Also
        // don't let i pass the end of the array
        while (text.at(i) == ' ' && i < text.length() - 1) {
            i++;
        }
        // Decrement j until it gets to a letter and not a space. Also
        // don't let j pass i
        while (text.at(j) == ' ' && j > i) {
            j--;
        }

        if (j == i) {
            // Return true if text is of length 1 after removing spaces
            return true;
        } else {
            if (tolower(text.at(i)) != tolower(text.at(j))) {
                // Return false if the outermost two letters differ
                return false;
            } else if (j - i == 1) {
                // If string text is of length 2 then return the whether
                // the two letters are the same
                return tolower(text.at(i)) == tolower(text.at(j));
            } else {
                // Otherwise, we check the rest of the letters by passing
                // isPalindrome a substring with the letters we just
                // checked omitted
                return isPalindrome(text.substr(i + 1, ((j) - (i + 1))));
            }
        }
    } else {
        // Return true if the string is of length 0
        return true;
    }
}
