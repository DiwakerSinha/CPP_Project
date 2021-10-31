#include "queue.hpp"

Queue::Queue() {
  head_ = nullptr;
  size_ = 0;
}

size_t Queue::GetSize() const { return size_; }

bool Queue::IsEmpty() const { return head_ == nullptr; }

Queue::QueueNode* Queue::Front() const { return head_; }

void Queue::EnqueueStudent(const std::string& name) {
  std::cout << name;  // comment this out
  // TODO: Implement this.
}

void Queue::RemoveStudent(const std::string& name) {
  std::cout << name;  // comment this out
  QueueNode* curr = head_;
  QueueNode* prev = nullptr;

  while (curr != nullptr) {
    // TODO: Complete this

    prev = curr;
    curr = curr->next;
  }
}

Queue::~Queue() {
  // TODO: Implement this.
}

std::ostream& operator<<(std::ostream& os, const Queue& q) {
  Queue::QueueNode* curr = q.Front();
  while (curr != nullptr) {
    os << curr->name << std::endl;
    curr = curr->next;
  }

  return os;
}
