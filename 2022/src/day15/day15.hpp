#pragma once

#include <cstdint>
#include <iostream>
#include <limits>
#include <map>
#include <optional>
#include <tuple>
#include <variant>

#include "utils/utils.hpp"

namespace aoc::day15 {

class Beacon {
 public:
  Beacon() = default;
  Beacon(utils::Coordinates coordinates) : _position{coordinates} {}

  auto position() const { return _position; }

 private:
  utils::Coordinates _position;
};

class Sensor {
 public:
  Sensor() = default;
  Sensor(utils::Coordinates coordinates, Beacon beacon)
      : _position{coordinates}, _next_beacon{beacon}, _dist{dist(beacon)} {}

  auto position() const { return _position; }
  auto beacon() const { return _next_beacon; }

  inline int64_t dist(utils::Coordinates coordinates) const {
    return std::abs(_position.x() - coordinates.x()) +
           std::abs(_position.y() - coordinates.y());
  }
  inline int64_t dist(Beacon beacon) const {  //
    return dist(beacon.position());
  }
  inline int64_t dist() const {  //
    return _dist;
  }

 private:
  utils::Coordinates _position;
  Beacon _next_beacon;
  utils::Coordinates::type_t::first_type _dist;
};

class Grid {
 public:
  typedef std::variant<Sensor, Beacon> type_t;
  typedef std::map<utils::Coordinates, type_t> map_t;
  typedef std::optional<std::pair<int64_t, int64_t> > coverage_t;
  typedef std::vector<std::pair<int64_t, int64_t> > line_coverage_t;

  auto emplace(auto&& value) { _elements[value.position()] = value; }
  auto elem(utils::Coordinates point) const -> std::optional<type_t> {
    if (auto p = _elements.find(point); p != _elements.end()) {
      return p->second;
    }
    return std::nullopt;
  };
  const auto& range() const { return _elements; };
  auto count_no_beacon_positions(int64_t y) const -> unsigned;

  auto get_line_coverage(const Sensor& sensor, int64_t line) const
      -> coverage_t;
  auto get_line_coverage(int64_t line) const -> line_coverage_t;

 private:
  map_t _elements;
};

auto operator>>(std::istream& is, Sensor& sensor) -> std::istream&;

auto main_pt1(int argc, char** argv) -> int;
auto main_pt2(int argc, char** argv) -> int;
}  // namespace aoc::day15
