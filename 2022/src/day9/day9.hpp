#pragma once
#include <algorithm>
#include <iostream>
#include <istream>
#include <ranges>
#include <set>
#include <tuple>
#include <vector>
#include <cassert>

namespace aoc::day9 {

enum class Direction : char { up = 'U', down = 'D', left = 'L', right = 'R' };

/**
 * 
 */
class Motion {
 public:
  typedef unsigned step_count_t;
  typedef std::tuple<Direction, step_count_t> motion_t;

  Motion() = default;
  Motion(motion_t motion) : _motion{motion} {}
  auto& get() { return _motion; }
  constexpr auto direction() const { return std::get<0>(_motion); }
  constexpr auto num_steps() const { return std::get<1>(_motion); }

 private:
  motion_t _motion;
};

/**
 * 
 */
class Motions {
 public:
  typedef std::vector<Motion> motions_t;
  auto append(Motion&& motion) { _motions.emplace_back(std::move(motion)); }

  auto get() { return _motions; }
  auto get() const { return _motions; }

 private:
  motions_t _motions;
};

class Position {
 public:
  typedef unsigned x_t;
  typedef unsigned y_t;
  typedef std::pair<x_t, y_t> position_t;

  Position() = default;
  Position(x_t x, y_t y) : _position{x, y} {}

  auto get() const { return _position; }
  constexpr void move(Motion motion) {
    motion.direction() == Direction::up     ? move_up(motion.num_steps())
    : motion.direction() == Direction::down ? move_down(motion.num_steps())
    : motion.direction() == Direction::left ? move_left(motion.num_steps())
                                            : move_right(motion.num_steps());
  }

 private:
  constexpr void move_up(auto num_steps) { _position.second += num_steps; }
  constexpr void move_down(auto num_steps) { _position.second -= num_steps; }
  constexpr void move_left(auto num_steps) { _position.first -= num_steps; }
  constexpr void move_right(auto num_steps) { _position.first += num_steps; }

  position_t _position{0, 0};
};

class Knot {
 public:
  auto pos() const { return _pos; }
  constexpr auto move(Motion motion) { _pos.move(motion); }

 protected:
  Position _pos;
};

class Head : public Knot {
 public:
 private:
};

class Tail : public Knot {
 public:
  auto follow(Head head) {
    auto [hx, hy] = head.pos().get();
    auto [tx, ty] = _pos.get();

    if (((hy == ty) && (hx == tx)) ||              // H

        ((hy == ty) && (hx == (tx + 1))) ||        // TH

        ((hy == ty) && (hx == (tx - 1))) ||        // HT

                                                   // H
        ((hy == (ty + 1)) && (hx == tx)) ||        // T

                                                   // T
        ((hy == (ty - 1)) && (hx == tx)) ||        // H

                                                   //  T
        ((hy == (ty - 1)) && (hx == (tx - 1))) ||  // H

                                                   // T
        ((hy == (ty - 1)) && (hx == (tx + 1))) ||  //  H

                                                   //  H
        ((hy == (ty + 1)) && (hx == (tx + 1))) ||  // T

                                                   // H
        ((hy == (ty + 1)) && (hx == (tx - 1)))     //  T
    ) {
      return;  // keep position
    }
    else
    {
      
    }

    if (hy == ty) {
      if (hx > tx) {
        _pos = {hx - 1, hy};  // follow right
      } else if (hx < tx) {
        _pos = {hx + 1, hy};  // follow left
      } else {
        throw std::runtime_error("missing case");        
      }

    } else if (hx == tx) {
      if (hy > ty) {
        _pos = {hx, hy - 1};  // follow up
      } else if (hy < ty) {
        _pos = {hx, hy + 1};  // follow down
      } else {
        throw std::runtime_error("missing case");        
      }

    } else if (hy > (ty + 1)) {
      _pos = {hx, hy - 1};  // follow up     ....H.
                            //               ....x.
                            //               ...T.T
    } else if (hy < (ty - 1)) {
      _pos = {hx, hy + 1};  // follow down   ..T.T.
                            //               ...x..
                            //               ...H..
    } else if (hx < (tx - 1)) {
      _pos = {hx + 1, hy};  // follow left   ....T.
                            //               ..Hx..
                            //               ....T.
    } else if (hx > (tx + 1)) {
      _pos = {hx - 1, hy};  // follow right  ..T...
                            //               ...xH.
                            //               ..T...      
    } else {
      throw std::runtime_error("missing case");
    }
  }

 private:
};

class Grid {
 public:
  typedef std::set<Position::position_t> grid_t;
  typedef std::tuple<Position::x_t, Position::y_t> dimension_t;
  auto get() const { return _grid; }
  auto dimension() const { return _dimension; }
  auto visit(Position pos) {
    auto coordinates = pos.get();
    auto& [dx, dy] = _dimension;
    auto& [cx, cy] = coordinates;
    if (dx < cx) dx = cx;
    if (dy < cy) dy = cy;
    _grid.insert(coordinates);
  }
  auto visited_fields() const { return _grid.size(); }

 private:
  grid_t _grid;
  dimension_t _dimension = {0, 0};
};

inline std::istream& operator>>(std::istream& is, Direction& direction) {
  auto d = char{};
  is >> d;
  direction = static_cast<Direction>(d);
  return is;
}

inline std::istream& operator>>(std::istream& is, Motion& motion) {
  auto& [dir, count] = motion.get();
  is >> dir >> count;
  return is;
}

inline std::ostream& operator<<(std::ostream& os, const Direction& direction) {
  os << static_cast<char>(direction);
  return os;
}

inline std::ostream& operator<<(std::ostream& os, const Motion& motion) {
  os << motion.direction() << " " << motion.num_steps();
  return os;
}

inline std::ostream& operator<<(std::ostream& os, const Motions& motions) {
  std::ranges::for_each(motions.get(),
                        [&os](auto&& motion) { os << motion << std::endl; });
  return os;
}

inline std::ostream& operator<<(std::ostream& os, Grid& grid) {
  auto [dx, dy] = grid.dimension();
  do {
    for (auto x = 0; x <= dx; ++x) {
      if (auto pos = grid.get().find({x, dy}); pos != grid.get().end())
        os << "#";
      else
        os << ".";
    }
    os << std::endl;
  } while (dy--);
  return os;
}

auto main_pt1(int argc, char** argv) -> int;
auto main_pt2(int argc, char** argv) -> int;
}  // namespace aoc::day9
