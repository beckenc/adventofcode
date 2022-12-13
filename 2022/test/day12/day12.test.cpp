#include "day12/day12.hpp"

#include <algorithm>
#include <ranges>
#include <string_view>
#include <vector>

#include "gtest/gtest.h"

namespace aoc::day12 {

TEST(SimpleTestPt1, day12) {
  auto input = std::vector<std::string>{"Sabqponm",  //
                                        "abcryxxl",  //
                                        "accszExk",  //
                                        "acctuvwj",  //
                                        "abdefghi"};

  auto heightmap = Heightmap{};
  std::ranges::for_each(input, [&heightmap](auto&& line) {
    heightmap.create(std::istringstream{line});
  });

  // heightmap.search();
}

TEST(SimpleTestPt2, day12) {}

}  // namespace aoc::day12