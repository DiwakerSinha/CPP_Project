#include "image_ppm.hpp"

// implement the rest of ImagePPM's functions here

// given functions below, DO NOT MODIFY

ImagePPM::ImagePPM() {
  height_ = 0;
  width_ = 0;
  max_color_value_ = 0;
  pixels_ = nullptr;
}

ImagePPM::ImagePPM(const std::string& path) {
  height_ = 0;
  width_ = 0;
  max_color_value_ = 0;
  pixels_ = nullptr;

  std::ifstream input_file(path);
  input_file >> *this;
  input_file.close();
}

ImagePPM::ImagePPM(const ImagePPM& source) {
  height_ = 0;
  width_ = 0;
  max_color_value_ = 0;
  pixels_ = nullptr;

  *this = source;
}

ImagePPM& ImagePPM::operator=(const ImagePPM& source) {
  if (this == &source) {
    return *this;
  }

  Clear();

  height_ = source.height_;
  width_ = source.width_;
  max_color_value_ = source.max_color_value_;

  pixels_ = new Pixel*[height_];
  for (int row = 0; row < height_; row++) {
    pixels_[row] = new Pixel[width_];

    for (int col = 0; col < width_; col++) {
      pixels_[row][col] = source.pixels_[row][col];
    }
  }

  return *this;
}

ImagePPM::~ImagePPM() { Clear(); }

void ImagePPM::Clear() {
  for (int i = 0; i < height_; i++) {
    delete[] pixels_[i];
  }

  delete[] pixels_;

  height_ = 0;
  width_ = 0;
  pixels_ = nullptr;
}

std::istream& operator>>(std::istream& is, ImagePPM& image) {
  image.Clear();
  std::string line;

  // ignore magic number line
  getline(is, line);

  // check to see if there's a comment line
  getline(is, line);
  if (line[0] == '#') {
    getline(is, line);
  }

  // parse width and height
  int space = line.find_first_of(' ');
  image.width_ = std::stoi(line.substr(0, space));
  image.height_ = std::stoi(line.substr(space + 1));

  // get max color value
  getline(is, line);
  image.max_color_value_ = std::stoi(line);

  // init and fill in Pixels array
  image.pixels_ = new Pixel*[image.height_];
  for (int i = 0; i < image.height_; i++) {
    image.pixels_[i] = new Pixel[image.width_];
  }

  for (int row = 0; row < image.height_; row++) {
    for (int col = 0; col < image.width_; col++) {
      getline(is, line);
      int red = std::stoi(line);
      getline(is, line);
      int green = std::stoi(line);
      getline(is, line);
      int blue = std::stoi(line);

      Pixel p(red, green, blue);
      image.pixels_[row][col] = p;
    }
  }

  return is;
}

// Implemented functions below

Pixel ImagePPM::GetPixel(int row, int col) const {
  if (row < 0 || row >= height_) {
    throw runtime_error("Out of bounds");
  }
  if (col < 0 || col >= width_) {
    throw runtime_error("Out of bounds");
  }
  return pixels_[row][col];
}

int ImagePPM::GetWidth() const { return width_; }

int ImagePPM::GetHeight() const { return height_; }

int ImagePPM::GetMaxColorValue() const { return max_color_value_; }

ostream& operator<<(std::ostream& os, const ImagePPM& image) {
  os << "P3" << endl;
  os << image.GetWidth() << " " << image.GetHeight() << endl;
  os << image.GetMaxColorValue() << endl;
  for (int i = 0; i < image.GetHeight(); i++) {
    for (int j = 0; j < image.GetHeight(); j++) {
      Pixel pixel = image.GetPixel(i, j);
      os << pixel.GetRed() << endl;
      os << pixel.GetGreen() << endl;
      os << pixel.GetBlue() << endl;
    }
  }
  return os;
}

void ImagePPM::RemoveHorizontalSeam(int* seam) {
  Pixel** newPixels = new Pixel*[height_ - 1];
  for (int i = 0; i < height_ - 1; i++) {
    newPixels[i] = new Pixel[width_];
  }
  for (int i = 0; i < width_; i++) {
    int temp = 0;
    for (int j = 0; j < height_; j++) {
      if (seam[i] != j) {
        newPixels[temp][i] = pixels_[j][i];
        temp++;
      }
    }
  }
  for (int i = 0; i < height_; ++i) {
    delete pixels_[i];
  }
  delete[] pixels_;
  pixels_ = newPixels;
  height_--;
}

void ImagePPM::RemoveVerticalSeam(int* seam) {
  Pixel** newPixels = new Pixel*[height_];
  for (int i = 0; i < height_; i++) {
    newPixels[i] = new Pixel[width_ - 1];
  }
  for (int i = 0; i < height_; i++) {
    int temp = 0;
    for (int j = 0; j < width_; j++) {
      if (seam[i] != j) {
        newPixels[i][temp] = pixels_[i][j];
        temp++;
      }
    }
  }
  for (int i = 0; i < height_; ++i) {
    delete pixels_[i];
  }
  delete[] pixels_;
  pixels_ = newPixels;
  width_--;
}