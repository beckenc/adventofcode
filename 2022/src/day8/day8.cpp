#include "day8/day8.hpp"

#include <iostream>

namespace aoc::day8 {

auto main_pt1(int argc, char **argv) -> int {
  auto grid = std::ranges::istream_view<Grid>(std::cin);
  std::cout << "Part1:" << (*grid.begin()).get_visibilities().size() << std::endl;
  return 0;
}

auto main_pt2(int argc, char **argv) -> int { return 0; }
}  // namespace aoc::day8
