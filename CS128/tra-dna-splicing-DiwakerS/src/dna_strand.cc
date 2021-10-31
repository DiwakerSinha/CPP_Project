#include "dna_strand.hpp"

#include <stdexcept>

using namespace std;

DNAstrand::DNAstrand() {
  head_ = nullptr;
  tail_ = nullptr;
}

DNAstrand::DNAstrand(const DNAstrand& rhs) {
  if (this == &rhs || rhs.head_ == NULL) {
    return;
  }
  head_ = new Node<char>(rhs.head_->data);
  Node<char>* curr = head_;
  Node<char>* curr_copy = rhs.head_;
  tail_ = curr;
  while (curr_copy->next != nullptr) {
    Node<char>* insert = new Node<char>(curr_copy->next->data);
    curr->next = insert;
    curr = curr->next;
    tail_ = curr;
  }
}
DNAstrand& DNAstrand::operator=(const DNAstrand& rhs) {
  if (this == &rhs) {
    return *this;
  }

  clear();

  if (rhs.head_ == NULL) {
    return *this;
  }
  head_ = new Node<char>(rhs.head_->data);
  Node<char>* curr = head_;
  Node<char>* curr_copy = rhs.head_;
  tail_ = curr;
  while (curr_copy->next != nullptr) {
    Node<char>* insert = new Node<char>(curr_copy->next->data);
    curr->next = insert;
    curr = curr->next;
    tail_ = curr;
  }

  return *this;
}
DNAstrand::~DNAstrand() { clear(); }

void DNAstrand::clear() {
  if (head_ == nullptr) {
    return;
  }
  Node<char>* curr = head_;
  while (curr != nullptr) {
    Node<char>* next = curr->next;
    delete curr;
    curr = next;
  }
  head_ = nullptr;
  tail_ = nullptr;
}

void DNAstrand::SpliceIn(const char* pattern, DNAstrand& to_splice_in) {
  if (to_splice_in.head_ == nullptr) {
    return;
  }

  char* nodes_seq = sequence(*this);

  if (finder(nodes_seq, pattern) == -1) {
    throw runtime_error(".");
  }

  else {
    tail_->next = to_splice_in.head_;
    tail_ = to_splice_in.tail_;
  }
  // } else {
  //   int to_start_delete = finder(nodes_seq, pattern);
  //   int index = 0;
  //   Node <char> * curr = head_;
  //   Node <char> * next = curr_;
  //   while ()
  //   while ()
  // }
}

char* DNAstrand::sequence(DNAstrand& nodes) {
  int size = 0;
  Node<char>* curr = nodes.head_;
  while (curr != nullptr) {
    size++;
    curr = curr->next;
  }

  char to_return[size];
  curr = nodes.head_;
  int counter = 0;
  while (curr != nullptr) {
    to_return[counter] = curr->data;
    counter++;
    curr = curr->next;
  }
  return to_return;
}

int DNAstrand::finder(const char* to_search_in, const char* key) {
  if (size(to_search_in) < size(key)) {
    return -1;
  }

  int size_search = size(to_search_in);

  for (int i = 0; i < size(to_search_in); i++) {
    int counter = 0;
    for (int j = 0; j < size(key); j++) {
      if (i + j >= size_search) {
        break;
      }
      if (to_search_in[i + j] == key[j]) {
        counter++;
      }
    }
    if (counter == size(key)) {
      return i;
    }
    counter = 0;
  }
  return -1;
}

int DNAstrand::size(const char* to_search_in) {
  int counter = 0;
  while (to_search_in[counter] != '\0') {
    counter++;
  }
  return counter;
}