#include "day20/day20.hpp"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <ranges>

namespace aoc::day20 {

auto main_pt1(int argc, char **argv) -> int {  //
  auto list = List{};
  std::ranges::for_each(
      std::ranges::istream_view<Number>(std::cin), [&list](auto &&number) {
        list.emplace_back(std::forward<decltype(number)>(number));
      });

  auto begin = [&list](auto li) {
    for (; li != std::ranges::end(list) && li->touched; std::advance(li, 1))
      ;
    return li;
  };

  auto nextpos = [max = std::ssize(list)](auto current_pos, auto value) {
    auto dist = value % (max - 1);
    if (std::signbit(dist)) {
      dist += (max - 1);
    }
    return (current_pos + dist) % (max - 1);
  };

  for (auto li = begin(std::ranges::begin(list)); li != std::ranges::end(list);
       li = begin(li)) {
    auto value = li->value;
    auto nxtpos = nextpos(std::distance(list.begin(), li), value);
    list.erase(li);
    list.insert(std::ranges::begin(list) + nxtpos, {value, true});
  }

  auto pos0 = std::distance(list.begin(), std::ranges::find(list, Number{}));

  auto sum = int64_t{0};
  for (auto pos : std::vector<int>{1000, 2000, 3000}) {
    auto npos = (pos + pos0) % std::ssize(list);
    auto number = list[npos];
    sum += number.value;
  }

  std::cout << "Part1:" << sum << std::endl;

  return 0;
}

auto main_pt2(int argc, char **argv) -> int {  //
  return 0;
}
}  // namespace aoc::day20
