/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

template <class T> List<T>::List() {
  // @TODO: graded in MP3.1
  head_ = NULL;
  tail_ = NULL;
}

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T> typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(head_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T> typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(NULL);
}

/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T> void List<T>::_destroy() {

  if (head_ == NULL) {
    return;
  }

  while (head_->next != NULL) {
    head_->next->prev = head_;
    head_ = head_->next;
    delete head_->prev;
  }
  head_ = NULL;
  tail_ = NULL;
  /// @todo Graded in MP3.1
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T> void List<T>::insertFront(T const &ndata) {
  /// @todo Graded in MP3.1
  ListNode *newNode = new ListNode(ndata);

  if (head_ == NULL) {
    head_ = newNode;
    tail_ = newNode;
  } else {
    newNode->next = head_;
    head_->prev = newNode;
    head_ = newNode;
  }
  length_++;
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T> void List<T>::insertBack(const T &ndata) {
  ListNode *newNode = new ListNode(ndata);

  if (head_ == NULL) {
    head_ = newNode;
    tail_ = newNode;

  } else {
    tail_->next = newNode;
    newNode->prev = tail_;
    tail_ = newNode;
  }
  length_++;
  /// @todo Graded in MP3.1
}

// template <typename T>
// List<T> List<T>::split(int splitPoint) {
//   ListNode* from_index = split(head_, splitPoint);
//   List<T> to_return;
//   to_return.head_ = from_index;
//   to_return.tail_ = from_index;
//   while(to_return.tail->next != NULL) {
//     to_return.tail = to_return.tail->next;
//   }
//   return to_return;
// }

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
template <typename T>
typename List<T>::ListNode *List<T>::split(ListNode *start, int splitPoint) {

  if (splitPoint == 0) {
    return start;
  }

  ListNode *curr = start;

  for (int i = 0; i < splitPoint && curr != NULL; i++) {
    curr = curr->next;
  }

  if (curr != NULL && curr->prev != NULL) {
    curr->prev->next = NULL;
    curr->prev = NULL;
  }

  return curr;

  // ListNode * from_index = start;
  // for (size_t i = 0; i < (unsigned)splitPoint; i++) {
  //   from_index = from_index->next;
  // }
  // //tail_ = from_index->prev;
  // from_index->prev = NULL;

  // return from_index;
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
template <typename T> void List<T>::tripleRotate() {
  if (head_ == NULL) {
    return;
  } else if (length_ < 3) {
    return;
  }

  ListNode *start = head_ -> next;
  ListNode *temp = head_;

  while (temp != NULL && temp->next != NULL && temp->next->next != NULL) {

  ListNode *two = temp->next;
  ListNode *three = temp->next->next;
  ListNode *four = temp->next->next->next;
    if (temp->prev != NULL) {
      temp->prev->next = two;
    }

    two->prev = temp->prev;
    temp->next = four;

    if (four != NULL) {
      four->prev = temp;
    }
    three->next = temp;
    temp->prev = three;

    temp = temp->next;
  }

    head_ = start;


  // size_t j = length_;
  // while (j > 3) {
  //   j = j % 3;
  // }
  // ListNode * temp = head_;
  // for (size_t i = 0; i < length_ - j; i++) {

  //   temp->next = NULL;
  //   tail_->next = temp;
  //   head_ = head_->next;
  //   head_ -> prev = NULL;
  // }
  // @todo Graded in MP3.1
}

/**
 * Reverses the current List.
 */
template <typename T> void List<T>::reverse() { reverse(head_, tail_); }

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
void List<T>::reverse(ListNode *&startPoint, ListNode *&endPoint) {
  /// @todo Graded in MP3.2

  if (startPoint == NULL || endPoint == NULL) {
    return;
  }

  if (startPoint == endPoint) {
    return;
  }

  ListNode *starting = startPoint;
  ListNode *ending = endPoint;
  ListNode *curr = startPoint;
  ListNode *prev_elem = startPoint->prev;
  ListNode *next_elem = endPoint->next;

  while (curr != next_elem) {
    ListNode *temp = curr->next;
    curr->next = curr->prev;
    curr->prev = temp;
    curr = curr->prev;
  }

  // curr->next = curr->prev;
  // curr->prev = prev_elem;
  // prev_elem->next = next_elem;

  ending->prev = prev_elem;
  starting->next = next_elem;

  if (prev_elem != NULL) {
    prev_elem->next = endPoint;
  }
  if (next_elem != NULL) {
    next_elem->prev = startPoint;
  }
  if (prev_elem == NULL) {
    head_ = endPoint;
  }
  if (next_elem == NULL) {
    tail_ = startPoint;
  }

  ListNode *temp = startPoint;
  startPoint = endPoint;
  endPoint = temp;

  // ListNode *temp = NULL;
  // ListNode *curr = startPoint;

  // while (curr != NULL) {
  //   temp = curr->prev;
  //   curr->prev = curr->next;
  //   curr->next = temp;
  //   curr = curr->next;
  // }

  // if (temp != NULL) {
  //   startPoint = temp->prev;
  // }

  // ListNode *finder = startPoint;
  // while (finder->next != NULL) {
  //   finder = finder->next;
  // }
  // endPoint = finder;

  // ListNode * curr = startPoint;
  // for (curr = startPoint; curr != endPoint && curr != NULL; curr =
  // curr->next) {
  //   ListNode * previous = curr -> prev;
  //   curr -> prev = curr -> next;
  //   curr -> next = previous;
  // }

  // curr->next = NULL;
  // endPoint->prev = NULL;
  // endPoint->next = endPoint->prev;

  // ListNode * ending = endPoint;
  // endPoint = startPoint;
  // startPoint = ending;
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T> void List<T>::reverseNth(int n) {
  if (n < 2) {
    return;
  }
  if (head_ == NULL) {
    return;
  }
  if (length_ <= n) {
    reverse(head_, tail_);
  }

  ListNode *startPoint = head_;
  ListNode *endPoint = NULL;
  while (startPoint != NULL) {
    endPoint = startPoint;
    for (auto i = 0; i < n - 1; i++) {
      if (endPoint->next != NULL) {
        endPoint = endPoint->next;
      }
    }
    reverse(startPoint, endPoint);
    startPoint = endPoint->next;
  }
  /// @todo Graded in MP3.2
}

/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T> void List<T>::mergeWith(List<T> &otherList) {
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
typename List<T>::ListNode *List<T>::merge(ListNode *first, ListNode *second) {
  if (first == NULL && second == NULL) {
    return NULL;
  } else if (first == NULL) {
    return second;
  } else if (second == NULL) {
    return first;
  }

  ListNode *temp_head;
  if (first->data < second->data || first->data == second->data) {
    temp_head = first;
    first = first->next;
  } else {
    temp_head = second;
    second = second->next;
  }
  ListNode *ptr = temp_head;

  while (first != NULL || second != NULL) {
    if (first != NULL && second != NULL) {
      if (first->data < second->data || first->data == second->data) {
        temp_head->next = first;
        temp_head = temp_head->next;
        first = first->next;
      } else {
        temp_head->next = second;
        temp_head = temp_head->next;
        second = second->next;
      }
    } else if (first == NULL) {
      temp_head->next = second;
      second = second->next;
      temp_head = temp_head->next;
    } else {
      temp_head->next = first;
      first = first->next;
      temp_head = temp_head->next;
    }
  }

  while (temp_head->prev != NULL) {
    temp_head = temp_head->prev;
  }
  return ptr;
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
typename List<T>::ListNode *List<T>::mergesort(ListNode *start,
                                               int chainLength) {
  if (chainLength == 0) {
    return NULL;
  }
  if (start == NULL) {
    return NULL;
  } else if (chainLength == 1) {
    return start;
  }

  ListNode *first = start;
  ListNode *second = split(start, (int)(chainLength / 2));

  first = mergesort(first, chainLength / 2);
  if (chainLength % 2 == 0) {
    second = mergesort(second, (int)(chainLength / 2));
  } else {
    second = mergesort(second, (int)(chainLength / 2 + 1));
  }

  return merge(first, second);
}
