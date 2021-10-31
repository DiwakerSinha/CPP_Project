#include "bathroom.hpp"

Bathroom::Bathroom(): Room("bathroom") {}

bool Bathroom::CanAddPerson() const {
  if (people_.size() == 0) {
    return true;
  }
  return false;
}