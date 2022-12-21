#pragma once

#include <algorithm>
#include <iostream>
#include <tuple>
#include <limits>

namespace aoc::utils {

class Coordinates {
 public:
  typedef std::pair<int64_t, int64_t> type_t;

  Coordinates() = default;
  Coordinates(type_t&& coordinates) : _coordinates{coordinates} {}

  auto x() const { return _coordinates.first; }
  auto y() const { return _coordinates.second; }
  auto xy() const { return _coordinates; }

  auto operator<=>(const Coordinates& rhs) const {
    return _coordinates <=> rhs._coordinates;
  };

 private:
  type_t _coordinates{0, 0};
};

class XYDimension {
 public:
  auto update(utils::Coordinates point) {
    _dimension.first.first = std::min(point.x(), _dimension.first.first);
    _dimension.second.first = std::max(point.x(), _dimension.second.first);
    _dimension.first.second = std::min(point.y(), _dimension.first.second);
    _dimension.second.second = std::max(point.y(), _dimension.second.second);
  }

  auto x_minmax() const {
    return std::make_pair(_dimension.first.first, _dimension.second.first);
  }
  auto y_minmax() const {
    return std::make_pair(_dimension.first.second, _dimension.second.second);
  }

 private:
  std::pair<utils::Coordinates::type_t, utils::Coordinates::type_t> _dimension =
      {{std::numeric_limits<utils::Coordinates::type_t::first_type>::max(),
        std::numeric_limits<utils::Coordinates::type_t::first_type>::max()},
       {std::numeric_limits<utils::Coordinates::type_t::first_type>::min(),
        std::numeric_limits<utils::Coordinates::type_t::first_type>::min()}};
};

auto operator>>(std::istream& is, Coordinates& point) -> std::istream&;

}  // namespace aoc::utils