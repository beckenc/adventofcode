#include "day21/day21.hpp"

#include <algorithm>
#include <iostream>
#include <ranges>

namespace aoc::day21 {

auto main_pt1(int argc, char **argv) -> int {
  auto monkeys = Monkeys{};
  std::ranges::for_each(std::ranges::istream_view<Monkey>(std::cin),
                        [&monkeys](auto &&monkey) {  //
                          monkeys[monkey.name()] = monkey;
                        });
  auto root_monkey = monkeys["root"];
  std::cout << "Part1:" << root_monkey(monkeys) << std::endl;

  return 0;
}

auto main_pt2(int argc, char **argv) -> int { return 0; }
}  // namespace aoc::day21
