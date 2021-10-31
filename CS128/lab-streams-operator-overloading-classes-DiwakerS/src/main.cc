#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "course.hpp"
#include "student.hpp"

int main() {
  std::ostringstream ss;
  string ans =
      "Name: Ike South\nUIN: 000000000\nNet Id: ike\nMajor: "
      "Undeclared\nCredits: 0\nCourses: \nGraduated: False";
  Student st("Ike South", "000000000", "ike");
  ss << st;
  std::cout << ss.str();
  return 0;
}
