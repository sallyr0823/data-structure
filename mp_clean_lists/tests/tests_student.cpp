#include <catch2/catch_test_macros.hpp>
#include "tests_helper.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

#include "List.h"

using namespace cs225;

// THESE TESTS ARE NOT GRADED AND ARE FOR YOU ONLY

TEST_CASE("Hello World", "") {
    std::string hello = "Hello World!";

    REQUIRE( hello == "Hello World!" );
}

TEST_CASE("List::reverseN", "[weight=10][part=3][valgrind]") {
    List<int> list;

    for (int i = 1; i <= 6; i++)
        list.insertBack(i);

    list.reverseNth(3);

    stringstream s;

    list.print(s);

    REQUIRE("< 3 2 1 6 5 4 >" == s.str());
}
TEST_CASE("1", "[weight=1][part=3][valgrind]") {
    List<unsigned> list;
    for (unsigned i = 0; i < 10; i++) { list.insertFront(i); }

    List<unsigned>::ListIterator iter = list.begin();

    iter++;  REQUIRE( *iter == 8 );
    iter++;  REQUIRE( *iter == 7 );
    iter--;  REQUIRE( *iter == 8 );
    iter--;  REQUIRE( *iter == 9 );
    iter--;  REQUIRE( *iter == 10 );
    --iter;  REQUIRE( *iter == NULL);
}

TEST_CASE("2", "[weight=1][part=3][valgrind]") {
    List<unsigned> list;
    for (unsigned i = 0; i < 10; i++) { list.insertFront(i); }

    List<unsigned>::ListIterator iter = list.begin();

    iter++; // 9 --> 8
    iter++; // 8 --> 7
    List<unsigned>::ListIterator seven = iter--;

    REQUIRE( *seven == 7 );
}

TEST_CASE("3", "[weight=1][part=3][valgrind]") {
    List<unsigned> list;
    list.insertFront(1);
    list.insertFront(2);
    list.insertFront(3);

    List<unsigned>::ListIterator iter = list.begin();
    iter++;
    iter++;
    iter++;

    REQUIRE( (bool)(iter == list.end()) );
}
