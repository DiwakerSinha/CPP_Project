#include "grayscale_image.hpp"

#include <cmath>

GrayscaleImage::GrayscaleImage(const ElevationDataset& dataset) {
  height_ = dataset.height();
  width_ = dataset.width();

  vector<vector<int>> data = dataset.get_data();
  if (dataset.max_ele() != dataset.min_ele()) {
    for (size_t i = 0; i < height_; i++) {
      vector<Color> to_add;
      for (size_t j = 0; j < width_; j++) {
        int color_at_index =
            std::round((double)((data[i][j]) - dataset.min_ele()) * 255 /
                       (double)(dataset.max_ele() - dataset.min_ele()));
        Color temp(color_at_index, color_at_index, color_at_index);
        to_add.push_back(temp);
      }
      image_.push_back(to_add);
    }
  } else {
    for (size_t i = 0; i < height_; i++) {
      vector<Color> to_add;
      for (size_t j = 0; j < width_; j++) {
        Color temp(0, 0, 0);
        to_add.push_back(temp);
      }
      image_.push_back(to_add);
    }
  }
}
GrayscaleImage::GrayscaleImage(const std::string& path,
                               size_t width,
                               size_t height) {
  ElevationDataset dataset(path, width, height);
  height_ = dataset.height();
  width_ = dataset.width();
  vector<vector<int>> data = dataset.get_data();
  if (dataset.max_ele() != dataset.min_ele()) {
    for (size_t i = 0; i < height_; i++) {
      vector<Color> to_add;
      for (size_t j = 0; j < width_; j++) {
        int color_at_index =
            std::round((double)((data[i][j]) - dataset.min_ele()) * 255 /
                       (double)(dataset.max_ele() - dataset.min_ele()));
        Color temp(color_at_index, color_at_index, color_at_index);
        to_add.push_back(temp);
      }
      image_.push_back(to_add);
    }
  } else {
    for (size_t i = 0; i < height_; i++) {
      vector<Color> to_add;
      for (size_t j = 0; j < width_; j++) {
        Color temp(0, 0, 0);
        to_add.push_back(temp);
      }
      image_.push_back(to_add);
    }
  }
}

size_t GrayscaleImage::width() const { return width_; }

size_t GrayscaleImage::height() const { return height_; }
unsigned int GrayscaleImage::max_color_value() const {
  return max_color_value_;
}
const Color& GrayscaleImage::color_at(int row, int col) const {
  if (((unsigned)row >= height_) || ((unsigned)col >= width_)) {
    return image_[0][0];
  }
  return image_.at((unsigned)row).at((unsigned)col);
}
const std::vector<std::vector<Color>>& GrayscaleImage::get_image() const {
  return image_;
}

void GrayscaleImage::to_ppm(const std::string& name) const {
  ofstream ppm(name);
  if (ppm.is_open()) {
    ppm << "P3" << endl;
    ppm << width_ << " " << height_ << endl;
    ppm << max_color_value_ << endl;
    for (size_t i = 0; i < height_; i++) {
      for (size_t j = 0; j < width_; j++) {
        Color at_index = color_at(i, j);
        ppm << at_index.red() << " " << at_index.green() << " "
            << at_index.blue() << " " << endl;
      }
    }
  }
  ppm.close();
}
