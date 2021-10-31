#include "util2.hpp"

#include <iostream>

#include "util1.hpp"

const std::string Person::kNames[] = {"Alice",
                                      "Bob",
                                      "Carlos",
                                      "Dave",
                                      "Erin",
                                      "Frank",
                                      "Grace",
                                      "Heidi",
                                      "Ivan",
                                      "Judy"};

Person* MakeFriends(int num_friends) {
  Person* friends = new Person[num_friends];

  for (int i = 0; i < num_friends; i++) {
    friends[i].name = Person::kNames[i % Person::kNumNameOptions];
    friends[i].cone = MakeCone(i + 1, 2);
  }

  return friends;
}

void DeleteFriends(Person* friends, int num_friends) {
  for (int i = 0; i < num_friends; i++) {
    EatCone(friends[i].cone, 2);
  }
}
