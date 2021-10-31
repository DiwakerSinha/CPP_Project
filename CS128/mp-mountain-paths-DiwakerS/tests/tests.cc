//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//                MP : MOUNTAIN PATHS : Student Test Cases                  //
//                                                                          //
// Written By :                         Environment :                       //
// Date ......:                         Compiler ...:                       //
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//                             Framework Set-up                             //
//////////////////////////////////////////////////////////////////////////////
#ifndef CATCH_CONFIG_MAIN
#  define CATCH_CONFIG_MAIN
#endif
#include "catch.hpp"

//////////////////////////////////////////////////////////////////////////////
//                                 Includes                                 //
//////////////////////////////////////////////////////////////////////////////
#include "color.hpp"
#include "elevation_dataset.hpp"
#include "grayscale_image.hpp"
#include "path.hpp"
#include "path_image.hpp"

using std::vector;

//////////////////////////////////////////////////////////////////////////////
//                                Test Cases                                //
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////

TEST_CASE("ElevationDataset construtor", "[constructor]") {
  ElevationDataset dataset(
      "/home/vagrant/src/mp-mountain-paths-DiwakerS/data/data.txt", 5, 2);
  vector<int> row_1{10, 20, 30, 40, 35};
  vector<int> row_2{25, 20, 15, 18, 20};
  vector<vector<int>> solution;
  solution.push_back(row_1);
  solution.push_back(row_2);
  dataset.get_data().size();
  REQUIRE(dataset.get_data() == solution);
}

TEST_CASE("Find Max and Min Elevation", "[FindMaxAndMinEle]") {
  ElevationDataset dataset(
      "/home/vagrant/src/mp-mountain-paths-DiwakerS/data/data.txt", 5, 2);
  dataset.FindMaxAndMinElevation();
  REQUIRE(dataset.max_ele() == 40);
  REQUIRE(dataset.min_ele() == 10);
}
TEST_CASE("GrayScale image", "[grayscale images") {
  ElevationDataset dataset(
      "/home/vagrant/src/mp-mountain-paths-DiwakerS/data/data.txt", 5, 2);
  GrayscaleImage image(dataset);
  vector<vector<Color>> solution;
  vector<Color> row_1{Color(0, 0, 0),
                      Color(85, 85, 85),
                      Color(170, 170, 170),
                      Color(255, 255, 255),
                      Color(213, 213, 213)};
  vector<Color> row_2{Color(128, 128, 128),
                      Color(85, 85, 85),
                      Color(43, 43, 43),
                      Color(68, 68, 68),
                      Color(85, 85, 85)};
  solution.push_back(row_1);
  solution.push_back(row_2);
  REQUIRE(solution == image.get_image());
}

TEST_CASE("PathImageTest1",
          "[constructor") {  // testing with the same row and same column
  ElevationDataset dataset(
      "/home/vagrant/src/mp-mountain-paths-DiwakerS/data/same_data.txt", 5, 2);
  GrayscaleImage image(dataset);
  vector<vector<Color>> solution;
  PathImage paths_obj(image, dataset);
  paths_obj.path_mapping();
  vector<size_t> solution_1{0, 0, 0, 0, 0};
  vector<size_t> solution_2{1, 1, 1, 1, 1};
  vector<Path> paths = paths_obj.paths();
  REQUIRE(solution_1 == paths_obj.paths().at(0).path());
  REQUIRE(solution_2 == paths_obj.paths().at(1).path());
}
TEST_CASE("PathImage", "[constructor]") {
  ElevationDataset dataset(
      "/home/vagrant/src/mp-mountain-paths-DiwakerS/data/big_data2.txt", 5, 4);
  GrayscaleImage image(dataset);
  vector<vector<Color>> solution;
  PathImage paths_obj(image, dataset);
  vector<size_t> solution_1{0, 1, 1, 1, 1};
  vector<size_t> solution_2{1, 1, 1, 1, 1};
  vector<Path> paths = paths_obj.paths();
  std::cout << paths_obj.paths().size() << std::endl;
  for (size_t i = 0; i < paths.size(); ++i) {
    REQUIRE(paths.at(0).path() == solution_1);
  }
  // REQUIRE(solution == paths.paths().path());
}

TEST_CASE("PathImage2", "[constructor]") {
  ElevationDataset dataset(
      "/home/vagrant/src/mp-mountain-paths-DiwakerS/data/big_data2.txt", 5, 3);
  GrayscaleImage image(dataset);
  vector<vector<Color>> solution;
  PathImage paths_obj(image, dataset);
  vector<size_t> solution_1{0, 1, 1, 1, 1};
  vector<size_t> solution_2{1, 1, 1, 1, 1};
  vector<Path> paths = paths_obj.paths();
  std::cout << paths_obj.paths().size() << std::endl;
  REQUIRE(paths.at(0).path() == solution_1);
  REQUIRE(solution_2 == paths.at(1).path());
}
// testing square data
TEST_CASE("PathImage3", "[constructor]") {
  ElevationDataset dataset(
      "/home/vagrant/src/mp-mountain-paths-DiwakerS/data/square_data.txt",
      3,
      3);
  GrayscaleImage image(dataset);
  vector<vector<Color>> solution;
  PathImage paths_obj(image, dataset);
  vector<size_t> solution_1{0, 1, 1, 1, 1};
  vector<size_t> solution_2{1, 1, 1, 1, 1};
  // vector<Path> paths = paths_obj.paths();
  // std::cout << paths_obj.paths().size() << std::endl;
  // REQUIRE(paths.at(0).path() == solution_1);
  // REQUIRE(solution_2 == paths.at(1).path());
}

TEST_CASE("CreatePathImage") {
  ElevationDataset dataset(
      "/home/vagrant/src/mp-mountain-paths-DiwakerS/data/data.txt", 5, 2);
  GrayscaleImage image(dataset);
  PathImage paths_obj(image, dataset);
  vector<vector<Color>> colored_image = paths_obj.path_image();
  std::cout << colored_image.at(0).at(0).red();
  REQUIRE(colored_image.at(0).at(0) == Color(252, 25, 63));
  REQUIRE(colored_image.at(0).at(1) == Color(252, 25, 63));
  REQUIRE(colored_image.at(1).at(2) == Color(31, 253, 13));
  REQUIRE(colored_image.at(1).at(3) == Color(31, 253, 13));
  REQUIRE(colored_image.at(1).at(4) == Color(31, 253, 13));
}
