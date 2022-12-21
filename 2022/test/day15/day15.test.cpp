#include "day15/day15.hpp"

#include <algorithm>
#include <map>
#include <ranges>
#include <variant>

#include "gtest/gtest.h"
#include "utils/utils.hpp"

namespace aoc::day15 {

TEST(SimpleTestPt1, day15) {
  auto input = std::vector<std::string>{
      "Sensor at x=2, y=18: closest beacon is at x=-2, y=15",
      "Sensor at x=9, y=16: closest beacon is at x=10, y=16",
      "Sensor at x=13, y=2: closest beacon is at x=15, y=3",
      "Sensor at x=12, y=14: closest beacon is at x=10, y=16",
      "Sensor at x=10, y=20: closest beacon is at x=10, y=16",
      "Sensor at x=14, y=17: closest beacon is at x=10, y=16",
      "Sensor at x=8, y=7: closest beacon is at x=2, y=10",
      "Sensor at x=2, y=0: closest beacon is at x=2, y=10",
      "Sensor at x=0, y=11: closest beacon is at x=2, y=10",
      "Sensor at x=20, y=14: closest beacon is at x=25, y=17",
      "Sensor at x=17, y=20: closest beacon is at x=21, y=22",
      "Sensor at x=16, y=7: closest beacon is at x=15, y=3",
      "Sensor at x=14, y=3: closest beacon is at x=15, y=3",
      "Sensor at x=20, y=1: closest beacon is at x=15, y=3"};

  auto elements = Grid{};
  std::ranges::for_each(input, [&elements](auto&& line) {  //
    auto sensor = Sensor{};
    std::istringstream{line} >> sensor;
    elements.emplace(sensor);
    elements.emplace(sensor.beacon());
  });

// 9 ...#########################...
// 10 ..####B######################..
// 11 .###S#############.###########.
// 35, 25, 30

  EXPECT_EQ(25, elements.count_no_beacon_positions(int64_t{9}));
  EXPECT_EQ(26, elements.count_no_beacon_positions(int64_t{10}));
  EXPECT_EQ(28, elements.count_no_beacon_positions(int64_t{11})); 
}

TEST(SimpleTestPt2, day15) {}

}  // namespace aoc::day15