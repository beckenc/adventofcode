#include "day14/day14.hpp"

#include <algorithm>
#include <iostream>
#include <ranges>
#include <vector>

#include "gtest/gtest.h"

namespace aoc::day14 {

TEST(SimpleTestPt1, day14) {
  auto input = std::vector<std::string>{"498,4 -> 498,6 -> 496,6",
                                        "503,4 -> 502,4 -> 502,9 -> 494,9"};

  auto cave = Cave{};
  std::ranges::for_each(input, [&cave](auto&& line) {  //
    auto rock = rock_t{};
    std::istringstream{line} >> rock;
    cave.add(std::move(rock));
  });

  for(int i = 0; i <= 100; ++i)
  cave.drop_sand({{500,0}});
  std::cout << cave << std::endl;
}

TEST(SimpleTestPt2, day14) {}

}  // namespace aoc::day14