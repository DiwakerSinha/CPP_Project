#ifndef PATH_IMAGE_H
#define PATH_IMAGE_H

#include <cstdlib>  // for size_t
#include <vector>

#include "color.hpp"
#include "grayscale_image.hpp"
#include "path.hpp"

class PathImage {
public:
  PathImage(const GrayscaleImage& image, const ElevationDataset& dataset);
  size_t width() const;
  size_t height() const;
  unsigned int max_color_value() const;
  const std::vector<Path>& paths() const;
  const std::vector<std::vector<Color>>& path_image() const;
  void to_ppm(const std::string& name) const;
  void colour(size_t lowest_ele_row);

private:
  std::vector<Path> paths_;
  std::vector<std::vector<Color>> path_image_;
  size_t width_;
  size_t height_;
  static const int max_color_value_ = 255;
};

#endif