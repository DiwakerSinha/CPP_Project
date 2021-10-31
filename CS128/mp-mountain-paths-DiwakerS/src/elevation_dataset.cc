#include "elevation_dataset.hpp"

#include <limits>
using namespace std;

ElevationDataset::ElevationDataset(const std::string& file,
                                   size_t width,
                                   size_t height) {
  width_ = width;
  height_ = height;

  ifstream ifs(file);  // opening the file
  if (!(ifs.is_open())) {
    throw runtime_error("Cannot open file");
  }

  vector<int> unformatted_values;  // to store the values in a one d array

  while (ifs.good()) {
    int temp = 0;
    ifs >> temp;
    if (ifs.fail()) {
      if (ifs.bad()) {
        throw runtime_error("Unreachable error");
      }
      ifs.clear();
      ifs.ignore(numeric_limits<streamsize>::max(), '\n');
    } else {
      unformatted_values.push_back(temp);
    }
  }
  // Now, unformatted_values should have read all the values from the file into
  // unformatted_values.
  ifs.close();
  if (width * height != unformatted_values.size()) {
    throw runtime_error("Number of entries don't match");
  }
  max_ele_ = unformatted_values.at(0);
  min_ele_ = unformatted_values.at(0);
  for (size_t i = 0; i < height; i++) {
    vector<int> to_add;
    for (size_t j = 0; j < width; j++) {
      to_add.push_back(unformatted_values[(i * width) + j]);

      if (unformatted_values[(i * width) + j] > max_ele_) {
        max_ele_ = unformatted_values[(i * width) + j];
      }
      if (unformatted_values[(i * width) + j] < min_ele_) {
        min_ele_ = unformatted_values[(i * width) + j];
      }
    }
    data_.push_back(to_add);
  }
}

size_t ElevationDataset::width() const { return width_; }

size_t ElevationDataset::height() const { return height_; }

int ElevationDataset::max_ele() const { return max_ele_; }

int ElevationDataset::min_ele() const { return min_ele_; }

int ElevationDataset::datum_at(size_t row, size_t col) const {
  if ((row >= height_ || row < 0) || (col >= width_ || col < 0)) {
    return 0;
  }
  return data_.at(row).at(col);
}
const std::vector<std::vector<int>>& ElevationDataset::get_data() const {
  return data_;
}