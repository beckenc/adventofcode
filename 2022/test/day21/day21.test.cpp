#include "day21/day21.hpp"

#include <algorithm>
#include <ranges>
#include <string>

#include "gtest/gtest.h"

namespace aoc::day21 {

TEST(SimpleTestPt1, day21) {
  auto input = std::vector<std::string>{
      "root: pppw + sjmn",  //
      "dbpl: 5",            //
      "cczh: sllz + lgvd",  //
      "zczc: 2",            //
      "ptdq: humn - dvpt",  //
      "dvpt: 3",            //
      "lfqf: 4",            //
      "humn: 5",            //
      "ljgn: 2",            //
      "sjmn: drzm * dbpl",  //
      "sllz: 4",            //
      "pppw: cczh / lfqf",  //
      "lgvd: ljgn * ptdq",  //
      "drzm: hmdt - zczc",  //
      "hmdt: 32"            //
  };

  auto monkeys = Monkeys{};
  std::ranges::for_each(input, [&monkeys](auto&& line) {  //
    auto monkey = Monkey{};
    std::istringstream{line} >> monkey;
    monkeys[monkey.name()] = monkey;
  });

  auto root_monkey = monkeys["root"];
  EXPECT_EQ(152, root_monkey(monkeys));
}

TEST(SimpleTestPt2, day21) {}

}  // namespace aoc::day21