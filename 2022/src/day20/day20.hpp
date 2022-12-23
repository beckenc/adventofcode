#pragma once
#include <iostream>
#include <list>
#include <vector>

namespace aoc::day20 {

struct Number {
  int64_t value = 0;
  bool touched = false;
  auto operator==(const Number& rhs) const { return value == rhs.value; };
  auto operator<=>(const Number& rhs) const { return value <=> rhs.value; };
};

struct List : public std::vector<Number> {
  auto nextpos(auto current_pos, auto increment) const;
};

inline auto& operator>>(std::istream& is, Number& number) {
  is >> number.value;
  return is;
}

auto main_pt1(int argc, char** argv) -> int;
auto main_pt2(int argc, char** argv) -> int;
}  // namespace aoc::day20
