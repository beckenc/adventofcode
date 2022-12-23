#pragma once
#include <iostream>
#include <list>
#include <vector>

namespace aoc::day20 {

struct Number {
  int64_t value = 0;
  int id = 0;
  auto operator==(const Number& rhs) const { return id == rhs.id; };
  auto operator<=>(const Number& rhs) const { return id <=> rhs.id; };
};

struct List : public std::vector<Number> {  //
};

struct RefList : public std::vector<List::const_iterator> {
  RefList(const List& list) : _list{list} {
    for (auto it = list.begin(); it != list.end(); ++it) {
      emplace_back(it);
    }
  }
  auto currentpos(auto number) const;
  auto nextpos(auto current_pos, auto increment) const;
  auto shuffle();

 private:
  const List& _list;
};

inline auto& operator>>(std::istream& is, Number& number) {
  static int id = 0;
  is >> number.value;
  number.id = id++;
  return is;
}

auto main_pt1(int argc, char** argv) -> int;
auto main_pt2(int argc, char** argv) -> int;
}  // namespace aoc::day20
