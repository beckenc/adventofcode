#include "day15/day15.hpp"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <map>
#include <optional>
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

auto Grid::get_line_coverage(const Sensor& sensor, int64_t line) const
    -> coverage_t {
  auto coverage = coverage_t{};

  auto is_beacon = [&line, this](auto x) {
    if (auto e = elem({{x, line}}); std::holds_alternative<Beacon>(*e)) {
      return true;
    }
    return false;
  };

  auto [xs, ys] = sensor.position().xy();
  auto mdist = sensor.dist();
  if ((ys >= line && (ys - mdist) <= line) ||
      (ys <= line && (ys + mdist) >= line)) {
    auto xdiff = std::abs(mdist - std::abs(ys - line));
    auto xmin = xs - xdiff;
    auto xmax = xs + xdiff;
    if (is_beacon(xmin)) {
      xmin++;
    }
    if (is_beacon(xmax)) {
      xmax--;
    }
    if (xmin < xmax) {
      coverage = std::make_pair(xmin, xmax);
    }
  }
  return coverage;
}

auto Grid::get_line_coverage(int64_t line) const -> line_coverage_t {
  auto line_coverage = line_coverage_t{};
  std::ranges::for_each(_elements, [&line_coverage, &line, this](auto&& var) {
    std::visit(
        [&line_coverage, &line, this](auto&& arg) {
          using T = std::decay_t<decltype(arg)>;
          if constexpr (std::is_same_v<T, Sensor>) {
            if (auto coverage = get_line_coverage(arg, line); coverage) {
              line_coverage.emplace_back(*coverage);
            }
          }
        },
        var.second);
  });
  std::ranges::sort(line_coverage, std::less_equal());
  // reduce overlapped regions
  auto it = line_coverage.begin();
  while (true) {
    if (auto& [xmin1, xmax1] = *it++; it != line_coverage.end()) {
      auto& [xmin2, xmax2] = *it;
      if (xmin2 <= (xmax1 + 1)) {
        xmax1 = std::max(xmax1, xmax2);
        line_coverage.erase(it--);
      }
    } else {
      break;
    }
  }

  return line_coverage;
}

auto Grid::count_no_beacon_positions(int64_t y) const -> unsigned {
  auto line_coverage = get_line_coverage(y);

  int result = 0;
  for (auto [min, max] : line_coverage) {
    result += (max - min) + 1;
  }

  return result;
}

auto main_pt1([[maybe_unused]] int argc, [[maybe_unused]] char **argv) -> int {  //
  auto grid = Grid{};
  std::ranges::for_each(std::ranges::istream_view<Sensor>(std::cin),
                        [&grid](auto&& sensor) {  //
                          grid.emplace(std::forward<Sensor>(sensor));
                          grid.emplace(std::forward<Beacon>(sensor.beacon()));
                        });
  std::cout << "Part1:" << grid.count_no_beacon_positions(2000000) << std::endl;
  return 0;
}

auto main_pt2([[maybe_unused]] int argc, [[maybe_unused]] char **argv) -> int {  //
  auto grid = Grid{};
  std::ranges::for_each(std::ranges::istream_view<Sensor>(std::cin),
                        [&grid](auto&& sensor) {  //
                          grid.emplace(std::forward<Sensor>(sensor));
                          grid.emplace(std::forward<Beacon>(sensor.beacon()));
                        });

  for (int y = 0; y <= 4000000; ++y) {
    auto c = grid.get_line_coverage(y);
    assert(c.size() <= 2);
    if (c.size() == 2) {
      uint64_t x1 = c[0].second + 1;
      uint64_t x2 = c[1].first - 1;
      assert(x1 == x2);
      if (!grid.elem({{x1, y}})) {
        std::cout << "Part2:" << uint64_t{x1 * 4000000} + y << std::endl;
        break;
      }
    }
  }

  return 0;
}

}  // namespace aoc::day15
