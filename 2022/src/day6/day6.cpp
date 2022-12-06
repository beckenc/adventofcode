#include "day6/day6.hpp"

#include <algorithm>
#include <iostream>
#include <ranges>
#include <sstream>

namespace aoc::day6 {

auto search_pattern(const std::string_view input, unsigned pattern_len)
    -> std::optional<unsigned> {
  for (auto i = 0; i < input.length(); ++i)
    if (auto seq = input.substr(i, pattern_len); std::ranges::all_of(
            seq, [&seq](auto &&c) { return std::ranges::count(seq, c) == 1; }))
      return i + pattern_len;
  return {};
};

auto main_pt1(int argc, char **argv) -> int {
  auto ss = std::stringstream{} << std::cin.rdbuf();
  auto result = search_pattern(ss.str(), 4);
  std::cout << "Part1:" << result.value_or(-1) << std::endl;
  return 0;
}

auto main_pt2(int argc, char **argv) -> int {
  auto ss = std::stringstream{} << std::cin.rdbuf();
  auto result = search_pattern(ss.str(), 14);
  std::cout << "Part2:" << result.value_or(-1) << std::endl;
  return 0;
}
}  // namespace aoc::day6
