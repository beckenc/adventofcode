#pragma once
#include <vector>

namespace aoc::day20 {

typedef std::vector<int64_t> List;

struct RefList : public std::vector<List::const_iterator> {
  RefList(const List& list) : _list{list} {
    for (auto it = list.begin(); it != list.end(); ++it) {
      emplace_back(it);
    }
  }
  auto shuffle(auto n);
  auto sumUp(auto ref, auto positions) const;

 private:
  auto currentpos(auto number) const;
  auto nextpos(auto current_pos, auto increment) const;

  const List& _list;
};

auto main_pt1([[maybe_unused]] int argc, [[maybe_unused]] char **argv) -> int;
auto main_pt2([[maybe_unused]] int argc, [[maybe_unused]] char **argv) -> int;
}  // namespace aoc::day20
