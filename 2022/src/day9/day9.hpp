#pragma once
#include <algorithm>
#include <istream>
#include <ranges>
#include <tuple>
#include <vector>

namespace aoc::day9 {

enum class Direction : char { up = 'U', down = 'D', left = 'L', right = 'R' };

class Motion {
 public:
  typedef unsigned step_count_t;
  typedef std::tuple<Direction, step_count_t> motion_t;

  auto& get() { return _motion; }
  auto direction() const { return std::get<0>(_motion); }
  auto num_steps() const { return std::get<1>(_motion); }

 private:
  motion_t _motion;
};

class Motions {
 public:
  typedef std::vector<Motion> motions_t;
  auto append(Motion&& motion) { _motions.emplace_back(std::move(motion)); }

  auto get() { return _motions; }
  auto get() const { return _motions; }  

 private:
  motions_t _motions;
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
  std::ranges::for_each(motions.get(), [&os](auto&& motion) { os << motion << std::endl; });
  return os;
}

auto main_pt1(int argc, char** argv) -> int;
auto main_pt2(int argc, char** argv) -> int;
}  // namespace aoc::day9
