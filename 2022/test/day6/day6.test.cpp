#include "day6/day6.hpp"

#include <iostream>
#include <ranges>
#include <sstream>
#include <algorithm>
#include <string>
#include <ranges>
#include <optional>

#include "gtest/gtest.h"

namespace aoc::day6 {

TEST(SimpleTestPt1, day6) {
  std::vector<std::pair<std::string_view, unsigned>> test_vectors = {
      {"mjqjpqmgbljsphdztnvjfqwrcgsmlb", 7},
      {"bvwbjplbgvbhsrlpgdmjqwftvncz", 5},
      {"nppdvjthqldpwncqszvftbrmjlhg", 6},
      {"nznrnfrfntjfmvfwmzdfjlvtqnbhcprsg", 10},
      {"zcfzfwzzqfrljwzlrfnpqdbhtmscgvjw", 11}};

  std::for_each(test_vectors.begin(), test_vectors.end(), [](auto&& test_vector) {
    auto [input, result] = test_vector;
    EXPECT_EQ(search_pattern(input, 4), result);
  });
}

TEST(SimpleTestPt2, day6) {
  std::vector<std::pair<std::string_view, unsigned>> test_vectors = {
      {"mjqjpqmgbljsphdztnvjfqwrcgsmlb", 19},
      {"bvwbjplbgvbhsrlpgdmjqwftvncz", 23},
      {"nppdvjthqldpwncqszvftbrmjlhg", 23},
      {"nznrnfrfntjfmvfwmzdfjlvtqnbhcprsg", 29},
      {"zcfzfwzzqfrljwzlrfnpqdbhtmscgvjw", 26}};

  std::for_each(test_vectors.begin(), test_vectors.end(), [](auto&& test_vector) {
    auto [input, result] = test_vector;
    EXPECT_EQ(search_pattern(input, 14), result);
  });
}

}  // namespace aoc::day6