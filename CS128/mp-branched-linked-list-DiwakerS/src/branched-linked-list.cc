#include "branched-linked-list.hpp"
using namespace std;

BLL::BLL() { head_ = nullptr; }
BLL::BLL(const BLL& to_copy) { head_ = copy_node(this->head_, to_copy.head_); }

void BLL::test(BLL* one, BLL* two) {
  head_ = copy_node(this->head_, two->head_);
}

Node* BLL::copy_node(Node* to_return, Node* to_copy) {
  if (to_copy == nullptr) {
    return nullptr;
  }
  to_return = new Node(to_copy->data_);
  std::cout << to_return->data_;
  to_return->next_bll_ = copy_bll(to_return->next_bll_, to_copy->next_bll_);
  to_return->next_node_ = copy_node(to_return->next_node_, to_copy->next_node_);

  return to_return;
}

BLL* BLL::copy_bll(BLL* to_return, BLL* to_copy) {
  if (to_copy == nullptr) {
    return nullptr;
  }
  if (to_copy->head_ == nullptr) {
    return nullptr;
  }
  cout << to_copy->head_->data_;
  << end;
  to_return->head_ = new Node(to_copy->head_->data_);
  to_return->head_->next_bll_ =
      copy_bll(to_return->head_->next_bll_, to_copy->head_->next_bll_);
  to_return->head_->next_node_ =
      copy_node(to_return->head_->next_node_, to_copy->head_->next_node_);

  return to_return;
}

BLL::~BLL() {
  //   delete head_;
  //   head_ = nullptr;
}

BLL& BLL::operator=(const BLL& rhs) {
  if (this == &rhs) {
    return *this;
  }
  return *this;
}
Node* BLL::PushBack(char dat) {
  Node* insert = new Node(dat);
  insert->next_node_ = nullptr;
  insert->next_bll_ = nullptr;
  if (head_ == nullptr) {
    head_ = insert;
    return head_;
  }
  Node* curr = head_;
  while (curr->next_node_ != nullptr) {
    curr = curr->next_node_;
  }
  curr->next_node_ = insert;
  return curr->next_node_;
}
char BLL::GetAt(size_t idx) const {
  if (idx >= 0) {
    return 'a';
  }
  return 'a';
}
void BLL::SetAt(size_t idx, char dat) {
  if (idx >= 0 || dat == 'a') {
    return;
  }
}
void BLL::Join(size_t idx, BLL* list) {
  if (idx >= 0 && list->head_ != NULL) {
    return;
  }
  return;
}
cs128::string BLL::ToString() const { return ""; }
size_t BLL::Size() const { return 0; }

bool BLL::IsBLLAcyclic() const { return true; }