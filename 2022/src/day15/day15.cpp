#include "day15/day15.hpp"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <map>
#include <ranges>
#include <regex>

namespace aoc::day15 {

auto operator>>(std::istream& is, Sensor& sensor) -> std::istream& {  //
  // e.g. Sensor at x=2, y=18: closest beacon is at x=-2, y=15
  static auto rgx = std::regex{
      "[=, A-Za-z]+(-?\\d+)[=, A-Za-z]+(-?\\d+)[:= A-Za-z]+(-?\\d+)[=, "
      "A-Za-z]+(-?\\d+)"};

  auto line = std::string{};
  std::getline(is, line);

  if (!line.empty()) {
    auto smatch = std::smatch{};
    std::regex_search(line, smatch, rgx);
    assert(smatch.size() == 5);

    sensor = Sensor{{{stoi(smatch[1]), stoi(smatch[2])}},
                    {{{stoi(smatch[3]), stoi(smatch[4])}}}};
  }
  return is;
}

auto Grid::count_no_beacon_positions(auto y) const -> unsigned {
  int result = 0;
  std::ranges::for_each(
      std::ranges::iota_view(-6000000, 6000000), [this, &result, &y](auto i) {
        auto point = utils::Coordinates{{i, y}};

        auto is_covered_by_sensor = [&point](auto&& arg) {
          using T = std::decay_t<decltype(arg)>;
          if constexpr (std::is_same_v<T, Sensor>) {
            return arg.dist(point) <= arg.dist();
          }
          return false;
        };

        if (!std::ranges::none_of(range(), [&is_covered_by_sensor](auto&& var) {
              return std::visit(is_covered_by_sensor, var.second);
            })) {
          if (!elem(point)) {
            result++;
          }
        }
      });
  return result;
}

auto main_pt1(int argc, char** argv) -> int {  //
  auto grid = Grid{};
  std::ranges::for_each(std::ranges::istream_view<Sensor>(std::cin),
                        [&grid](auto&& sensor) {  //
                          grid.emplace(std::forward<Sensor>(sensor));
                          grid.emplace(std::forward<Beacon>(sensor.beacon()));
                        });
  std::cout << "Part1:" << grid.count_no_beacon_positions(2000000) << std::endl;
  return 0;
}

auto main_pt2(int argc, char** argv) -> int {  //
  std::cout << "Part2:" << std::endl;
  return 0;
}
}  // namespace aoc::day15
