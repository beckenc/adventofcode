#include "day20/day20.hpp"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <ranges>
#include <set>

namespace aoc::day20 {

auto RefList::currentpos(auto li) const {
  auto numpos = std::ranges::find(*this, li);
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

auto RefList::shuffle(auto n) {
  for (auto i : std::views::iota(0) | std::views::take(n)) {
    for (auto li = _list.begin(); li != _list.end(); ++li) {
      auto current = currentpos(li);
      auto [next, pos] = nextpos(current, *li);
      erase(std::begin(*this) + current);
      insert(next, li);
    }
  }
  return *this;
}

auto RefList::sumUp(auto ref, auto positions) const {
  auto it = std::ranges::find(_list, ref);
  auto refit = std::ranges::find(*this, it);
  auto refpos = std::distance(std::begin(*this), refit);

  auto sum = int64_t{0};
  for (auto pos : positions) {
    auto npos = (pos + refpos) % std::ssize(*this);
    auto it = std::begin(*this);
    std::advance(it, npos);
    sum += **it;
  }
  return sum;
}

auto main_pt1(int argc, char **argv) -> int {  //
  auto list = List{};
  std::ranges::for_each(
      std::ranges::istream_view<List::value_type>(std::cin),
      [&list, pos = 0](auto &&number) mutable {
        list.emplace_back(std::forward<decltype(number)>(number));
      });

  auto sum = RefList{list}.shuffle(1).sumUp(
      0, std::initializer_list{1000, 2000, 3000});

  std::cout << "Part1:" << sum << std::endl;

  return 0;
}

auto main_pt2(int argc, char **argv) -> int {  //
  auto list = List{};
  std::ranges::for_each(
      std::ranges::istream_view<List::value_type>(std::cin),
      [&list, pos = 0](auto &&number) mutable {
        number *= 811589153;
        list.emplace_back(std::forward<decltype(number)>(number));
      });

  auto sum = RefList{list}.shuffle(10).sumUp(
      0, std::initializer_list{1000, 2000, 3000});

  std::cout << "Part2:" << sum << std::endl;

  return 0;
}
}  // namespace aoc::day20
