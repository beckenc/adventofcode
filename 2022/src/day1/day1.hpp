#pragma once
#include <istream>
#include <vector>

namespace aoc::day1 {

auto count_calories(std::istream &input) -> std::vector<unsigned>;
auto main_pt1([[maybe_unused]] int argc, [[maybe_unused]] char **argv) -> int;
auto main_pt2([[maybe_unused]] int argc, [[maybe_unused]] char **argv) -> int;
}  // namespace aoc::day1