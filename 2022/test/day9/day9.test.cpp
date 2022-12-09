#include "day9/day9.hpp"

#include <iostream>
#include <sstream>
#include <vector>

#include "gtest/gtest.h"

namespace aoc::day9 {

TEST(SimpleTestPt1, day9) {
  auto input = std::vector<std::string>{"R 4", "U 4", "L 3", "D 1",
                                        "R 4", "D 1", "L 5", "R 2"};

  auto motions = Motions{};
  for (auto in : input) {
    auto motion = Motion{};
    std::stringstream{in} >> motion;
    motions.append(std::move(motion));
  }

  std::cout << motions << std::endl;
}

TEST(SimpleTestPt2, day9) {}

}  // namespace aoc::day9