#include "seam_carver.hpp"

// implement the rest of SeamCarver's functions here

// given functions below, DO NOT MODIFY

SeamCarver::SeamCarver(const ImagePPM& image): image_(image) {
  height_ = image.GetHeight();
  width_ = image.GetWidth();
}

void SeamCarver::SetImage(const ImagePPM& image) {
  image_ = image;
  width_ = image.GetWidth();
  height_ = image.GetHeight();
}

// Implemented functions below

const ImagePPM& SeamCarver::GetImage() const { return image_; }

int SeamCarver::GetHeight() const { return height_; }

int SeamCarver::GetWidth() const { return width_; }

int SeamCarver::GetEnergy(int row, int col) const { return energy_[row][col]; }

int* SeamCarver::GetHorizontalSeam() {
  energy_ = new int*[height_];

  for (int i = 0; i < height_; i++) {
    energy_[i] = new int[width_];
  }

  for (int i = 0; i < height_; i++) {
    for (int j = 0; j < width_; j++) {
      if (i == 0) {
        ZeroRow(i, j);
      } else if (j == 0) {
        ZeroColumn(i, j);
      } else if (i == height_ - 1) {
        LastRow(i, j);
      } else if (j == width_ - 1) {
        LastColumn(i, j);
      } else {
        Internal(i, j);
      }
    }
  }

  int** grid = new int*[height_];

  // Allocating memory
  for (int i = 0; i < height_; i++) {
    grid[i] = new int[width_];
  }

  for (int i = width_ - 2; i >= 0; i--) {
    for (int j = 0; j < height_; j++) {
      int minimun;
      if (j == 0) {
        minimun = Minimum(grid[j][i + 1], grid[j + 1][i + 1]);
      } else if (j == height_ - 1) {
        minimun = Minimum(grid[j][i + 1], grid[j - 1][i + 1]);
      } else {
        minimun =
            Minimum(grid[j][i + 1], grid[j + 1][i + 1], grid[j - 1][i + 1]);
      }
      grid[j][i] = GetEnergy(j, i) + minimun;
    }
  }
  for (int i = 0; i < height_; i++) {
    grid[i][width_ - 1] = GetEnergy(i, width_ - 1);
  }

  int* to_return = new int[width_];
  int minimum = 99999999;
  int min_row = 0;
  for (int i = 0; i < height_; i++) {
    if (grid[i][0] < minimum) {
      minimum = grid[i][0];
      min_row = i;
    } else {
      continue;
    }
  }

  to_return[0] = min_row;
  for (int i = 1; i < width_; i++) {
    int same_row = grid[min_row][i];
    int index_lesser = grid[min_row - 1][i];
    int index_greater = grid[min_row + 1][i];
    if (min_row == 0) {
      if (same_row <= index_greater) {
        to_return[i] = min_row;
      } else {
        min_row++;
        to_return[i] = min_row;
      }
    } else if (min_row == height_ - 1) {
      if (same_row <= index_lesser) {
        to_return[i] = min_row;
      } else {
        min_row--;
        to_return[i] = min_row;
      }
    } else if ((same_row <= index_lesser) && (same_row <= index_greater)) {
      to_return[i] = min_row;
    } else if ((index_lesser < same_row) && (index_lesser <= index_greater)) {
      min_row--;
      to_return[i] = min_row;
    } else if ((index_greater < index_lesser) && (index_greater < same_row)) {
      min_row++;
      to_return[i] = min_row;
    }
  }

  // for (int i = 0; i < height_; ++i) {
  //   delete grid[i];
  // }
  // delete[] grid;

  return to_return;
}

int SeamCarver::Minimum(int x, int y) const {
  int to_return = (x <= y) ? x : y;
  return to_return;
}

int SeamCarver::Minimum(int x, int y, int z) const {
  int to_return = (x <= y) ? x : y;
  to_return = (to_return <= z) ? to_return : z;
  return to_return;
}

int* SeamCarver::GetVerticalSeam() {
  energy_ = new int*[height_];

  for (int i = 0; i < height_; i++) {
    energy_[i] = new int[width_];
  }

  for (int i = 0; i < height_; i++) {
    for (int j = 0; j < width_; j++) {
      if (i == 0) {
        ZeroRow(i, j);
      } else if (j == 0) {
        ZeroColumn(i, j);
      } else if (i == height_ - 1) {
        LastRow(i, j);
      } else if (j == width_ - 1) {
        LastColumn(i, j);
      } else {
        Internal(i, j);
      }
    }
  }

  int** grid = new int*[height_];
  for (int i = 0; i < height_; i++) {
    grid[i] = new int[width_];
  }

  for (int i = height_ - 2; i >= 0; i--) {
    for (int j = 0; j < width_; j++) {
      int minimum;
      if (j == 0) {
        minimum = Minimum(grid[i + 1][j], grid[i + 1][j + 1]);
      } else if (j == width_ - 1) {
        minimum = Minimum(grid[i + 1][j], grid[i + 1][j - 1]);
      } else {
        minimum =
            Minimum(grid[i + 1][j - 1], grid[i + 1][j], grid[i + 1][j + 1]);
      }
      grid[i][j] = GetEnergy(i, j) + minimum;
    }
  }

  for (int i = 0; i < width_; i++) {
    grid[height_ - 1][i] = GetEnergy(height_ - 1, i);
  }

  int* to_return = new int[height_];
  int minimum = 9999999;
  int min_col = 0;

  for (int i = 0; i < width_; i++) {
    if (grid[0][i] < minimum) {
      minimum = grid[0][i];
      min_col = i;
    } else {
      continue;
    }
  }

  to_return[0] = min_col;

  for (int i = 1; i < height_; i++) {
    int same_row = grid[i][min_col];
    int index_lesser = grid[i][min_col - 1];
    int index_greater = grid[i][min_col + 1];
    if (min_col == 0) {
      if (same_row <= index_greater) {
        to_return[i] = min_col;
      } else {
        min_col++;
        to_return[i] = min_col;
      }
    } else if (min_col == width_ - 1) {
      if (same_row <= index_lesser) {
        to_return[i] = min_col;
      } else {
        min_col--;
        to_return[i] = min_col;
      }
    } else if ((same_row <= index_lesser) && (same_row <= index_greater)) {
      to_return[i] = min_col;
    } else if ((index_lesser < same_row) && (index_lesser <= index_greater)) {
      min_col--;
      to_return[i] = min_col;
    } else if ((index_greater < index_lesser) && (index_greater < same_row)) {
      min_col++;
      to_return[i] = min_col;
    }
  }

  // for (int i = 0; i < height_; ++i) {
  //   delete grid[i];
  // }
  // delete[] grid;

  return to_return;
}

void SeamCarver::RemoveHorizontalSeam() {
  if (height_ >= 1) {
    int* seam = GetHorizontalSeam();
    image_.RemoveHorizontalSeam(seam);
    height_--;
    delete[] seam;

    energy_ = new int*[height_];

    for (int i = 0; i < height_; i++) {
      energy_[i] = new int[width_];
    }

    for (int i = 0; i < height_; i++) {
      for (int j = 0; j < width_; j++) {
        if (i == 0) {
          ZeroRow(i, j);
        } else if (j == 0) {
          ZeroColumn(i, j);
        } else if (i == height_ - 1) {
          LastRow(i, j);
        } else if (j == width_ - 1) {
          LastColumn(i, j);
        } else {
          Internal(i, j);
        }
      }
    }
  }
  // free(this);
}

void SeamCarver::RemoveVerticalSeam() {
  if (height_ >= 1) {
    energy_ = new int*[height_];

    for (int i = 0; i < height_; i++) {
      energy_[i] = new int[width_];
    }

    for (int i = 0; i < height_; i++) {
      for (int j = 0; j < width_; j++) {
        if (i == 0) {
          ZeroRow(i, j);
        } else if (j == 0) {
          ZeroColumn(i, j);
        } else if (i == height_ - 1) {
          LastRow(i, j);
        } else if (j == width_ - 1) {
          LastColumn(i, j);
        } else {
          Internal(i, j);
        }
      }
    }

    if (width_ >= 1) {
      int* seam = GetVerticalSeam();
      image_.RemoveVerticalSeam(seam);
      width_--;
      delete[] seam;
    }

    energy_ = new int*[height_];

    for (int i = 0; i < height_; i++) {
      energy_[i] = new int[width_];
    }

    for (int i = 0; i < height_; i++) {
      for (int j = 0; j < width_; j++) {
        if (i == 0) {
          ZeroRow(i, j);
        } else if (j == 0) {
          ZeroColumn(i, j);
        } else if (i == height_ - 1) {
          LastRow(i, j);
        } else if (j == width_ - 1) {
          LastColumn(i, j);
        } else {
          Internal(i, j);
        }
      }
    }
  }

  // free(this);
}

void SeamCarver::ZeroRow(int row, int col) {
  Pixel up = image_.GetPixel(height_ - 1, col);
  Pixel down = image_.GetPixel(row + 1, col);

  Pixel left;
  if (col == 0) {
    left = image_.GetPixel(row, width_ - 1);
  } else {
    left = image_.GetPixel(row, col - 1);
  }

  Pixel right;
  if (col == width_ - 1) {
    right = image_.GetPixel(row, 0);
  } else {
    right = image_.GetPixel(row, col + 1);
  }

  int row_energy =
      ((up.GetRed() - down.GetRed()) * (up.GetRed() - down.GetRed()));
  row_energy +=
      ((up.GetGreen() - down.GetGreen()) * (up.GetGreen() - down.GetGreen()));
  row_energy +=
      ((up.GetBlue() - down.GetBlue()) * (up.GetBlue() - down.GetBlue()));

  int col_energy =
      ((left.GetRed() - right.GetRed()) * (left.GetRed() - right.GetRed()));
  col_energy += ((left.GetGreen() - right.GetGreen()) *
                 (left.GetGreen() - right.GetGreen()));
  col_energy +=
      ((left.GetBlue() - right.GetBlue()) * (left.GetBlue() - right.GetBlue()));
  energy_[row][col] = row_energy + col_energy;
}

void SeamCarver::ZeroColumn(int row, int col) {
  Pixel left = image_.GetPixel(row, width_ - 1);
  Pixel right = image_.GetPixel(row, col + 1);

  Pixel up;
  if (row == 0) {
    up = image_.GetPixel(height_ - 1, col);
  } else {
    up = image_.GetPixel(row - 1, col);
  }
  Pixel down;
  if (row == height_ - 1) {
    down = image_.GetPixel(0, col);
  } else {
    down = image_.GetPixel(row + 1, col);
  }
  int row_energy =
      (up.GetRed() - down.GetRed()) * (up.GetRed() - down.GetRed());
  row_energy +=
      (up.GetGreen() - down.GetGreen()) * (up.GetGreen() - down.GetGreen());
  row_energy +=
      (up.GetBlue() - down.GetBlue()) * (up.GetBlue() - down.GetBlue());

  int col_energy =
      (left.GetRed() - right.GetRed()) * (left.GetRed() - right.GetRed());
  col_energy += (left.GetGreen() - right.GetGreen()) *
                (left.GetGreen() - right.GetGreen());
  col_energy +=
      (left.GetBlue() - right.GetBlue()) * (left.GetBlue() - right.GetBlue());

  energy_[row][col] = row_energy + col_energy;
}

void SeamCarver::LastRow(int row, int col) {
  Pixel up = image_.GetPixel(row - 1, col);
  Pixel down = image_.GetPixel(0, col);
  Pixel left;
  if (col == 0) {
    left = image_.GetPixel(row, width_ - 1);
  } else {
    left = image_.GetPixel(row, col - 1);
  }
  Pixel right;
  if (col == width_ - 1) {
    right = image_.GetPixel(row, 0);
  } else {
    right = image_.GetPixel(row, col + 1);
  }

  int row_energy =
      (up.GetRed() - down.GetRed()) * (up.GetRed() - down.GetRed());
  row_energy +=
      (up.GetGreen() - down.GetGreen()) * (up.GetGreen() - down.GetGreen());
  row_energy +=
      (up.GetBlue() - down.GetBlue()) * (up.GetBlue() - down.GetBlue());

  int col_energy =
      (left.GetRed() - right.GetRed()) * (left.GetRed() - right.GetRed());
  col_energy += (left.GetGreen() - right.GetGreen()) *
                (left.GetGreen() - right.GetGreen());
  col_energy +=
      (left.GetBlue() - right.GetBlue()) * (left.GetBlue() - right.GetBlue());

  energy_[row][col] = row_energy + col_energy;
}

void SeamCarver::LastColumn(int row, int col) {
  Pixel left = image_.GetPixel(row, col - 1);
  Pixel right = image_.GetPixel(row, 0);

  Pixel up;
  if (row == 0) {
    up = image_.GetPixel(height_ - 1, col);
  } else {
    up = image_.GetPixel(row - 1, col);
  }

  Pixel down;
  if (row == height_ - 1) {
    down = image_.GetPixel(0, col);
  } else {
    down = image_.GetPixel(row + 1, col);
  }
  int row_energy =
      (up.GetRed() - down.GetRed()) * (up.GetRed() - down.GetRed());
  row_energy +=
      (up.GetGreen() - down.GetGreen()) * (up.GetGreen() - down.GetGreen());
  row_energy +=
      (up.GetBlue() - down.GetBlue()) * (up.GetBlue() - down.GetBlue());

  int col_energy =
      (left.GetRed() - right.GetRed()) * (left.GetRed() - right.GetRed());
  col_energy += (left.GetGreen() - right.GetGreen()) *
                (left.GetGreen() - right.GetGreen());
  col_energy +=
      (left.GetBlue() - right.GetBlue()) * (left.GetBlue() - right.GetBlue());
  energy_[row][col] = row_energy + col_energy;
}

void SeamCarver::Internal(int row, int col) {
  Pixel up = image_.GetPixel(row - 1, col);
  Pixel down = image_.GetPixel(row + 1, col);
  Pixel left = image_.GetPixel(row, col - 1);
  Pixel right = image_.GetPixel(row, col + 1);
  int row_energy =
      (up.GetRed() - down.GetRed()) * (up.GetRed() - down.GetRed());
  row_energy +=
      (up.GetGreen() - down.GetGreen()) * (up.GetGreen() - down.GetGreen());
  row_energy +=
      (up.GetBlue() - down.GetBlue()) * (up.GetBlue() - down.GetBlue());

  int col_energy =
      (left.GetRed() - right.GetRed()) * (left.GetRed() - right.GetRed());
  col_energy += (left.GetGreen() - right.GetGreen()) *
                (left.GetGreen() - right.GetGreen());
  col_energy +=
      (left.GetBlue() - right.GetBlue()) * (left.GetBlue() - right.GetBlue());

  energy_[row][col] = row_energy + col_energy;
}