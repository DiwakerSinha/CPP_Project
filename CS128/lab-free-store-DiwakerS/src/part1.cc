#include <iostream>

#include "util1.hpp"

int main() {
  IceCream** cone = MakeCone( 1, 2 );
  for ( int i = 0; i < 2; ++i ) {
    std::cout << cone[i]->flavor << std::endl;
  }

  EatCone( cone, 2 );
}