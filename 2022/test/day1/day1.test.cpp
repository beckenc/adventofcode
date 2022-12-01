#include "day1/day1.hpp"

#include <sstream>
#include <vector>

#include "gtest/gtest.h"

TEST(TrivialTest, Day1) {
  std::pair<std::string, unsigned> input = {
      "1000\n2000\n3000\n\n4000\n\n5000\n6000\n\n7000\n8000\n9000\n\n10000",
      24000};

  std::stringstream s(input.first);
  auto calories = aoc::day1::count_calories(s);
  auto max_calories = std::max_element(calories.begin(), calories.end());
  EXPECT_EQ(*max_calories, input.second);
}
