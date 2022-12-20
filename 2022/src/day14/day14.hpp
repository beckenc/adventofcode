#pragma once

#include <algorithm>
#include <iostream>
#include <limits>
#include <map>
#include <optional>
#include <ranges>
#include <tuple>
#include <vector>

namespace aoc::day14 {

class Coordinates {
 public:
  typedef std::pair<int, int> type_t;

  Coordinates() = default;
  Coordinates(type_t&& coordinates) : _coordinates{coordinates} {}

  auto x() const { return _coordinates.first; }
  auto y() const { return _coordinates.second; }
  auto xy() const { return _coordinates; }

  auto adjacent() const {
    return std::make_tuple(Coordinates{{x() - 1, y() + 1}},
                           Coordinates{{x(), y() + 1}},
                           Coordinates{{x() + 1, y() + 1}});
  };

  auto operator<=>(const Coordinates& rhs) const {
    return _coordinates <=> rhs._coordinates;
  };

 private:
  std::pair<int, int> _coordinates;
};

enum class Point : char { air = '.', rock = '#', sand = 'o', foo = '~' };

typedef std::vector<Coordinates> rock_t;

class Cave {
  typedef std::map<Coordinates, Point> type_t;

 public:
  auto add(rock_t&& rock) -> void;
  auto point(Coordinates coordinates) const -> Point;
  auto adjacent(Coordinates coordinates) const {
    auto [left, below, right] = coordinates.adjacent();
    return std::make_tuple(point(left), point(below), point(right));
  }
  auto drop_sand(Coordinates coordinates) -> bool;
  auto x_minmax() const {
    return std::make_pair(_dimension.first.first, _dimension.second.first);
  }
  auto y_minmax() const { return std::make_pair(0, _dimension.second.second); }
  auto y_floor() const { return _dimension.second.second + 2; }

 private:
  std::pair<Coordinates::type_t, Coordinates::type_t> _dimension = {
      {std::numeric_limits<Coordinates::type_t::first_type>::max(),
       std::numeric_limits<Coordinates::type_t::first_type>::max()},
      {std::numeric_limits<Coordinates::type_t::first_type>::min(),
       std::numeric_limits<Coordinates::type_t::first_type>::min()}};
  type_t _cave;
};

auto operator>>(std::istream& is, Coordinates& point) -> std::istream&;
auto operator>>(std::istream& is, rock_t& rock) -> std::istream&;
auto operator<<(std::ostream& os, const Point& point) -> std::ostream&;
auto operator<<(std::ostream& os, const Cave& cave) -> std::ostream&;

auto main_pt1(int argc, char** argv) -> int;
auto main_pt2(int argc, char** argv) -> int;
}  // namespace aoc::day14
