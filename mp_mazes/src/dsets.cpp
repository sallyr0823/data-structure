/* Your code here! */
#include "dsets.h"
#include <vector>
using namespace std;


void DisjointSets::addelements(int num) {
    for(int i = 0 ; i < num; i++) {
        index_.push_back(-1);
    }
    size_ += num;
}

int DisjointSets::find(int elem) {
    if(index_[elem]<0) {return elem;} 
    else {
        int output = find(index_[elem]);
        // add path compression
		index_[elem] = output;
        return output;
    }
}

void DisjointSets::setunion(int a, int b) {
    // a and b are index
    if(find(a) == find(b)) {return;}
    int a_ = find(a);
    int b_ = find(b);
    int newSize = index_[a_] + index_[b_];
    if(index_[a_] <= index_[b_]) {
        // a larger
        index_[b_] = a;
        index_[a_] = newSize;
    } else {
        index_[a_] = b;
        index_[b_] = newSize;
    }

}

/*void DisjointSets::UnionHelper(int s, int l) {
    // nodes_[s] -> nsize_ < nodes_[l] -> nsize;
    // a = l, b = s
    // a	Index of the first element to union
    // b	Index of the second element to union
    int newSize = index_[s] + index_[l];
    if(index_[s] < index_[l]) {
        index_[l] = s;
        index_[s] = newSize;
    } else {
        index_[s] = l;
        index_[l] = newSize;
    }

}*/

int DisjointSets::size(int elem) {
    int par = find(elem);
    return index_[par] * -1;
}

