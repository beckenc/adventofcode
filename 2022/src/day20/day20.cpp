#include "day20/day20.hpp"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <ranges>
#include <set>

namespace aoc::day20 {

auto RefList::currentpos(auto number) const {
  auto numpos = std::ranges::find_if(*this, [&number](auto &&it) {  //
    return it->id == number.id;
  });
  assert(numpos != std::end(*this));
  return std::distance(std::begin(*this), numpos);
};

auto RefList::nextpos(auto current, auto increment) const {
  auto max = std::ssize(*this) - 1;
  if (std::signbit(increment)) {
    increment += ((std::abs(increment) / max) + 1) * max;
  }
  auto next = (current + increment) % max;
  auto it = std::begin(*this);
  return std::make_pair(it + next, next);
};

auto RefList::shuffle() {
  for (auto li = _list.begin(); li != _list.end(); ++li) {
    auto current = currentpos(*li);
    auto [next, pos] = nextpos(current, li->value);
    erase(std::begin(*this) + current);
    insert(next, li);
  }
}

auto main_pt1(int argc, char **argv) -> int {  //
  auto list = List{};
  std::ranges::for_each(
      std::ranges::istream_view<List::value_type>(std::cin),
      [&list, pos = 0](auto &&number) mutable {
        list.emplace_back(std::forward<decltype(number)>(number));
      });

  auto shuffled = RefList{list};
  shuffled.shuffle();

  auto pos0 = std::distance(
      std::begin(shuffled),
      std::ranges::find_if(shuffled, [](auto &&n) { return n->value == 0; }));

  auto sum = int64_t{0};
  for (auto pos : std::vector<int>{1000, 2000, 3000}) {
    auto npos = (pos + pos0) % std::ssize(shuffled);
    auto it = std::begin(shuffled);
    std::advance(it, npos);
    sum += (*it)->value;
  }

  std::cout << "Part1:" << sum << std::endl;

  return 0;
}

auto main_pt2(int argc, char **argv) -> int {  //
  auto list = List{};
  std::ranges::for_each(
      std::ranges::istream_view<List::value_type>(std::cin),
      [&list, pos = 0](auto &&number) mutable {
        number.value *= 811589153;
        list.emplace_back(std::forward<decltype(number)>(number));
      });

  auto shuffled = RefList{list};
  for (auto i : std::views::iota(0) | std::views::take(10)) {
    shuffled.shuffle();
  }

  auto pos0 = std::distance(
      std::begin(shuffled),
      std::ranges::find_if(shuffled, [](auto &&n) { return n->value == 0; }));

  auto sum = int64_t{0};
  for (auto pos : std::vector<int>{1000, 2000, 3000}) {
    auto npos = (pos + pos0) % std::ssize(shuffled);
    auto it = std::begin(shuffled);
    std::advance(it, npos);
    sum += (*it)->value;
  }

  std::cout << "Part2:" << sum << std::endl;

  return 0;
}
}  // namespace aoc::day20
