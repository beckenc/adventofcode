#include "day11/day11.hpp"

#include <tuple>
#include <vector>
#include <ranges>
#include <algorithm>

#include "gtest/gtest.h"

namespace aoc::day11 {

TEST(SimpleTestPt1, day11) {
  auto participants =
      MonkeyGame::Participants_t{
        {0, {79, 98}, Operation::mul, 19, Monkey::test_t{23, 2, 3}},
        {1, {54, 65, 75, 74}, Operation::add, 6, Monkey::test_t{19, 2, 0}},
        {2, {79, 60, 97}, Operation::mul, std::nullopt, Monkey::test_t{13, 1, 3}},
        {3, {74}, Operation::add, 3, Monkey::test_t{17, 0, 1}}
      };
  MonkeyGame{participants}.play_game1(20).print_result(std::cout);
  std::cout << std::endl;
  MonkeyGame{participants}.play_game2(10000).print_result(std::cout);  
}

TEST(SimpleTestPt2, day11) {}

}  // namespace aoc::day11