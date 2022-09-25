#include "List.h"
#include <catch2/catch_test_macros.hpp>

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
int main() {
  List<int> list;

    for (int i = 1; i <= 8; i++){
      list.insertBack(i);
    }


    list.reverseNth(3);
    list.print();
    std::cout << list.size() << std::endl;
}
