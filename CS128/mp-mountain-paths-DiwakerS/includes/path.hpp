#ifndef PATH_H
#define PATH_H

#include <cstdlib>  // for size_t
#include <vector>

using namespace std;

class Path {
public:
  Path(size_t length, size_t starting_row);
  size_t length() const;
  size_t starting_row() const;
  unsigned int ele_change() const;
  void inc_ele_change(unsigned int value);
  const std::vector<size_t>& path() const;
  void set_loc(size_t col, size_t row);
  void path_mapping(vector<vector<int>> data);

private:
  std::vector<size_t> path_;
  size_t length_;
  size_t starting_row_;
  unsigned int ele_change_ = 0;
};

#endif