#include "path_image.hpp"

#include <iostream>
using namespace std;

PathImage::PathImage(const GrayscaleImage& image,
                     const ElevationDataset& dataset) {
  width_ = dataset.width();
  height_ = dataset.height();
  path_image_ = image.get_image();
  vector<Path> temp;
  paths_ = temp;

  vector<vector<int>> data = dataset.get_data();
  size_t row = 0;
  while (row < height_) {
    Path to_add(width_, row);
    to_add.path_mapping(data);
    paths_.push_back(to_add);
    row++;
  }

  size_t min_ele = paths_[0].ele_change();
  size_t lowest_ele_row = 0;
  for (size_t i = 0; i < paths_.size(); i++) {
    if (paths_[i].ele_change() < min_ele) {
      min_ele = paths_[i].ele_change();
      lowest_ele_row = i;
    }
  }

  colour(lowest_ele_row);
}

size_t PathImage::width() const { return width_; }

size_t PathImage::height() const { return height_; }

unsigned int PathImage::max_color_value() const { return max_color_value_; }

const std::vector<Path>& PathImage::paths() const { return paths_; }
const std::vector<std::vector<Color>>& PathImage::path_image() const {
  return path_image_;
}

void PathImage::to_ppm(const std::string& name) const {
  ofstream ppm(name);
  if (ppm.is_open()) {
    ppm << "P3" << endl;
    ppm << width_ << " " << height_ << endl;
    ppm << max_color_value_ << endl;
    for (size_t i = 0; i < path_image_.size(); i++) {
      for (size_t j = 0; j < path_image_[i].size(); j++) {
        ppm << path_image_[i][j].red() << " " << path_image_[i][j].green()
            << " " << path_image_[i][j].blue() << " ";
      }
      ppm << endl;
    }
  }
  ppm.close();
}

void PathImage::colour(size_t lowest_ele_row) {
  for (size_t i = 0; i < height_; i++) {
    for (size_t j = 0; j < paths_[i].length(); j++) {
      Color red(252, 25, 63);
      path_image_[paths_[i].path()[j]][j] = red;
    }
  }

  for (size_t i = 0; i < paths_[lowest_ele_row].length(); i++) {
    Color green(31, 253, 13);
    path_image_[paths_[lowest_ele_row].path()[i]][i] = green;
  }
}
