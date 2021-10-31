#ifndef DNA_STRAND_HPP
#define DNA_STRAND_HPP

#include "node.hpp"

class DNAstrand {
public:
  DNAstrand();
  DNAstrand(const DNAstrand& rhs);
  DNAstrand& operator=(const DNAstrand& rhs);
  ~DNAstrand();
  void clear();
  char* sequence(DNAstrand& nodes);
  int finder(const char* to_search_in, const char* key);
  int size(const char* to_search_in);

  void SpliceIn(const char* pattern, DNAstrand& to_splice_in);

private:
  Node<char>* head_;
  Node<char>* tail_;
};

#endif