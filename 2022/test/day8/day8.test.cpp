#include "day8/day8.hpp"

#include <istream>
#include <ranges>
#include <sstream>
#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace aoc::day8 {

TEST(SimpleTestPt1, day8) {
  std::vector<std::pair<std::string, std::pair<std::pair<unsigned, unsigned>,
                                               std::pair<unsigned, unsigned>>>>
      input = {{"30373", {{7, 3}, {7, 3}}},
               {"25512", {{5, 1}, {5, 2}}},
               {"65332", {{6, 0}, {5, 1}}},
               {"33549", {{5, 2}, {9, 4}}},
               {"35390", {{9, 3}, {9, 3}}}};

  unsigned i = 0;
  auto grid = Grid{};

  for (auto [row, result] : input) {
    std::stringstream{row} >> grid;
  }

  EXPECT_EQ(grid.size(), 5);
  std::ranges::for_each(grid, [](auto&& row) { EXPECT_EQ(row.size(), 5); });

  EXPECT_EQ(grid.get_visibilities().size(), 21);
}

TEST(SimpleTestPt2, day8) {}

}  // namespace aoc::day8