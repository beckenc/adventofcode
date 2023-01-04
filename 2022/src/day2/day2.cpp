#include "day2/day2.hpp"

#include <exception>
#include <iostream>
#include <numeric>
#include <ranges>
#include <sstream>

namespace aoc::day2 {

auto to_shape(char c) -> SHAPE{
  return (c == 'A' || c == 'X')   ? SHAPE::rock
         : (c == 'B' || c == 'Y') ? SHAPE::paper
         : (c == 'C' || c == 'Z') ? SHAPE::sizzor
                                  : throw std::bad_cast();
};

auto to_outcome(char c) -> OUTCOME {
  return c == 'X'   ? OUTCOME::lost
         : c == 'Y' ? OUTCOME::draw
         : c == 'Z' ? OUTCOME::win
                    : throw std::bad_cast();
};

Round1::Round1(SHAPE opponent, SHAPE me)
    : _outcome{(opponent == me) ? OUTCOME::draw
               : ((opponent == SHAPE::rock) && (me == SHAPE::paper)) ||
                       ((opponent == SHAPE::paper) && (me == SHAPE::sizzor)) ||
                       ((opponent == SHAPE::sizzor) && (me == SHAPE::rock))
                   ? OUTCOME::win
                   : OUTCOME::lost},
      _shape{me} {}

Round2::Round2(SHAPE opponent, OUTCOME outcome)
    : _outcome{outcome},
      _shape{(outcome == OUTCOME::draw) ? opponent
             : (outcome == OUTCOME::win)
                 ? ((opponent == SHAPE::paper)  ? SHAPE::sizzor
                    : (opponent == SHAPE::rock) ? SHAPE::paper
                                                : SHAPE::rock)
             : (opponent == SHAPE::paper) ? SHAPE::rock
             : (opponent == SHAPE::rock)  ? SHAPE::sizzor
                                          : SHAPE::paper} {}

auto main_pt1([[maybe_unused]] int argc, [[maybe_unused]] char **argv) -> int {
  std::cout << "Part1:" << Game<Round1>{std::cin}.play() << "\n";
  return 0;
}
auto main_pt2([[maybe_unused]] int argc, [[maybe_unused]] char **argv) -> int {
  std::cout << "Part2:" << Game<Round2>{std::cin}.play() << "\n";
  return 0;
}
}  // namespace aoc::day2