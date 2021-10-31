#include "functions.hpp"

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// functions() {

//}

std::string main(std::string str) {
  std::stringstream input(str);
  std::string tmp = "";
  std::vector<std::string> indi_word;

  while (input >> tmp) {
    indi_word.push_back(tmp);
  }  // Successfully transferring every word to the vector as individual string
     // elements

  std::string output = "";

  for (std::string val : indi_word) {
    tmp = "";
    while (val.compare("") != 0) {
      std::string temp = "";

      for (unsigned long i = 0; i < val.length();
           i++) {  // homogenous lowercase
        char letter = val.at(i);
        if (letter >= 'A' && letter <= 'Z') {
          letter = letter - ('Z' - 'z');
        }
        temp = temp + letter;
      }
      val = temp;

      for (unsigned long i = 1; i < val.length(); i++) {
        if (val.at(i) == 'w') {
          if (val.at(i - 1) == 'i' || val.at(i - 1) == 'e') {
            try {
              val = val.substr(0, i) + "v" + val.substr(i + 1, val.length());
            } catch (exception e) {
              val = val.substr(0, i) + "v";
            }
          }
        }
      }

      if (val.length() == 2) {
        // Vowel group check
        if (val.substr(0, 2).compare("ai") == 0) {
          tmp = tmp + "eye-";
          val = "";
          continue;
        } else if (val.substr(0, 2).compare("ae") == 0) {
          tmp = tmp + "eye-";
          val = "";
          continue;
        } else if (val.substr(0, 2).compare("ao") == 0) {
          tmp = tmp + "ow-";
          val = "";
          continue;
        } else if (val.substr(0, 2).compare("au") == 0) {
          tmp = tmp + "ow-";
          val = "";
          continue;
        } else if (val.substr(0, 2).compare("ei") == 0) {
          tmp = tmp + "ay-";
          val = "";
          continue;
        } else if (val.substr(0, 2).compare("eu") == 0) {
          tmp = tmp + "eh-oo-";
          val = "";
          continue;
        } else if (val.substr(0, 2).compare("iu") == 0) {
          tmp = tmp + "ew-";
          val = "";
          continue;
        } else if (val.substr(0, 2).compare("oi") == 0) {
          tmp = tmp + "oy-";
          val = "";
          continue;
        } else if (val.substr(0, 2).compare("ou") == 0) {
          tmp = tmp + "ow-";
          val = "";
          continue;
        } else if (val.substr(0, 2).compare("ui") == 0) {
          tmp = tmp + "ooey-";
          val = "";
          continue;
        }
      } else if (val.length() >= 3) {  // Vowel group check
        if (val.substr(0, 2).compare("ai") == 0) {
          tmp = tmp + "eye-";
          val = val.substr(2);
          continue;
        } else if (val.substr(0, 2).compare("ae") == 0) {
          tmp = tmp + "eye-";
          val = val.substr(2);
          continue;
        } else if (val.substr(0, 2).compare("ao") == 0) {
          tmp = tmp + "ow-";
          val = val.substr(2);
          continue;
        } else if (val.substr(0, 2).compare("au") == 0) {
          tmp = tmp + "ow-";
          val = val.substr(2);
          continue;
        } else if (val.substr(0, 2).compare("ei") == 0) {
          tmp = tmp + "ay-";
          val = val.substr(2);
          continue;
        } else if (val.substr(0, 2).compare("eu") == 0) {
          tmp = tmp + "eh-oo-";
          val = val.substr(2);
          continue;
        } else if (val.substr(0, 2).compare("iu") == 0) {
          tmp = tmp + "ew-";
          val = val.substr(2);
          continue;
        } else if (val.substr(0, 2).compare("oi") == 0) {
          tmp = tmp + "oy-";
          val = val.substr(2);
          continue;
        } else if (val.substr(0, 2).compare("ou") == 0) {
          tmp = tmp + "ow-";
          val = val.substr(2);
          continue;
        } else if (val.substr(0, 2).compare("ui") == 0) {
          tmp = tmp + "ooey-";
          val = val.substr(2);
          continue;
        }
      }

      if (val.at(0) == 'a') {  // indidual vowels
        tmp = tmp + "ah-";
        if (val.length() >= 2) {
          val = val.substr(1);
          continue;
        } else {
          val = "";
        }
      } else if (val.at(0) == 'e') {
        tmp = tmp + "eh-";
        if (val.length() >= 2) {
          val = val.substr(1);
          continue;
        } else {
          val = "";
        }
      } else if (val.at(0) == 'i') {
        tmp = tmp + "ee-";
        if (val.length() >= 2) {
          val = val.substr(1);
          continue;
        } else {
          val = "";
        }
      } else if (val.at(0) == 'o') {
        tmp = tmp + "oh-";
        if (val.length() >= 2) {
          val = val.substr(1);
          continue;
        } else {
          val = "";
        }
      } else if (val.at(0) == 'u') {
        tmp = tmp + "oo-";
        if (val.length() >= 2) {
          val = val.substr(1);
          continue;
        } else {
          val = "";
        }
      }

      if (val.at(0) == 'p' || val.at(0) == 'k' || val.at(0) == 'h' ||
          val.at(0) == 'l' || val.at(0) == 'm' ||
          val.at(0) == 'n') {  // Consonants that don't change
        tmp = tmp + val.at(0);
        if (val.length() >= 2) {
          val = val.substr(1);
          continue;
        } else {
          val = "";
        }
      }

      if (val.at(0) == 'w' || val.at(0) == 'v') {  // 'w'

        tmp = tmp + val.at(0);
        if (val.length() >= 2) {
          val = val.substr(1);
          continue;
        } else {
          val = "";
        }
      }
      if (val.at(0) == '\'') {
        tmp = tmp + val.at(0);
        if (val.length() >= 2) {
          val = val.substr(1);
          continue;
        } else {
          val = "";
        }
      } else {
        return (str +
                " contains a character not a part of the Hawaiian language.");
      }
    }
    if (tmp.at(tmp.length() - 1) == '-') {
      tmp = tmp.substr(0, tmp.length());
    }
    output = output + " " + tmp;
  }
  if (output.at(0) == ' ') {
    output = output.substr(1);
  }
  return output;
}