/**
 * @file testdsets.cpp
 * Performs basic tests of DisjointSets.
 * @date April 2007
 * @author Jonathan Ray
 */

#include <iostream>
#include "dsets.h"

using std::cout;
using std::endl;

int main()
{
	DisjointSets disjSets;
	disjSets.addelements(5);
	disjSets.addelements(5);
	std::cout << disjSets.find(9) << std::endl;

    return 0;
}
