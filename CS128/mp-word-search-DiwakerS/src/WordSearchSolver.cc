#include "WordSearchSolver.hpp"

#include <math.h>

#include <iostream>
#include <string>
#include <vector>

#include "CharPositions.hpp"
#include "WordLocation.hpp"

using namespace std;

WordSearchSolver::WordSearchSolver(
    const std::vector<std::vector<char>>& puzzle) {
  puzzle_ = puzzle;
  puzzle_height_ = puzzle_.size();
  puzzle_width_ = puzzle_.at(0).size();
}

bool WordSearchSolver::LocationInBounds(size_t row, size_t col) const {
  return ((row < puzzle_height_) && (col < puzzle_width_));
}

WordLocation WordSearchSolver::FindWord(const std::string& word) {
  if (FindWord(word, CheckDirection::kHorizontal).char_positions.size() != 0) {
    return FindWord(word, CheckDirection::kHorizontal);

  } else if (FindWord(word, CheckDirection::kVertical).char_positions.size() !=
             0) {
    return (FindWord(word, CheckDirection::kVertical));

  } else if (FindWord(word, CheckDirection::kLeftDiag).char_positions.size() !=
             0) {
    return FindWord(word, CheckDirection::kLeftDiag);

  } else if (FindWord(word, CheckDirection::kRightDiag).char_positions.size() !=
             0) {
    return FindWord(word, CheckDirection::kRightDiag);
  }

  return WordLocation{};
}

WordLocation WordSearchSolver::FindWord(const std::string& word,
                                        CheckDirection direction) {
  if (direction == CheckDirection::kHorizontal) {
    return Row(word);
  } else if (direction == CheckDirection::kVertical) {
    return Column(word);
  } else if (direction == CheckDirection::kLeftDiag) {
    return LeftDiag(word);
  } else if (direction == CheckDirection::kRightDiag) {
    return RightDiag(word);
  } else {
    throw runtime_error("Invalid direction");
  }
  return WordLocation{};  // unreachable statement
}

WordLocation WordSearchSolver::Row(const std::string& word) {
  if (word.length() > puzzle_width_) {
    return WordLocation{};
  }

  for (size_t i = 0; i < puzzle_height_; i++) {
    string row = "";
    size_t width_at_index = 0;

    while (row.length() != puzzle_width_) {
      row = row + puzzle_.at(i).at(width_at_index++);
    }

    if (row.find(word) == string::npos) {
      continue;
    }

    size_t row_index_found = row.find(word);

    WordLocation word_location_to_return;
    word_location_to_return.word = word;
    vector<CharPositions> to_add_to_return;

    for (size_t j = row_index_found; j < row_index_found + word.length(); j++) {
      CharPositions at_index;
      // cout << word.at(j - row_index_found) << endl;
      at_index.character = word.at(j - row_index_found);

      at_index.row = i;
      // cout << at_index.row;

      at_index.col = j;
      // cout << at_index.col;

      to_add_to_return.push_back(at_index);
    }
    word_location_to_return.char_positions = to_add_to_return;
    return word_location_to_return;
  }
  return WordLocation{};
}

WordLocation WordSearchSolver::Column(const std::string& word) {
  if (word.length() > puzzle_height_) {
    return WordLocation{};
  }

  for (size_t i = 0; i < puzzle_width_; i++) {
    string column = "";
    size_t height_at_index = 0;

    while (column.length() != puzzle_height_) {
      column = column + puzzle_.at(height_at_index++).at(i);
    }

    if (column.find(word) == string::npos) {
      continue;
    }

    size_t column_index_found = column.find(word);

    WordLocation word_location_to_return;
    word_location_to_return.word = word;
    vector<CharPositions> to_add_to_return;

    for (size_t j = column_index_found; j < column_index_found + word.length();
         j++) {
      CharPositions at_index;
      at_index.character = word.at(j - column_index_found);
      at_index.row = j;
      at_index.col = i;

      to_add_to_return.push_back(at_index);
    }
    word_location_to_return.char_positions = to_add_to_return;
    return word_location_to_return;
  }
  return WordLocation{};
}

WordLocation WordSearchSolver::RightDiag(const std::string& word) {
  // if (word.length() > (unsigned long)(sqrt(puzzle_height_ * puzzle_height_ +
  //                                          puzzle_width_ * puzzle_width_))) {
  //   return WordLocation{};
  // }

  for (size_t i = 0; i < puzzle_height_; i++) {
    for (size_t j = 0; j < puzzle_width_; j++) {
      string rdiag = "";

      size_t temp_row = i;
      size_t temp_col = j;

      while (LocationInBounds(temp_row, temp_col)) {
        rdiag = rdiag + puzzle_.at(temp_row).at(temp_col);
        temp_row++;
        temp_col++;
      }

      if (rdiag.find(word) == string::npos) {
        continue;
      }

      // for (size_t x = 0; x < puzzle_height_; x++) {
      //   for (size_t y = 0; y < puzzle_width_; y++) {
      //     cout << puzzle_.at(x).at(y) << " ";
      //   }
      //   cout << endl;
      // }

      size_t diag_index_found = rdiag.find(word);

      WordLocation word_location_to_return;
      word_location_to_return.word = word;
      vector<CharPositions> to_add_to_return;

      temp_row = i + diag_index_found;
      temp_col = j + diag_index_found;

      for (size_t k = diag_index_found; k < diag_index_found + word.length();
           k++) {
        CharPositions at_index;
        // cout << word.at(k - diag_index_found) << " ";
        at_index.character = word.at(k - diag_index_found);

        at_index.row = temp_row;
        temp_row++;
        // cout << at_index.row << " ";

        at_index.col = temp_col;
        temp_col++;
        // cout << at_index.col << endl;

        to_add_to_return.push_back(at_index);
      }
      word_location_to_return.char_positions = to_add_to_return;
      return word_location_to_return;
    }
  }
  return WordLocation{};
}

WordLocation WordSearchSolver::LeftDiag(const std::string& word) {
  for (size_t i = 0; i < puzzle_height_; i++) {
    for (size_t j = puzzle_width_ - 1; j > 0; j--) {
      string ldiag = "";

      size_t temp_row = i;
      size_t temp_col = j;

      while (LocationInBounds(temp_row, temp_col)) {
        ldiag = ldiag + puzzle_.at(temp_row).at(temp_col);
        temp_row++;
        temp_col--;
      }

      if (word.length() > ldiag.length()) {
        continue;
      }
      if (ldiag.find(word) == string::npos) {
        continue;
      }

      // for (size_t x = 0; x < puzzle_height_; x++) {
      //   for (size_t y = 0; y < puzzle_width_; y++) {
      //     cout << puzzle_.at(x).at(y) << " ";
      //   }
      //   cout << endl;
      // }

      size_t diag_index_found = ldiag.find(word);
      cout << diag_index_found << endl;

      WordLocation word_location_to_return;
      word_location_to_return.word = word;
      vector<CharPositions> to_add_to_return;

      temp_row = i + diag_index_found;
      temp_col = j - diag_index_found;

      for (size_t k = diag_index_found; k < diag_index_found + word.length();
           k++) {
        CharPositions at_index;
        cout << word.at(k - diag_index_found) << " ";
        at_index.character = word.at(k - diag_index_found);

        at_index.row = temp_row;
        temp_row++;
        cout << at_index.row << " ";

        at_index.col = temp_col;
        temp_col--;
        cout << at_index.col << endl;

        to_add_to_return.push_back(at_index);
      }
      word_location_to_return.char_positions = to_add_to_return;
      return word_location_to_return;
    }
  }
  return WordLocation{};
}