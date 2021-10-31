// clang-format off
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
//  Written By : Michael R. Nowak                Environment : ubuntu:bionic               //
//  Date ......: 2021/02/10                      Compiler ...: clang-10                    //
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
// clang-format on
/////////////////////////////////////////////////////////////////////////////////////////////
//                             Framework Set-up //
/////////////////////////////////////////////////////////////////////////////////////////////
#ifndef CATCH_CONFIG_MAIN
#  define CATCH_CONFIG_MAIN
#endif

#include "catch.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
//                                 Includes //
/////////////////////////////////////////////////////////////////////////////////////////////
#include <stdexcept>

#include "board.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
//                             Helpers/Constants //
/////////////////////////////////////////////////////////////////////////////////////////////
constexpr int kBoardWidth = 7;
constexpr int kBoardHeight = 6;

bool AreEqual(DiskType solution[][kBoardWidth],
              DiskType student[][kBoardWidth]) {
  for (int i = 0; i < kBoardHeight; ++i) {
    for (int j = 0; j < kBoardWidth; ++j) {
      if (solution[i][j] != student[i][j]) return false;
    }
  }
  return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//                                Test Cases //
/////////////////////////////////////////////////////////////////////////////////////////////

// Provided
TEST_CASE("Board initialization", "[board_init]") {
  // SECTION("Can use sections") {}
  // clang-format off
  DiskType solution[kBoardHeight][kBoardWidth] = { 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty} 
  };
  // clang-format on
  Board student;  // NOLINT
  InitBoard(student);
  REQUIRE(AreEqual(solution, student.board));
}

TEST_CASE("BoardLocationInBounds - Row and col in bounds",
          "[BoardLocationInBounds]") {
  Board student;
  InitBoard(student);

  SECTION("Correct Coordinates") { REQUIRE(BoardLocationInBounds(1, 1)); }
  SECTION("Negative Coordinates") {
    REQUIRE_FALSE(BoardLocationInBounds(-1, -1));
  }
  SECTION("row and col > kBoardWidth and kBoardHeight") {
    REQUIRE_FALSE(BoardLocationInBounds(100, 100));
  }
}

TEST_CASE("DropDiskToBoard", "[drop]") {
  Board student;
  InitBoard(student);

  SECTION("Dropping in invalid column") {
    REQUIRE_THROWS_AS(DropDiskToBoard(student, DiskType::kPlayer1, 100),
                      runtime_error);
  }

  SECTION("Adding disk to empty board within bounds") {
    DropDiskToBoard(student, DiskType::kPlayer1, 0);
    REQUIRE(student.board[0][0] == DiskType::kPlayer1);
  }

  SECTION("Filling random column 3 till complete") {
    DropDiskToBoard(student, DiskType::kPlayer1, 3);
    REQUIRE(student.board[0][3] == DiskType::kPlayer1);
    DropDiskToBoard(student, DiskType::kPlayer1, 3);
    REQUIRE(student.board[1][3] == DiskType::kPlayer1);
    DropDiskToBoard(student, DiskType::kPlayer1, 3);
    REQUIRE(student.board[2][3] == DiskType::kPlayer1);
    DropDiskToBoard(student, DiskType::kPlayer1, 3);
    REQUIRE(student.board[3][3] == DiskType::kPlayer1);
    DropDiskToBoard(student, DiskType::kPlayer1, 3);
    REQUIRE(student.board[4][3] == DiskType::kPlayer1);
    DropDiskToBoard(student, DiskType::kPlayer1, 3);
    REQUIRE(student.board[5][3] == DiskType::kPlayer1);
  }
}

TEST_CASE("SearchForWinner - Row", "[row]") {
  Board student;
  InitBoard(student);

  SECTION("Bottom Row - Beginning") {
    DropDiskToBoard(student, DiskType::kPlayer1, 0);
    DropDiskToBoard(student, DiskType::kPlayer1, 1);
    DropDiskToBoard(student, DiskType::kPlayer1, 2);
    DropDiskToBoard(student, DiskType::kPlayer1, 3);
    REQUIRE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kHorizontal));
  }

  SECTION("BOTTOM ROW - MIDDLE") {
    DropDiskToBoard(student, DiskType::kPlayer1, 1);
    DropDiskToBoard(student, DiskType::kPlayer1, 2);
    DropDiskToBoard(student, DiskType::kPlayer1, 3);
    DropDiskToBoard(student, DiskType::kPlayer1, 4);
    REQUIRE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kHorizontal));
  }

  SECTION("BOTTOM ROW- PLAYER 2 DISKS 1ST") {
    DropDiskToBoard(student, DiskType::kPlayer2, 0);
    DropDiskToBoard(student, DiskType::kPlayer1, 1);
    DropDiskToBoard(student, DiskType::kPlayer1, 2);
    DropDiskToBoard(student, DiskType::kPlayer1, 3);
    DropDiskToBoard(student, DiskType::kPlayer1, 4);
    REQUIRE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kHorizontal));
  }

  SECTION("MIDDLE ROW") {
    student.board[3][0] = DiskType::kPlayer1;
    student.board[3][1] = DiskType::kPlayer1;
    student.board[3][2] = DiskType::kPlayer1;
    student.board[3][3] = DiskType::kPlayer1;
    student.board[3][4] = DiskType::kPlayer2;
    student.board[3][5] = DiskType::kPlayer2;
    REQUIRE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kHorizontal));
  }

  SECTION("TOP ROW") {
    student.board[5][0] = DiskType::kPlayer2;
    student.board[5][1] = DiskType::kPlayer1;
    student.board[5][2] = DiskType::kPlayer1;
    student.board[5][3] = DiskType::kPlayer1;
    student.board[5][4] = DiskType::kPlayer1;
    student.board[5][5] = DiskType::kPlayer2;
    REQUIRE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kHorizontal));
  }
}

/////////////////////////////////////////////////////////////////////////////////////////////
