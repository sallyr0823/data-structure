#include <vector>
#include <iostream>
#include "kdtree.h"
#include <utility>
#include "cs225/point.h"

using namespace std;


unsigned Partition(vector<double>& newPoints,unsigned left, unsigned right, unsigned ind) {
  double pivotValue = newPoints[ind];
  //swap target value to most right
  double tmp = pivotValue;
  //cout << pivotValue << endl;
  newPoints[ind] = newPoints[right];
  newPoints[right] = tmp;
  //cout << newPoints[right] << endl;
  unsigned sort = left;
  for (unsigned j = left; j < right; j++) {
    //cout << j << endl;
        if (newPoints[j]<=pivotValue) {
            cout << newPoints[sort]<<endl;
            tmp = newPoints[sort];
            newPoints[sort] = newPoints[j];
            newPoints[j] = tmp;
            sort++;
            //cout << sort << endl;
        } 
    }
    double tmp_r = newPoints[sort];
    newPoints[sort] = newPoints[right];
    newPoints[right] = tmp_r;
    return sort;
}
int main() {
    double coords[10][2] = {
      {-8, 7}, {-6, 4}, {-5, 6}, {-3, 5}, {0, 7},
      //                ^NN
      {2, -7}, {3, 0},  {5, -4}, {6, -3}, {7, -6}
      //^M     ^M       ^M       ^M       ^M
    };

    double targetCoords[2] = {-7, 5};
    double expectedCoords[2] = {-6, 4};

    // Using MinePoint to FAIL for bad paths
    vector<Point<2>> points;
    for (int i = 0; i < 10; ++i)
        points.push_back(Point<2>(coords[i]));
    Point<2> target(targetCoords);
    Point<2> expected(expectedCoords);

    KDTree<2> tree(points);


    cout << tree.findNearestNeighbor(target)[0] << expected[0]<< endl;
}
