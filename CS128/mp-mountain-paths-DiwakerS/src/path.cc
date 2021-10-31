#include "path.hpp"

#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;

Path::Path(size_t length, size_t starting_row) {
  length_ = length;
  starting_row_ = starting_row;
}

size_t Path::length() const { return length_; }

size_t Path::starting_row() const { return starting_row_; }

unsigned int Path::ele_change() const { return ele_change_; }

void Path::inc_ele_change(unsigned int value) { ele_change_ += value; }

const std::vector<size_t>& Path::path() const { return path_; }

void Path::set_loc(size_t col, size_t row) { path_[col] = row; }

void Path::path_mapping(vector<vector<int>> dataset) {
  size_t row = starting_row_;
  path_.push_back(starting_row_);
  // cout << row << " ";
  if (dataset.size() == 0) {
    return;
  }
  if (row >= dataset.size()) {
    throw runtime_error("Out of bounds");
  }
  if (dataset.size() == 1) {
    for (size_t i = 0; i < dataset[0].size(); i++) {
      path_.push_back(dataset[0][i]);
      return;
    }
  }

  for (size_t i = 1; i < length_; i++) {
    if (row == 0) {
      auto greater_index_row = abs(dataset[row][i - 1] - dataset[row + 1][i]);
      auto same_row = abs(dataset[row][i - 1] - dataset[row][i]);
      if (greater_index_row <= same_row) {
        inc_ele_change(greater_index_row);
        row++;
      } else {
        inc_ele_change(same_row);
      }
    } else if (row == dataset.size() - 1) {
      auto lower_index_rows = abs(dataset[row][i - 1] - dataset[row - 1][i]);
      auto same_row = abs(dataset[row][i - 1] - dataset[row][i]);
      if (lower_index_rows < same_row) {
        inc_ele_change(lower_index_rows);
        row--;
      } else {
        inc_ele_change(same_row);
      }
    } else {  // Now three possible paths
      auto lower_index_rows = abs(dataset[row][i - 1] - dataset[row - 1][i]);
      auto same_rows = abs(dataset[row][i - 1] - dataset[row][i]);
      auto greater_index_rows = abs(dataset[row][i - 1] - dataset[row + 1][i]);

      if ((same_rows <= lower_index_rows) && (same_rows < greater_index_rows)) {
        inc_ele_change(same_rows);
      } else if ((lower_index_rows < same_rows) &&
                 (lower_index_rows < greater_index_rows)) {
        inc_ele_change(lower_index_rows);
        row--;
      } else {
        inc_ele_change(greater_index_rows);
        row++;
      }
    }
    path_.push_back(row);
  }
}