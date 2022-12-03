#include "day3/day3.hpp"

#include <iostream>
#include <sstream>
#include <vector>

#include "gtest/gtest.h"

namespace aoc::day3 {

TEST(SimpleTest, Day3) {
  std::vector<std::pair<std::string, std::pair<char, unsigned>>> inputs = {
      {"vJrwpWtwJgWrhcsFMMfFFhFp", {'p', 16}},
      {"BjqHRNqRjqzjGDLGLrsFMfFZSrLrFZsSL", {'L', 38}},
      {"PmmdzqPrVvPwwTWBwg", {'P', 42}},
      {"wMqvLMZHhHMvwLHjbvcjnnSBnvTQFn", {'v', 22}},
      {"ttgJtRGJQctTZtZT", {'t', 20}},
      {"CrZsJsPPZsGzwwsLwLmpwMDw", {'s', 19}}};

  for (auto const& [supplies, result] : inputs) {
    auto [shared, priority] = result;

    auto s = std::stringstream{} << supplies;
    Rucksack rs;
    s >> rs;
    auto [share, prio] = rs.get_shared_item();
    EXPECT_EQ(share, shared);
    EXPECT_EQ(prio, priority);
  }
}

}  // namespace aoc::day3