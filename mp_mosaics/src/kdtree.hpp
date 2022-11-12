/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>
#include <cmath>
#include <iostream>

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
    //a[0] = 4;
    // a is now (4, 2, 3)
    if (curDim < 0 || curDim >= Dim) return false;
    if(first[curDim] == second[curDim]) {
      return first < second;
    }
    // tiebreak
    return first[curDim] < second[curDim];
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
   double cur_dist = 0;
   double pot_dist = 0;
    for(int i=0; i<Dim;i++){  
       	cur_dist += ((target[i]-currentBest[i])*(target[i]-currentBest[i]));
       	pot_dist += ((target[i]-potential[i])*(target[i]-potential[i]));
    }
    // tiebreak
    if(cur_dist==pot_dist) return potential < currentBest; 
    return pot_dist<cur_dist;
}
// main constructor function, here
template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
    if(newPoints.empty()) {
      return;
    }
    size = 0;
    vector<Point<Dim>> point_copy;
    point_copy.assign(newPoints.begin(),newPoints.end());
    root = TreeGrow(point_copy,0,newPoints.size()-1,0);


}
// To whom it may concern:
// I wirte every line for constructor under the instruction of AMA slides
// and my own thought
// If it meets with another student's code coincidentally(i mean, out of logic)
// It's just a coincidence
// helper function
template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::TreeGrow(vector<Point<Dim>>& newPoints,unsigned left,unsigned right, int dim)
{
  if(newPoints.empty() || right >= newPoints.size() || left < 0 || left >= newPoints.size()) {return NULL;}
  if(left > right) {return NULL;}
  unsigned med = (left+right)/2;
  KDTreeNode* subroot = new KDTreeNode(QuickSelect(newPoints,left,right,med,dim%Dim));
  size++;
  dim++;
  subroot -> left = TreeGrow(newPoints, left, med - 1, dim % Dim);
  subroot -> right = TreeGrow(newPoints, med + 1, right, dim % Dim);
  return subroot;    
}
// partition
template <int Dim>
unsigned KDTree<Dim>::Partition(vector<Point<Dim>>& newPoints,unsigned left, unsigned right, unsigned ind, int dim) {
  Point<Dim> x = newPoints[ind];
  //swap target value to most right
  Point<Dim> tmp = newPoints[ind];
  newPoints[ind] = newPoints[right];
  newPoints[right] = tmp;
  unsigned sort = left;
  for (unsigned j = left; j < right; j++) {
        if (smallerDimVal(newPoints[j],x,dim)) {
            Point<Dim> tmp = newPoints[sort];
            newPoints[sort] = newPoints[j];
            newPoints[j] = tmp;
            sort++;
        }
    }
    Point<Dim> tmp_r = newPoints[sort];
    newPoints[sort] = newPoints[right];
    newPoints[right] = tmp_r;
    return sort;
}
// quickselect
template <int Dim>
Point<Dim> KDTree<Dim>::QuickSelect(vector<Point<Dim>>& newPoints,unsigned left,unsigned right,unsigned ind,int dim)
{ 
  if(left == right) {return newPoints[left];}
  unsigned tmp = ind;
  unsigned pivot_ind = Partition(newPoints,left,right,ind,dim % Dim);
  //ind is the original index,pivot_ind is the index after partition
  //std::cout << pivot_ind << std::endl;
  if(ind == pivot_ind) {
    return newPoints[ind];
    } else if(ind < pivot_ind) {
      return QuickSelect(newPoints,left,pivot_ind-1,ind,dim% Dim);
    } else {
      return QuickSelect(newPoints,pivot_ind+1,right,ind,dim%Dim);
    }

}


template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
   */
  size = other.size;
  root = _copy(other.root);
  
}
template<int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::_copy(KDTreeNode* otherroot) {
  if(otherroot == NULL) return NULL;
  KDTreeNode* subroot = new KDTreeNode(otherroot -> point);
  //size++;
  subroot -> left = _copy(otherroot -> left);
  subroot -> right = _copy(otherroot -> right);
  return subroot;

}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   * 
   */
  if(&this == rhs) {return *this;}
  size = rhs.size;
  root = rhs.root;
  _copy(root,rhs.root);

  return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
  size = 0;
  _destroy(root);
}

template<int Dim>
void KDTree<Dim>::_destroy(KDTreeNode* subroot) {
  if(subroot == NULL) {return;}
  if(subroot -> left != NULL) {
    _destroy(subroot -> left);
  }
  if(subroot -> right != NULL) {
    _destroy(subroot -> right);
  }
  delete subroot;
  subroot = nullptr;

}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */

    if(root == NULL) {return NULL;}
    return dfs(root,query,0);
}

template<int Dim>
Point<Dim> KDTree<Dim>::dfs(KDTreeNode* subroot, const Point<Dim>& query,int dim)  const{
  if(subroot == NULL) {return NULL;}
  if (subroot->point == query) { return subroot->point; }
  Point<Dim> nearest = subroot -> point;
  if(subroot -> left == NULL && subroot -> right == NULL) {return subroot -> point;}
  bool left = true;
  if(smallerDimVal(query,subroot -> point,dim % Dim)) {
    //recursive on left until leaf
    if(subroot  -> left != NULL) {
      nearest = dfs(subroot -> left,query,(dim+1) % Dim);
    } 
  } else {
    //recursive on right until leaf
    if(subroot -> right != NULL) {
      nearest = dfs(subroot -> right,query,(dim+1) % Dim);
      left = false;
    } 
  }


 if (shouldReplace(query, nearest, subroot->point)) {
    nearest = subroot -> point;
  }

  double radius = 0;
  for(int i=0; i<Dim;i++){
       	radius += ((nearest[i]-query[i])*(nearest[i]-query[i]));
  }
  double split = (subroot -> point[dim] - query[dim])*(subroot -> point[dim]-query[dim]);
  if(split <= radius) {
    KDTreeNode* check = left ? subroot -> right : subroot -> left;
    if(check != NULL) {
      Point<Dim> checkBest = dfs(check, query, (dim+1) % Dim);
      if (shouldReplace(query, nearest, checkBest)) {
        nearest = checkBest;  
  }
    }
      
  }

  return nearest;


}



