#ifndef BRANCHED_LINKED_LIST_HPP
#define BRANCHED_LINKED_LIST_HPP

#include <cstddef>
#include <stdexcept>

#include "cs128string.hpp"
#include "node.hpp"

class BLL {
public:
  BLL();
  BLL(const BLL& to_copy);
  ~BLL();

  BLL& operator=(const BLL& rhs);
  Node* PushBack(char dat);
  char GetAt(size_t idx) const;
  void SetAt(size_t idx, char dat);
  void Join(size_t idx, BLL* list);
  cs128::string ToString() const;
  size_t Size() const;
  Node* copy_node(Node* to_return, Node* to_copy);
  BLL* copy_bll(BLL* to_return, BLL* to_copy);
  void test(BLL* one, BLL* two);

private:
  Node* head_;
  bool IsBLLAcyclic() const;
};

#endif