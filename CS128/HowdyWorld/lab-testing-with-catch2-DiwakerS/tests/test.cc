#ifndef CATCH_CONFIG_MAIN
#  define CATCH_CONFIG_MAIN
#endif
#include <catch/catch.hpp>
#include <iostream>
#include <string>
#include <vector>

#include "sandwich.hpp"

using std::string;
using std::vector;

// A helper method for you to visualize what the contents of a vector are. You
// are welcome to modify this method or create additional helper methods.
//
// Example usage:
//  vector<string> my_vec;
//  my_vec.push_back("hello");
//  my_vec.push_back("world"):
//  PrintVector(my_vec);
// Prints:
//  [hello, world]
void PrintVector(const vector<string>& vec) {
  std::cout << "[";
  bool first = true;
  for (const auto& it : vec) {
    if (!first) {
      std::cout << ", ";
    } else {
      first = false;
    }

    std::cout << it;
  }

  std::cout << "]" << std::endl;
}

TEST_CASE("Sandwich::AddTopping test", "[AddTopping]") {
  Sandwich s;
  vector<string> toppings;
  SECTION("Can add toppings from toppings given") {
    REQUIRE(s.AddTopping("cheese"));
    REQUIRE(s.AddTopping("tomato"));
    REQUIRE(s.AddTopping("onions"));
    REQUIRE(s.AddTopping("pickles"));
    REQUIRE(s.AddTopping("lettuce"));
  }

  SECTION("Cannot add cheese more than twice") {
    s.AddTopping("cheese");
    REQUIRE_FALSE(s.AddTopping("cheese"));
  }
}

TEST_CASE("Sandwich::RemoveTopping test", "[RemoveTopping]") {
  Sandwich s;
  vector<string> toppings;
  vector<string> dressings;
  SECTION("Removing toppings from empty snadwich not possible") {
    REQUIRE_FALSE(s.RemoveTopping("cheese"));
    REQUIRE_FALSE(s.RemoveTopping("tomato"));
    REQUIRE_FALSE(s.RemoveTopping("onions"));
    REQUIRE_FALSE(s.RemoveTopping("pickles"));
    REQUIRE_FALSE(s.RemoveTopping("lettuce"));
  }
  /**SECTION("Can remove topping from topping that is already there") {
    s.AddTopping("cheese");
    s.AddTopping("tomato");
    s.AddTopping("onions");
    s.AddTopping("pickles");
    s.AddTopping("lettuce");
    REQUIRE(s.RemoveTopping("cheese"));
    REQUIRE(s.RemoveTopping("tomato"));
    REQUIRE(s.RemoveTopping("onions"));
    REQUIRE(s.RemoveTopping("pickles"));
    REQUIRE(s.RemoveTopping("lettuce"));
  }*/
  SECTION("CANNOT REMOVE ANY TOPPINGS ONLY AFTER ANY SAUCES ARE ADDED") {
    s.AddTopping("cheese");
    s.AddTopping("tomato");
    s.AddTopping("onions");
    s.AddTopping("pickles");
    s.AddTopping("lettuce");
    s.AddDressing("mayo");
    REQUIRE_FALSE(s.RemoveTopping("cheese"));
    REQUIRE_FALSE(s.RemoveTopping("tomato"));
    REQUIRE_FALSE(s.RemoveTopping("onions"));
    REQUIRE_FALSE(s.RemoveTopping("pickles"));
    REQUIRE_FALSE(s.RemoveTopping("lettuce"));
  }
}

TEST_CASE("Sandwich::AddDressing test", "[AddDressing]") {
  Sandwich s;
  vector<string> toppings;
  vector<string> dressings;
  SECTION("CAN'T ADD DRESSING UNTIL THERE IS AT LEAST ONE TOPPING") {
    REQUIRE_FALSE(s.AddDressing("mayo"));
    REQUIRE_FALSE(s.AddDressing("mustard"));
    REQUIRE_FALSE(s.AddDressing("vinegar"));
  }
  SECTION("CAN ADD DRESSING") {
    s.AddTopping("onions");
    REQUIRE(s.AddDressing("mayo"));
    REQUIRE_FALSE(s.AddDressing("mayo"));
  }
  SECTION("NO MORE THAN ONE DRESSING") {
    s.AddDressing("mayo");
    REQUIRE_FALSE(s.AddDressing("mayo"));
    s.AddDressing("mustard");
    REQUIRE_FALSE(s.AddDressing("mustard"));
    s.AddDressing("vinegar");
    REQUIRE_FALSE(s.AddDressing("vinegar"));
  }
}
