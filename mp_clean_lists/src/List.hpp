/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

template <class T>
List<T>::List() { 
  // @TODO: graded in MP3.1
    head_ = NULL;
    tail_ = NULL;
    length_ = 0;
}

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(head_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in MP3.1

  return List<T>::ListIterator(NULL);
}


/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  /// @todo Graded in MP3.1
  if (length_ == 0) {
    return;
  }
  while (head_ != nullptr) {
    ListNode* tmp = head_;
    head_ = head_ -> next;
    delete tmp;
    tmp = nullptr;
  }
  head_ = nullptr;
  tail_ = nullptr;
  length_ = 0;
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in MP3.1
  ListNode * newNode = new ListNode(ndata);
  if (length_ == 0) {
    head_ = newNode;
    tail_ = newNode;
  } else {
    newNode -> next = head_;
    head_ -> prev = newNode;
    head_ = head_ -> prev;
  }
  length_++;

}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in MP3.1
  ListNode* newNode = new ListNode(ndata);
  if (length_ == 0) {
    head_ = newNode;
    tail_ = newNode;
  } else {
    newNode -> prev = tail_;
    tail_ -> next = newNode;
    tail_ = tail_ -> next;
  }
  length_++;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * This function is also called by the public split() function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */

// i can't allocate new node
/*template<typename T >
List< T > List< T >::split(int splitPoint) {
  if (splitPoint > length_) {
    return List<T>();
  }
  if (splitPoint <= 0) {
    return this;
  }
  List<T> r;
  int count = 0;
  r.tail_ = tail_;
  tail_ = head_;
  while(count < splitPoint) {
    tail_ = tail_ -> next;
    count++;
  }
  r.head_  = split(head_,splitPoint);
  r.length_ = length_ - splitPoint;
  length_ = splitPoint;
  return r;
}*/

template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in MP3.1
  if (splitPoint >= length_) {return nullptr;}
  if (splitPoint <= 0) {return head_;}
  	ListNode* curr = start;
    for (int i = 0; i < splitPoint; i++) {
      if (curr -> next != nullptr) {
        curr = curr -> next;
      }
    }
    tail_ = curr -> prev;
    tail_ -> next = nullptr;
    curr -> prev = nullptr;
    return curr;

}

/**
  * Modifies List using the rules for a TripleRotate.
  *
  * This function will to a wrapped rotation to the left on every three 
  * elements in the list starting for the first three elements. If the 
  * end of the list has a set of 1 or 2 elements, no rotation all be done 
  * on the last 1 or 2 elements.
  * 
  * You may NOT allocate ANY new ListNodes!
  */
template <typename T>
void List<T>::tripleRotate() {
  // @todo Graded in MP3.1
  if (length_ < 3) {return;}
  ListNode* curr = head_;
  ListNode* second;
  ListNode* first;
  int i = 1;
  while(curr != nullptr) {
    if (i % 3 == 0) {
      // tmp is the next of the end node
      // curr is at 3
      ListNode* tmp = (curr -> next == nullptr) ? nullptr: curr -> next;
      second = curr -> prev;
      first = second -> prev;
      // tmp2 is the prev of start node
      ListNode* tmp2 = (first -> prev == nullptr) ? nullptr: first -> prev;
      curr -> next = first;
      first -> prev = curr;
      // if first is the tail
      if (tmp == nullptr) {
        first -> next = nullptr;
        tail_ = first;
      } else {
        // 1,2,3 -> 4 ---- 2,3,1 -> 4, 1 is the first, 4 is the tmp
        first -> next = tmp;
        tmp -> prev = first;
      }
      // 3 -> 4,5,6 --- 3 -> 5,6,4, 5 is the second, 3 is the tmp2
      if (tmp2 == nullptr) {
        second -> prev = nullptr;
        head_ = second;
      } else {
        second -> prev = tmp2;
        tmp2 -> next = second;
      }
      curr = curr -> next;
      if ((length_ - i) < 3 && length_ > 3) {
        return;
      }
    } 
    curr = curr -> next;
    i++;
    
    
}
}


/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  /// @todo Graded in MP3.2
  ListNode* start = startPoint;
  // prev of startpoint
  ListNode* prev = startPoint -> prev;
  ListNode* tmp = start -> next;
  start -> next = endPoint -> next;
  start -> prev = tmp;
  start = tmp;

  // loop of reverse
  while (start != endPoint) {
    tmp = start -> next;
    start -> next = start -> prev;
    start -> prev = tmp;
    start = tmp;
  }
  endPoint -> next = endPoint -> prev;
  endPoint -> prev = prev;
  if (head_ != startPoint) {
    prev->next = start;
  } else {
    head_ = endPoint;
  }
  if (tail_ != endPoint) {
    startPoint->next->prev = startPoint;
  } else {
    tail_ = startPoint;
  }

}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in MP3.2
  ListNode * start = head_;
  ListNode * end = start;

  while (start != NULL) {
    int count = 1;
    while (count < n) {
      if (end != tail_) {
        end = end->next;
      }
      count++;
    }
    reverse(start, end);
    start = start->next; //to the next block
    end = start;  
  }
}


/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  /// @todo Graded in MP3.2
    ListNode* result;
    if (first -> data < second -> data) {
      result = first;
      first = first -> next;
    } else {
      result = second;
      second = second -> next;
    }
    ListNode* tmp = result;
    while (first != NULL && second != NULL) {
      if (first->data < second -> data) {
        tmp -> next = first;
        first -> prev = tmp;
        first = first -> next;
      } else {
        tmp -> next = second;
        second -> prev = tmp;
        second = second -> next;
      }
      tmp = tmp -> next;
    }
    if (first != NULL && second == NULL) {
      tmp -> next = first;
      first -> prev = tmp;
    }
    if (first == NULL && second != NULL) {
      tmp -> next = second;
      second -> prev = tmp;
    }
    return result;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in MP3.2
  if (start -> next == NULL) {
    return start;
  }
  ListNode* second = split(start, chainLength/2);
  return merge(mergesort(start, chainLength/2),mergesort(second, (chainLength/2) + (chainLength%2)));
}
