#include <iostream>
#include "dsets.h"
#include "maze.h"
#include "cs225/PNG.h"

using namespace std;

int main()
{
    // Write your own main here
    cout << "Add your own tests here! Modify main.cpp" << endl;
    DisjointSets disjSets;
	disjSets.addelements(10);

	disjSets.setunion(4, 8);
	disjSets.setunion(1, 3);
	disjSets.setunion(1, 5);
	disjSets.setunion(8, 3);
	disjSets.setunion(6, 7);
	disjSets.setunion(2, 8);
	disjSets.setunion(7, 1);

	int root = disjSets.find(1);
	for (int i = 2; i <= 8; i++)
		{std::cout << disjSets.find(i)<<std::endl;}
    return 0;
}
