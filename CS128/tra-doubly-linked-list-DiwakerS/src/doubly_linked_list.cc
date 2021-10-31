#include <iomanip>
#include <sstream>
#include <stdexcept>
using namespace std;

#include "doubly_linked_list.hpp"

DoublyLinkedList::DoublyLinkedList(char val) {
  head_ = new Node(val);
  head_->next = nullptr;
  head_->prev = nullptr;
  tail_ = head_;
  size_ = 1;
}

DoublyLinkedList::DoublyLinkedList(const std::vector<char>& values) {
  if (values.size() == 0) {
    head_ = nullptr;
    tail_ = nullptr;
    size_ = 0;
  } else if (values.size() == 1) {
    head_ = new Node(values.at(0));
    head_->next = nullptr;
    head_->prev = nullptr;
    tail_ = head_;
    size_ = 1;
  } else {
    head_ = new Node(values.at(0));
    Node* curr = head_;
    for (size_t i = 1; i < values.size(); i++) {
      curr->next = new Node(values.at(i));
      Node* nextt = curr->next;
      nextt->prev = curr;
      nextt->next = nullptr;
      curr = curr->next;
    }
    tail_ = curr;
    curr->next = nullptr;
    size_ = values.size();
  }
}

DoublyLinkedList::DoublyLinkedList(const DoublyLinkedList& rhs) {
  size_ = rhs.size_;

  if (rhs.size_ == 0) {
    head_ = nullptr;
    tail_ = nullptr;
    return;
  } else if (rhs.size_ == 1) {
    head_ = new Node(rhs.head_->data);
    head_->next = nullptr;
    head_->prev = nullptr;
    tail_ = head_;
    return;
  }

  head_ = new Node(rhs.head_->data);

  Node* curr_new = head_;
  Node* curr_copy_from = rhs.head_;

  while (curr_copy_from->next !=
         nullptr) {  // loop ends when curr_copy_from is at tail_

    Node* next_to_be_added = new Node(curr_copy_from->next->data);
    curr_new->next = next_to_be_added;
    next_to_be_added->prev = curr_new;

    curr_new = curr_new->next;
    curr_copy_from = curr_copy_from->next;
  }

  tail_ = curr_new;
  tail_->next = nullptr;
}

DoublyLinkedList& DoublyLinkedList::operator=(const DoublyLinkedList& rhs) {
  //~DoublyLinkedList(this);
  if (this == &rhs) {
    return *this;
  }
  // if (head_ != nullptr) {
  //   return;
  // }
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

  size_ = rhs.size_;

  if (rhs.size_ == 0) {
    head_ = nullptr;
    tail_ = nullptr;
  } else if (rhs.size_ == 1) {
    head_ = new Node(rhs.head_->data);
    head_->next = nullptr;
    head_->prev = nullptr;
    tail_ = head_;
  } else {
    head_ = new Node(rhs.head_->data);

    Node* curr_new = head_;
    Node* curr_copy_from = rhs.head_;

    while (curr_copy_from->next !=
           nullptr) {  // loop ends when curr_copy_from is at tail_

      Node* next_to_be_added = new Node(curr_copy_from->next->data);
      curr_new->next = next_to_be_added;
      next_to_be_added->prev = curr_new;

      curr_new = curr_new->next;
      curr_copy_from = curr_copy_from->next;
    }

    tail_ = curr_new;
    tail_->next = nullptr;
  }

  return *this;
}
DoublyLinkedList::~DoublyLinkedList() {
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

char& DoublyLinkedList::Back() {
  if (head_ == nullptr) {
    throw runtime_error(".");
  }
  return tail_->data;
}
char& DoublyLinkedList::Front() {
  if (head_ == nullptr) {
    throw runtime_error(".");
  }
  return head_->data;
}
void DoublyLinkedList::PopBack() {
  if (head_ == nullptr) {
    throw runtime_error(".");
  } else if (head_->next == nullptr) {
    delete head_;
    head_ = nullptr;
    tail_ = nullptr;
  } else {
    Node* prev = tail_->prev;
    delete tail_;
    tail_ = prev;
    tail_->next = nullptr;
  }
  size_--;
}

void DoublyLinkedList::PopFront() {
  if (head_ == nullptr) {
    throw runtime_error(".");
  } else if (head_->next == nullptr) {
    delete head_;
    head_ = nullptr;
    tail_ = nullptr;
  } else {
    Node* temp = head_->next;
    delete head_;
    head_ = temp;
    head_->prev = nullptr;
  }
  size_--;
}

void DoublyLinkedList::PushBack(char val) {
  Node* insert = new Node(val);
  if (head_ == nullptr) {
    head_ = insert;
    head_->next = nullptr;
    head_->prev = nullptr;
    tail_ = head_;
  } else {
    insert->prev = tail_;
    tail_->next = insert;
    tail_ = tail_->next;
    tail_->next = nullptr;
  }
  size_++;
}
void DoublyLinkedList::PushFront(char val) {
  Node* insert = new Node(val);
  if (head_ == nullptr) {
    head_ = insert;
    head_->next = nullptr;
    head_->prev = nullptr;
    tail_ = head_;
  } else {
    insert->next = head_;
    head_->prev = insert;
    head_ = insert;
    head_->prev = nullptr;
  }
  size_++;
}

void DoublyLinkedList::InsertAt(size_t idx, char val) {
  if (idx > size_) {
    throw runtime_error("Out of bounds");
  }

  Node* insert = new Node(val);

  if (size_ == 0) {
    head_ = insert;
    head_->prev = nullptr;
    head_->next = nullptr;
    tail_ = head_;

  } else if (idx == 0) {
    insert->next = head_;
    head_->prev = insert;
    head_ = insert;

  } else if (idx == size_) {
    tail_->next = insert;
    insert->prev = tail_;
    tail_ = insert;
  } else {
    Node* curr = head_;
    for (size_t i = 0; i < idx - 1; i++) {
      curr = curr->next;
    }
    insert->next = curr->next;
    curr->next->prev = insert;
    curr->next = insert;
    insert->prev = curr;
  }
  size_++;
}
void DoublyLinkedList::EraseAt(size_t idx) {
  if (idx >= size_) {
    throw runtime_error("Out of bounds");
  }

  if (size_ == 1) {
    delete head_;
    head_ = nullptr;
    tail_ = nullptr;

  } else if (idx == 0) {
    Node* curr = head_->next;
    curr->prev = nullptr;
    delete head_;
    head_ = curr;

  } else if (idx == size_ - 1) {
    Node* curr = tail_->prev;
    curr->next = nullptr;
    delete tail_;
    tail_ = curr;

  } else {
    Node* curr = head_;
    for (size_t i = 0; i < idx - 1; i++) {
      curr = curr->next;
    }
    Node* to_delete = curr->next;

    curr->next = to_delete->next;
    if (to_delete->next->prev != nullptr) {
      to_delete->next->prev = curr;
    }
    delete to_delete;
  }
  size_--;
}

char& DoublyLinkedList::Find(char val) {
  if (head_ == nullptr) {
    throw runtime_error(".");
  }
  Node* curr = head_;
  while (curr != tail_) {
    if (curr->data == val) {
      return curr->data;
    }
    curr = curr->next;
  }
  if (curr->data == val) {
    return curr->data;
  } else {
    throw runtime_error("Not found");
  }
  return curr->data;
}
void DoublyLinkedList::Clear() { return; }

// Functions provided to you
ostream& operator<<(ostream& os, const DoublyLinkedList& ll) {
  constexpr unsigned int width = 16;
  os << "Doubly Linked List" << endl;
  os << "Head: " << ll.head_ << "\t Tail: " << ll.tail_ << endl;
  os << "Size: " << ll.size_ << endl;
  if (ll.head_ == nullptr) return (os << "Empty" << endl);
  const Node* curr = ll.head_;
  os << "Nodes (accessible from head to tail):" << endl << endl;
  os << setw(width) << setfill(' ') << ' ' << ' ' << center("prev", width - 1)
     << ' ' << center("data", width - 1) << ' ' << center("next", width - 1)
     << endl;
  while (curr != nullptr) {
    ostringstream oss;
    oss << (curr->prev);
    string prev = oss.str();
    oss.str("");
    oss << (curr->next);
    string next = oss.str();
    oss.str("");
    oss << (curr->data);
    string data = oss.str();
    oss.str("");
    oss << curr;
    string address = oss.str();
    os << setw(width) << setfill(' ') << ' ' << '.' << setw(width)
       << setfill('-') << '.' << setw(width) << '.' << setw(width) << '.'
       << endl;
    os << setw(width) << setfill(' ') << center(address, width - 1) << '|'
       << setw(width - 1) << setfill(' ') << center(prev, width - 1) << '|'
       << setw(width - 1) << center(data, width - 1) << '|' << setw(width - 1)
       << center(next, width - 1) << '|' << endl;
    os << setw(width) << setfill(' ') << ' ' << '\'' << setw(width)
       << setfill('-') << '\'' << setw(width) << '\'' << setw(width) << '\''
       << endl;
    os << endl;
    curr = curr->next;
  }
  return os;
}

std::string center(const std::string& str, decltype(str.length()) col_width) {
  // quick and easy (but error-prone) implementation
  decltype(str.length()) padl = (col_width - str.length()) / 2;
  decltype(str.length()) padr = (col_width - str.length()) - padl;
  string strf = string(padl, ' ') + str + string(padr, ' ');
  return strf;
}