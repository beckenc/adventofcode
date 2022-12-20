#include "day14/day14.hpp"

#include <cassert>
#include <iostream>
#include <sstream>

namespace aoc::day14 {

std::istream& operator>>(std::istream& is, Coordinates& point) {
  auto x = int{};
  auto y = int{};
  auto c = char{};
  is >> x >> c >> y;
  point = Coordinates{{x, y}};
  return is;
}

std::istream& operator>>(std::istream& is, rock_t& rock) {
  auto line = std::string{};
  std::getline(is, line);
  auto iss = std::istringstream{line};

  auto devnull = std::string{};
  auto current = Coordinates{};
  iss >> current >> devnull;
  rock.emplace_back(std::move(current));

  while (iss >> current) {
    // add distance between predecessor and current also to the rock
    auto predecessor = rock.back();

    auto [x0, y0] = predecessor.xy();
    auto [x1, y1] = current.xy();

    auto x_distance = int{x1 - x0};
    auto x_dir = x_distance / std::abs(x_distance);
    for (auto x = 1; x < std::abs(x_distance); ++x) {
      rock.emplace_back(Coordinates{{x0 + x_dir * x, y0}});
    }

    auto y_distance = int{y1 - y0};
    auto y_dir = y_distance / std::abs(y_distance);
    for (auto y = 1; y < std::abs(y_distance); ++y) {
      rock.emplace_back(Coordinates{{x0, y0 + y_dir * y}});
    }

    assert(x_distance == 0 || y_distance == 0);

    rock.emplace_back(current);
    iss >> devnull;
  }
  return is;
}

auto operator<<(std::ostream& os, const Point& point) -> std::ostream& {
  os << static_cast<char>(point);
  return os;
}

auto operator<<(std::ostream& os, const Cave& cave) -> std::ostream& {
  auto [xmin, xmax] = cave.x_minmax();
  auto [ymin, ymax] = cave.y_minmax();

  for (auto y = ymin; y <= ymax + 1; ++y) {
    for (auto x = xmin - 1; x <= xmax + 1; ++x) {
      os << cave.point(Coordinates{{x, y}});
    }
    os << std::endl;
  }
  return os;
}

auto Cave::point(Coordinates coordinates) const -> Point {
  if (auto point = _cave.find(coordinates); point != _cave.end())
    return point->second;
  return Point::air;
}

auto Cave::drop_sand(Coordinates coordinates) -> bool {
  auto occupied = [this](auto&& coordinates) {
    auto point = this->point(coordinates);
    return point == Point::rock || point == Point::sand;
  };

  auto ymax = this->y_minmax().second;
  if (coordinates.y() >= ymax) {
    return false;
  }

  if (auto [left_below, below, right_below] = coordinates.adjacent();
      !occupied(below)) {
    return drop_sand(below);
  } else if (!occupied(left_below)) {
    return drop_sand(left_below);
  } else if (!occupied(right_below)) {
    return drop_sand(right_below);
  }
  if (_cave[coordinates] == Point::sand) {
    return false;
  }
  _cave[coordinates] = Point::sand;
  return true;
}

auto Cave::add(rock_t&& rock) -> void {
  std::ranges::for_each(rock, [this](auto&& point) {
    _dimension.first.first = std::min(point.x(), _dimension.first.first);
    _dimension.second.first = std::max(point.x(), _dimension.second.first);
    _dimension.first.second = std::min(point.y(), _dimension.first.second);
    _dimension.second.second = std::max(point.y(), _dimension.second.second);
    _cave.emplace(point, Point::rock);
  });
}

auto main_pt1(int argc, char** argv) -> int {
  auto cave = Cave{};
  std::ranges::for_each(std::ranges::istream_view<rock_t>(std::cin),
                        [&cave](auto&& rock) {  //
                          cave.add(std::forward<rock_t>(rock));
                        });
  auto sand_count = 0;
  while (cave.drop_sand({{500, 0}})) {
    sand_count++;
  }
  std::cout << "Part1: " << sand_count << std::endl;

  return 0;
}

auto main_pt2(int argc, char** argv) -> int {
  auto cave = Cave{};
  std::ranges::for_each(std::ranges::istream_view<rock_t>(std::cin),
                        [&cave](auto&& rock) {  //
                          cave.add(std::forward<rock_t>(rock));
                        });

  auto [min, max] = cave.x_minmax();

  auto xmin =
      std::to_string(min - 200);  // asume, that 200 is kind of infinitive
  auto xmax = std::to_string(max + 200);
  auto y = std::to_string(cave.y_floor());

  auto floordesc = xmin + "," + y + " -> " + xmax + "," + y;
  auto rock = rock_t{};
  std::istringstream{floordesc} >> rock;
  cave.add(std::move(rock));

  auto sand_count = 0;
  while (cave.drop_sand({{500, 0}})) {
    sand_count++;
  }

  std::cout << "Part2: " << sand_count << std::endl;

  return 0;
}
}  // namespace aoc::day14
