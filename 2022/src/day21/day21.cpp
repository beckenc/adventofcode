#include "day21/day21.hpp"

#include <algorithm>
#include <cmath>
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

auto main_pt2(int argc, char **argv) -> int {
  auto monkeys = Monkeys{};
  std::ranges::for_each(std::ranges::istream_view<Monkey>(std::cin),
                        [&monkeys](auto &&monkey) {  //
                          monkeys[monkey.name()] = monkey;
                        });

  monkeys["root"].fix_arithmetic(std::minus());
  auto root_monkey = monkeys["root"];
  auto &humn_monkey = monkeys["humn"];

  //
  // Binary Search by HAND :-D
  // Modify, Compile and Repeat until sign changes
  //

  humn_monkey.fix_arithmetic(3876027195100);
  auto v1 = root_monkey(monkeys);
  humn_monkey.fix_arithmetic(3876030000000);
  auto v2 = root_monkey(monkeys);

  auto sign =
      (std::signbit(v1) != std::signbit(v2)) ? "different sign" : "same sign";
  std::cout << sign << std::endl;

  for (int64_t i = 3876027195100; i < 3876030000000; ++i) {
    humn_monkey.fix_arithmetic(i);
    if (0 == root_monkey(monkeys)) {
      std::cout << "Part2: " << i << std::endl;
      break;
    }
  }

  return 0;
}
}  // namespace aoc::day21
