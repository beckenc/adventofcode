#pragma once
#include <iostream>
#include <list>
#include <vector>

namespace aoc::day20 {

struct Number {
  int64_t value = 0;
  int uuid = 0;
};

typedef std::vector<Number> List;

struct RefList : public std::vector<List::const_iterator> {
  RefList(const List& list) : _list{list} {
    for (auto it = list.begin(); it != list.end(); ++it) {
      emplace_back(it);
    }
  }
  auto currentpos(auto number) const;
  auto nextpos(auto current_pos, auto increment) const;
  auto shuffle(auto n);
  auto sumUp(auto ref, auto positions) const;

 private:
  const List& _list;
};

inline auto& operator>>(std::istream& is, Number& number) {
  static int uuid = 0;
  is >> number.value;
  number.uuid = uuid++;
  return is;
}

auto main_pt1(int argc, char** argv) -> int;
auto main_pt2(int argc, char** argv) -> int;
}  // namespace aoc::day20
