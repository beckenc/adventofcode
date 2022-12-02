#pragma once
#include <istream>
#include <vector>

namespace aoc::day1 {

auto count_calories(std::istream &input) -> std::vector<unsigned>;
auto main_pt1(int argc, char **argv) -> int;
auto main_pt2(int argc, char **argv) -> int;
}  // namespace aoc::day1