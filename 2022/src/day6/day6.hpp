#pragma once

#include <optional>
#include <string_view>

namespace aoc::day6 {

auto search_pattern(const std::string_view input, unsigned pattern_len) -> std::optional<unsigned>;

auto main_pt1(int argc, char** argv) -> int;
auto main_pt2(int argc, char** argv) -> int;
}  // namespace aoc::day6
