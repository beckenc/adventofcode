#pragma once

#include <istream>

namespace aoc::day1 {

auto count_increasing(std::istream &input) -> unsigned;
auto main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) -> int;
}  // namespace aoc::day1