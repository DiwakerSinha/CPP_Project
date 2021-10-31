#ifndef UTIL2_H
#define UTIL2_H

#include "person.hpp"

// Creates an array of friends on the free store
//
// @param num_friends the size of the array on the free store
// @return the array of friends initialized on the free store
Person* MakeFriends( int num_friends );

// Deletes the array of friends on the free store
//
// @param friends the array to be deleted
// @param num_friends the number of elements in the array
void DeleteFriends( Person* friends, int num_friends );

#endif  // UTIL2_H