#include <iostream>

#include "util2.hpp"

int main() {
  Person* friends = MakeFriends( 5 );

  for ( int i = 0; i < 5; i++ ) {
    std::cout << friends[i].name << " has ";
    for ( int j = 0; j < 2; j++ ) {
      std::cout << friends[i].cone[j]->flavor;
      if ( j == 0 ) {
        std::cout << " and ";
      }
    }
    std::cout << std::endl;
  }

  DeleteFriends( friends, 5 );
}