#ifndef ICECREAM_H
#define ICECREAM_H

#include <string>

struct IceCream {
  static constexpr int kNumFlavorOptions = 5;
  static const std::string kFlavors[];
  std::string flavor;
};

#endif  // ICECREAM_H