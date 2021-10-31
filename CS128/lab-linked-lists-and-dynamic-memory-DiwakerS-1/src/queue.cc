#include "queue.hpp"

Queue::Queue() {
  head_ = nullptr;
  size_ = 0;
}

size_t Queue::GetSize() const { return size_; }

bool Queue::IsEmpty() const { return head_ == nullptr; }

Queue::QueueNode* Queue::Front() const { return head_; }

void Queue::EnqueueStudent(const std::string& name) {
  // std::cout << name;  // comment this out

  QueueNode* to_add = new QueueNode();
  to_add->name = name;

  if (head_ == nullptr) {
    head_ = to_add;
    to_add->next = nullptr;
    size_++;
    return;
  }

  QueueNode* curr = head_;
  while (curr->next != nullptr) {
    curr = curr->next;
  }
  curr->next = to_add;
  to_add->next = nullptr;
  size_++;
}

void Queue::RemoveStudent(const std::string& name) {
  // std::cout << name;  // comment this out
  QueueNode* curr = head_;
  QueueNode* prev = nullptr;

  if (head_ == nullptr) {
    throw std::runtime_error("Not present");
  }

  if (head_->name.compare(name) == 0) {
    head_ = head_->next;
    delete curr;
    size_--;
    return;
  }

  while (curr != nullptr) {
    if (curr->name.compare(name) == 0) {
      prev->next = curr->next;
      // curr = curr->next;
      delete curr;
      size_--;
      return;
    }
    prev = curr;
    curr = curr->next;
  }
}

Queue::~Queue() {
  QueueNode* curr = head_;
  while (curr != nullptr) {
    QueueNode* next = curr->next;
    delete curr;
    curr = next;
  }
}

std::ostream& operator<<(std::ostream& os, const Queue& q) {
  Queue::QueueNode* curr = q.Front();
  while (curr != nullptr) {
    os << curr->name << std::endl;
    curr = curr->next;
  }

  return os;
}
