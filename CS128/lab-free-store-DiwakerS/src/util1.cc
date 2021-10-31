#include "util1.hpp"

#include <iostream>

const std::string IceCream::kFlavors[] = {"chocolate",
                                          "vanilla",
                                          "strawberry",
                                          "mint-chocolate-chip",
                                          "snickerdoodle"};

IceCream** MakeCone(int num_flavors, int num_scoops) {
  IceCream** cone = new IceCream*[num_scoops];

  // hint, you don't need to edit below here!

  if (num_flavors > IceCream::kNumFlavorOptions) {
    num_flavors = IceCream::kNumFlavorOptions;
  }

  for (int i = 0, f = 0; i < num_scoops; ++i, f = (f + 1) % num_flavors) {
    cone[i] = new IceCream();
    cone[i]->flavor = IceCream::kFlavors[f];
  }

  return cone;
}

void EatCone(IceCream** cone, int cone_size) {
  // something else needs to be done here!
  for (int i = 0; i < cone_size; i++) {
    delete cone[i];
  }
}
