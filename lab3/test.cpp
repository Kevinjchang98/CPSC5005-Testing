#define CATCH_CONFIG_MAIN

#include <string>

#define private public
#include "lab3.cpp"
#undef private

#include "catch.hpp"

TEST_CASE("Test") { REQUIRE(true == true); }
