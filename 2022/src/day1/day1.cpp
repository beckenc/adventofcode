#include "day1/day1.hpp"

#include <algorithm>
#include <iostream>
#include <numeric>
#include <sstream>

namespace aoc::day1 {

auto count_calories(std::istream &input) -> std::vector<unsigned> {
  auto result = std::vector<unsigned>{};

  unsigned calories;
  for (std::string line; std::getline(input, line);) {
    if (unsigned x; !line.empty()) {
      std::istringstream{line} >> x;
      calories += x;
    } else {
      result.emplace_back(calories);
      calories = 0;
    }
  }
  result.emplace_back(calories);
  return result;
}

static auto part1(auto calories) {
  std::ranges::sort(calories, std::ranges::greater());
  std::cout << "Part1:" << calories[0] << "\n";
}

static auto part2(auto calories) {
  std::ranges::sort(calories, std::ranges::greater());
  auto top_three_calories =
      std::accumulate(calories.begin(), calories.begin() + 3, 0);
  std::cout << "Part2:" << top_three_calories << "\n";
}

auto main_pt1([[maybe_unused]] int argc, [[maybe_unused]] char **argv) -> int {
  part1(count_calories(std::cin));
  return 0;
}

auto main_pt2([[maybe_unused]] int argc, [[maybe_unused]] char **argv) -> int {
  part2(count_calories(std::cin));
  return 0;
}
}  // namespace aoc::day1