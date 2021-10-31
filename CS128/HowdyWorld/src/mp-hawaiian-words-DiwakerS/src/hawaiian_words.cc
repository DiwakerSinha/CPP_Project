#include <iostream>
#include <string>

#include "functions.hpp"

using namespace std;

int main(int argc, char** argv) {
  if (argc != 2) {
    std::cerr << "Usage: ./bin/exec word" << std::endl;
    return 1;
  }
  std::string word = argv[1];
  std::string output_p = main(word);
  std::cout << output_p << std::endl;
  return 0;
}