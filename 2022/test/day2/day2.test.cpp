#include "day2/day2.hpp"

#include <sstream>
#include <vector>

#include "gtest/gtest.h"

namespace aoc::day2 {

TEST(SimpleTest, Day2) {
  std::vector<std::pair<std::string, Game::Score_t>> inputs = {
      {"A Y", 8}, {"B X", 1}, {"C Z", 6}, {"A Y\nB X\nC Z", 15}};

  for (const auto& [input, result] : inputs) {
    auto s = std::stringstream{input};
    auto game = Game{s};
    EXPECT_EQ(game.play(), result);
  }
}

TEST(RoundTest, Day2) {
  std::vector<std::pair<std::pair<char, char>, aoc::day2::Round1::Score_t>>
      inputs = {{{'A', 'A'}, 4}, {{'B', 'B'}, 5}, {{'C', 'C'}, 6},
                {{'A', 'B'}, 8}, {{'A', 'C'}, 3}, {{'B', 'A'}, 1},
                {{'B', 'C'}, 9}, {{'A', 'Z'}, 3}};

  for (const auto& [input, result] : inputs) {
    auto [opponent, me] = input;
    auto round = Round1{opponent, me};
    EXPECT_EQ(round.score(), result);
  };
}

}  // namespace aoc::day2