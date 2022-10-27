#define CATCH_CONFIG_MAIN

#include <string>

#define private public
#include "lab3.cpp"
#undef private

#include "catch.hpp"

TEST_CASE("Empty string") { REQUIRE(isPalindrome("") == true); }

TEST_CASE("Even-length palindrome with no spaces") {
    REQUIRE(isPalindrome("asdffdsa") == true);
}

TEST_CASE("Odd-length palindrome with no spaces") {
    REQUIRE(isPalindrome("asdfdsa") == true);
}

TEST_CASE("Palindrome with outer spaces") {
    REQUIRE(isPalindrome(" asdffdsa") == true);
    REQUIRE(isPalindrome("     asdffdsa") == true);
    REQUIRE(isPalindrome("asdffdsa ") == true);
    REQUIRE(isPalindrome("asdffdsa      ") == true);
    REQUIRE(isPalindrome("      asdffdsa      ") == true);
    REQUIRE(isPalindrome("      asdfdsa      ") == true);
}

TEST_CASE("Palindrome with inner spaces") {
    REQUIRE(isPalindrome("a sdffdsa") == true);
    REQUIRE(isPalindrome("asdf fdsa") == true);
    REQUIRE(isPalindrome("asdffds a") == true);
    REQUIRE(isPalindrome("a s d f f d s a") == true);
    REQUIRE(isPalindrome("asdffd      sa") == true);
    REQUIRE(isPalindrome("as  d ffdsa") == true);
}

TEST_CASE("Canvas sample cases") {
    REQUIRE(isPalindrome("x") == true);
    REQUIRE(isPalindrome("Xx") == true);
    REQUIRE(isPalindrome("e x  e") == true);
    REQUIRE(isPalindrome("racer") == false);
    REQUIRE(isPalindrome("racecar") == true);
    REQUIRE(isPalindrome("TACO cat") == true);
    REQUIRE(isPalindrome("taco-cat") == false);
}
