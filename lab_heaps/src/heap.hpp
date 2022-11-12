
/**
 * @file heap.cpp
 * Implementation of a heap class.
 */
#include <cstddef>
#include <limits>

template <class T, class Compare>
class heap;

template <class T, class Compare>
size_t heap<T, Compare>::root() const
{
    // @TODO Update to return the index you are choosing to be your root.
    return 1;
}

template <class T, class Compare>
size_t heap<T, Compare>::leftChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the left child.
    size_t child = currentIdx * 2;
    return child;
}

template <class T, class Compare>
size_t heap<T, Compare>::rightChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the right child.
    size_t child = currentIdx * 2 + 1;
    return child;
}

template <class T, class Compare>
size_t heap<T, Compare>::parent(size_t currentIdx) const
{
    // @TODO Update to return the index of the parent.

    return (int)(currentIdx / 2);
}

template <class T, class Compare>
bool heap<T, Compare>::hasAChild(size_t currentIdx) const
{
    // @TODO Update to return whether the given node has a child
    size_t check = currentIdx * 2;
    if(check >= _elems.size()) {
        return false;
    }
    return true;
}

template <class T, class Compare>
size_t heap<T, Compare>::maxPriorityChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the child with highest priority
    ///   as defined by higherPriority()

    size_t left = currentIdx * 2;
    size_t right = currentIdx * 2 + 1;
    if (right >= _elems.size()) {return left;}
    if (higherPriority(_elems[left], _elems[right])) {return left;}
    return right;
}

template <class T, class Compare>
void heap<T, Compare>::heapifyDown(size_t currentIdx)
{
    // @TODO Implement the heapifyDown algorithm.
    if(!hasAChild(currentIdx)) {
        return;
    }
    size_t childIdx = maxPriorityChild(currentIdx);
    if (higherPriority(_elems[childIdx], _elems[currentIdx])) {
        std::swap(_elems[childIdx], _elems[currentIdx]);
        heapifyDown(childIdx);
    }
}

template <class T, class Compare>
void heap<T, Compare>::heapifyUp(size_t currentIdx)
{
    if (currentIdx == root())
        return;
    size_t parentIdx = parent(currentIdx);
    if (higherPriority(_elems[currentIdx], _elems[parentIdx])) {
        std::swap(_elems[currentIdx], _elems[parentIdx]);
        heapifyUp(parentIdx);
    }
}

template <class T, class Compare>
heap<T, Compare>::heap()

{
    // @TODO Depending on your implementation, this function may or may
    ///   not need modifying
    _elems = {T()};
}

template <class T, class Compare>
heap<T, Compare>::heap(const std::vector<T>& elems) 
{
    // @TODO Construct a heap using the buildHeap algorithm
    _elems = {T()};
    for (size_t i = 0; i < elems.size(); i++) {
        _elems.push_back(elems[i]);
    }
    for(size_t i = _elems.size() / 2; i > 0; i--) {
        heapifyDown(i);
    }
}

template <class T, class Compare>
T heap<T, Compare>::pop()
{
    // @TODO Remove, and return, the element with highest priority
    if(!empty()) {
        size_t size_ = _elems.size();
        T minValue = _elems[1];
        std::swap(_elems[root()], _elems.back());
        _elems.pop_back();
        heapifyDown(root());
        return minValue;
    }
    return T();
}

template <class T, class Compare>
T heap<T, Compare>::peek() const
{
    // @TODO Return, but do not remove, the element with highest priority
    return _elems[root()];
}

template <class T, class Compare>
void heap<T, Compare>::push(const T& elem)
{
    // @TODO Add elem to the heap
    _elems.push_back(elem);
    heapifyUp(_elems.size() - 1);
}

template <class T, class Compare>
void heap<T, Compare>::updateElem(const size_t & idx, const T& elem)
{
    // @TODO In-place updates the value stored in the heap array at idx
    // Corrects the heap to remain as a valid heap even after update
    _elems[idx] = elem;
    if(higherPriority(elem,_elems[parent(idx)])) {
        heapifyUp(idx);
    } else {
        heapifyDown(idx );
    }
    
}


template <class T, class Compare>
bool heap<T, Compare>::empty() const
{
    // @TODO Determine if the heap is empty
    return _elems.size() == root();
}

template <class T, class Compare>
void heap<T, Compare>::getElems(std::vector<T> & heaped) const
{
    for (size_t i = root(); i < _elems.size(); i++) {
        heaped.push_back(_elems[i]);
    }
}
