#include <iostream>
#include <string>

#include "board.hpp"

using namespace std;

int main() {
  Board student;  // NOLINT
  InitBoard(student);
  for (size_t i = 0; i < student.kBoardHeight; i++) {
    for (size_t j = 0; j < student.kBoardWidth; j++) {
      cout << " " << to_string(i) << to_string(j) << " ";
    }
    cout << endl;
  }

  student.board[0][6] = DiskType::kPlayer1;
  student.board[1][5] = DiskType::kPlayer1;
  student.board[2][4] = DiskType::kPlayer1;
  student.board[3][3] = DiskType::kPlayer1;
  std::cout << LeftDiagonal(student, DiskType::kPlayer1) << std::endl;

  /**SECTION("Get true when win is in the left diagonal in the middle") {
    student.board[0][4] = DiskType::kPlayer1;
    student.board[1][3] = DiskType::kPlayer1;
    student.board[2][2] = DiskType::kPlayer1;
    student.board[3][1] = DiskType::kPlayer1;
    REQUIRE(CheckLeftDiagonal(student, DiskType::kPlayer1));
  }
  SECTION("Get true when win is in the left diagonal on the right") {
    student.board[4][1] = DiskType::kPlayer1;
    student.board[3][2] = DiskType::kPlayer1;
    student.board[2][3] = DiskType::kPlayer1;
    student.board[1][4] = DiskType::kPlayer1;
    REQUIRE(CheckLeftDiagonal(student, DiskType::kPlayer1));
  }*/
}
