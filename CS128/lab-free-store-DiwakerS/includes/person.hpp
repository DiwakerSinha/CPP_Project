#ifndef PERSON_H
#define PERSON_H

#include <string>

#include "ice-cream.hpp"

struct Person {
  static const int kNumNameOptions = 10;
  static const std::string kNames[];
  std::string name;
  IceCream** cone;
};

#endif  // PERSON_H
