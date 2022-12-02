#include "day2/day2.hpp"


#include <exception>
#include <iostream>
#include <numeric>
#include <ranges>
#include <sstream>

namespace aoc::day2 {

auto main_pt1(int argc, char **argv) -> int {
  std::cout << "Part1:" << Game<Round1>{std::cin}.play() << "\n";
  return 0;
}
auto main_pt2(int argc, char **argv) -> int {
  std::cout << "Part2:" << Game<Round2>{std::cin}.play() << "\n";
  return 0;
}
}  // namespace aoc::day2