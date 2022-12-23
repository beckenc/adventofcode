#include "day20/day20.hpp"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <ranges>

namespace aoc::day20 {


auto List::nextpos(auto current_pos, auto increment) const {
  auto max = std::ssize(*this);
  auto dist = increment % (max - 1);
  if (std::signbit(dist)) {
    dist += (max - 1);
  }
  auto pos = (current_pos + dist) % (max - 1);
  auto it = std::begin(*this);
  std::advance(it, pos);
  return it;
};

auto main_pt1(int argc, char **argv) -> int {  //
  auto list = List{};
  std::ranges::for_each(
      std::ranges::istream_view<Number>(std::cin), [&list](auto &&number) {
        list.emplace_back(std::forward<decltype(number)>(number));
      });

  auto begin = [&list](auto li) {
    for (; li != std::end(list) && li->touched; std::advance(li, 1))
      ;
    return li;
  };

  for (auto li = begin(std::begin(list)); li != std::end(list);
       li = begin(li)) {
    auto value = li->value;
    auto nxtpos = list.nextpos(std::distance(std::begin(list), li), value);
    list.erase(li);
    list.insert(nxtpos, {value, true});
  }

  auto pos0 = std::distance(std::begin(list), std::ranges::find(list, Number{}));

  auto sum = int64_t{0};
  for (auto pos : std::vector<int>{1000, 2000, 3000}) {
    auto npos = (pos + pos0) % std::ssize(list);
    auto it = std::begin(list);
    std::advance(it, npos);
    sum += it->value;
  }

  std::cout << "Part1:" << sum << std::endl;

  return 0;
}

auto main_pt2(int argc, char **argv) -> int {  //
  return 0;
}
}  // namespace aoc::day20
