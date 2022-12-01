#include "day1/day1.hpp"
#include "gtest/gtest.h"
#include <sstream>
#include <vector>

TEST(TrivialTest, Day1) {
  std::vector<std::pair<std::string, uint32_t>> inputs = {
      {"", 0},                 // empty input 0 increasing
      {"0", 0},                // single element 0 increasing
      {"0 1", 1},              // two elements, with increase
      {"0 1 0 1 0 1 0 1", 4},  // alternating, 4 repetitions
      {"0 0 0 0 0 0", 0},      // monotonic, no increase
      {"0 1 2 3", 3},          // increasing sequence - 3 increases
      {"3 2 1 0", 0},          // decreasing sequence - 0 increases
      {"199 200 208 120 200 207 240 269 260 263", 7}
  };

  for (auto &[input, count] : inputs) {
    std::stringstream s(input);
    EXPECT_EQ(aoc::day1::count_increasing(s), count) << " on input " << input;
  }
}
