#include "board.hpp"

// you might need additional includes
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

using namespace std;
/**************************************************************************/
/* your function definitions                                              */
/**************************************************************************/

void InitBoard(Board& b) {
  for (size_t i = 0; i < Board::kBoardHeight; i++) {
    for (size_t j = 0; j < Board::kBoardWidth; j++) {
      b.board[i][j] = DiskType::kEmpty;
    }
  }
}

void DropDiskToBoard(Board& b, DiskType disk, int col) {
  if (col < 0 || col >= Board::kBoardWidth) {
    throw std::runtime_error("Column out of bounds");
  }

  for (size_t i = 0; i < Board::kBoardHeight; i++) {
    if (b.board[i][col] == DiskType::kEmpty) {
      b.board[i][col] = disk;
      return;
    }
  }

  throw std::runtime_error("Column full");
}

bool CheckForWinner(Board& b, DiskType disk) {
  return SearchForWinner(b, disk, WinningDirection::kHorizontal) ||
         SearchForWinner(b, disk, WinningDirection::kVertical) ||
         SearchForWinner(b, disk, WinningDirection::kRightDiag) ||
         SearchForWinner(b, disk, WinningDirection::kLeftDiag);
}

bool SearchForWinner(Board& b, DiskType disk, WinningDirection to_check) {
  if (to_check == WinningDirection::kHorizontal) {
    return Row(b, disk);

  } else if (to_check == WinningDirection::kVertical) {
    return Column(b, disk);

  } else if (to_check == WinningDirection::kLeftDiag) {
    return LeftDiagonal(b, disk);

  } else if (to_check == WinningDirection::kRightDiag) {
    return RightDiagonal(b, disk);
  }

  return false;
}

bool Row(Board& b, DiskType disk) {
  string to_compare = "";
  to_compare += static_cast<char>(disk);

  // To create a str of 4 disks
  to_compare = to_compare + to_compare + to_compare + to_compare;

  string row = "";
  for (size_t i = 0; i < Board::kBoardHeight; i++) {
    for (size_t j = 0; j < Board::kBoardWidth; j++) {
      row += static_cast<char>(b.board[i][j]);
    }
    if (row.find(to_compare) != string::npos) {
      return true;
    }
    row = "";
  }
  return false;
}

bool Column(Board& b, DiskType disk) {
  string to_compare = "";
  to_compare += static_cast<char>(disk);
  // To create a str of 4 disks
  to_compare = to_compare + to_compare + to_compare + to_compare;

  string column = "";
  for (size_t i = 0; i < Board::kBoardWidth; i++) {
    for (size_t j = 0; j < Board::kBoardHeight; j++) {
      column += static_cast<char>(b.board[j][i]);
    }
    if (column.find(to_compare) != string::npos) {
      return true;
    }
    column = "";
  }
  return false;
}

bool LeftDiagonal(Board& b, DiskType disk) {
  string to_compare = "";
  to_compare += static_cast<char>(disk);
  // To create a str of 4 disks
  to_compare = to_compare + to_compare + to_compare + to_compare;

  for (size_t i = 0; i <= Board::kBoardHeight - 1; i++) {
    for (size_t j = 0; j <= Board::kBoardWidth - 1; j++) {
      size_t row = i;
      size_t col = j;
      string left_diagonal = "";
      while (BoardLocationInBounds(row, col)) {
        if (b.board[row][col] != DiskType::kEmpty) {
          left_diagonal += static_cast<char>(b.board[row][col]);
        }
        row++;
        col--;

        if (left_diagonal.length() < 4) {
          continue;
        }
      }
      if (left_diagonal.find(to_compare) != string::npos) {
        return true;
      }
    }
  }
  return false;
}

// Still need to implement
bool RightDiagonal(Board& b, DiskType disk) {
  string to_compare = "";
  to_compare += static_cast<char>(disk);
  // To create a str of 4 disks
  to_compare = to_compare + to_compare + to_compare + to_compare;

  for (size_t i = 0; i <= Board::kBoardHeight - 1; i++) {
    for (size_t j = 0; j <= Board::kBoardWidth - 1; j++) {
      size_t row = i;
      size_t col = j;
      string right_diagonal = "";
      while (BoardLocationInBounds(row, col)) {
        if (b.board[row][col] != DiskType::kEmpty) {
          right_diagonal += static_cast<char>(b.board[row][col]);
        }
        row++;
        col++;

        if (right_diagonal.length() < 4) {
          continue;
        }
      }
      if (right_diagonal.find(to_compare) != string::npos) {
        return true;
      }
    }
  }
  return false;
}

bool BoardLocationInBounds(int row, int col) {
  if ((row < 0 || row >= Board::kBoardHeight) ||
      (col < 0 || col >= Board::kBoardWidth)) {
    return false;
  }
  return true;
}

/**************************************************************************/
/* provided to you                                                        */
/**************************************************************************/
std::string BoardToStr(const Board& b) {
  constexpr int kTotalWidth = Board::kBoardWidth * 11 - Board::kBoardHeight - 1;
  std::stringstream ss;
  ss << std::endl;
  for (int row = Board::kBoardHeight; row > 0; --row) {
    ss << " |";
    for (int col = 0; col < Board::kBoardWidth; ++col) {
      std::string value_here;
      value_here.push_back(static_cast<char>(b.board[row - 1][col]));
      ss << ' ' << CenterStr(value_here, Board::kBoardWidth + 1) << '|';
    }
    ss << std::endl;
    ss << " |" << std::setw(kTotalWidth) << std::setfill('-') << '|'
       << std::endl;
  }
  ss << " |";
  for (int col = 0; col < Board::kBoardWidth; ++col) {
    ss << ' ' << CenterStr(std::to_string(col), Board::kBoardWidth + 1) << '|';
  }
  return ss.str();
}

std::string CenterStr(const std::string& str, int col_width) {
  // quick and easy (but error-prone) implementation
  auto padl = (col_width - str.length()) / 2;
  auto padr = (col_width - str.length()) - padl;
  std::string strf = std::string(padl, ' ') + str + std::string(padr, ' ');
  return strf;
}