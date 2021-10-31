#include "circular-linked-list.hpp"

#include <vector>
using namespace std;

CircularLinkedList::CircularLinkedList() {
  head_ = nullptr;
  tail_ = nullptr;
  node_order_ = Order::kASC;
}

CircularLinkedList::CircularLinkedList(const CircularLinkedList& source) {
  node_order_ = source.node_order_;
  if (source.head_ == nullptr) {
    head_ = nullptr;
    tail_ = nullptr;
    return;
  }

  head_ = new Node(source.head_->data);
  head_->next = nullptr;

  Node* curr_new = head_;
  Node* curr_copy = source.head_;

  while (curr_copy->next != source.head_) {
    Node* to_add = new Node(curr_copy->next->data);
    curr_new->next = to_add;
    curr_new = curr_new->next;
    curr_copy = curr_copy->next;
  }
  tail_ = curr_new;
  tail_->next = head_;
}

CircularLinkedList& CircularLinkedList::operator=(
    const CircularLinkedList& source) {
  if (this == &source) {
    return *this;
  }

  Clear();

  node_order_ = source.node_order_;
  if (source.head_ == nullptr) {
    head_ = nullptr;
    tail_ = nullptr;
    return *this;
  }

  head_ = new Node(source.head_->data);
  head_->next = nullptr;

  Node* curr_new = head_;
  Node* curr_copy = source.head_;

  while (curr_copy->next != source.head_) {
    Node* to_add = new Node(curr_copy->next->data);
    curr_new->next = to_add;
    curr_new = curr_new->next;
    curr_copy = curr_copy->next;
  }
  tail_ = curr_new;
  tail_->next = head_;

  return *this;
}

void CircularLinkedList::InsertInOrder(int data) {
  Node* insert = new Node(data);

  if (head_ == nullptr) {  // empty list
    head_ = insert;
    head_->next = nullptr;
    tail_ = head_;
    tail_->next = head_;
    return;
  }

  if (node_order_ == Order::kASC) {  // ascending order

    if (insert->data <= head_->data) {  // to insert <= first node
      insert->next = head_;
      tail_->next = insert;
      head_ = insert;
      return;
    }

    if (insert->data >= tail_->data) {
      tail_->next = insert;
      insert->next = head_;
      tail_ = insert;
      return;
    }

    Node* curr = head_;

    while (curr != tail_) {  // Inserts till the before the last node.

      if ((curr->data <= data) && (data <= curr->next->data)) {
        insert->next = curr->next;
        curr->next = insert;
        return;
      }

      curr = curr->next;
    }

  } else if (node_order_ == Order::kDESC) {
    if (insert->data >= head_->data) {  // to insert <= first node
      insert->next = head_;
      tail_->next = insert;
      head_ = insert;
      return;
    }

    if (insert->data <= tail_->data) {
      tail_->next = insert;
      insert->next = head_;
      tail_ = insert;
      return;
    }

    Node* curr = head_;

    while (curr->next != tail_) {  // Inserts till the before the last node.

      if ((curr->data >= data) && (data >= curr->next->data)) {
        insert->next = curr->next;
        curr->next = insert;
        return;
      }
      curr = curr->next;
    }
  }
}

CircularLinkedList::~CircularLinkedList() { Clear(); }

void CircularLinkedList::Reverse() {
  node_order_ = ((node_order_ == Order::kASC) ? Order::kDESC : Order::kASC);
  if (head_ == nullptr) {
    return;
  }

  Node* to_be_tail = head_;
  Node* prev = head_;
  Node* curr = head_->next;

  head_ = head_->next;

  while (head_ != to_be_tail) {
    head_ = head_->next;
    curr->next = prev;

    prev = curr;
    curr = head_;
  }

  curr->next = prev;
  head_ = prev;

  curr = head_;
  while (curr->next != head_) {
    curr = curr->next;
  }

  tail_ = curr;
}

void CircularLinkedList::Clear() {
  if (head_ == nullptr) {
    return;
  }
  Node* curr = head_;
  while (curr != tail_) {
    curr = curr->next;
    delete head_;
    head_ = curr;
  }
  delete tail_;
  curr = nullptr;
  tail_ = nullptr;
  head_ = nullptr;
}

// std::ostream& operator<<(std::ostream& os, const CircularLinkedList& cll) {
//   return os;
// }

// std::ostream& operator<<(std::ostream& os, const CircularLinkedList& cll) {
//   // do something
//   return os;
// }