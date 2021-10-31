#ifndef UTIL1_H
#define UTIL1_H

#include "ice-cream.hpp"

// Creates an ice cream cone on the free store
//
// @param num_flavors the number of flavors to increment in kFlavors[]
// @param num_scoops the number of pointers to IceCream
// @return the array of IceCream pointers on the free store
IceCream** MakeCone( int num_flavors, int num_scoops );

// Deletes the ice cream cone on the free store
//
// @param cone the cone to delete
// @param cone_size the number of pointers to IceCream in cone
void EatCone( IceCream** cone, int cone_size );

#endif  // UTIL1_H
