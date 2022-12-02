#pragma once
#include <algorithm>
#include <iostream>
#include <istream>
#include <ranges>
#include <sstream>
#include <vector>

namespace aoc::day2 {

enum class SHAPE : unsigned { rock = 1, paper = 2, sizzor = 3 };
inline auto to_shape(char c) {
  return (c == 'A' || c == 'X')   ? SHAPE::rock
         : (c == 'B' || c == 'Y') ? SHAPE::paper
         : (c == 'C' || c == 'Z') ? SHAPE::sizzor
                                  : throw std::bad_cast();
};

enum class OUTCOME : unsigned { lost = 0, draw = 3, win = 6 };
inline auto to_outcome(char c) {
  return c == 'X'   ? OUTCOME::lost
         : c == 'Y' ? OUTCOME::draw
         : c == 'Z' ? OUTCOME::win
                    : throw std::bad_cast();
};

class Round1 {
  OUTCOME _outcome;
  SHAPE _shape;

 public:
  typedef unsigned Score_t;
  Round1(char opponent, char me) : Round1{to_shape(opponent), to_shape(me)} {}
  Round1(SHAPE opponent, SHAPE me)
      : _outcome{(opponent == me) ? OUTCOME::draw
                 : ((opponent == SHAPE::rock) && (me == SHAPE::paper)) ||
                         ((opponent == SHAPE::paper) &&
                          (me == SHAPE::sizzor)) ||
                         ((opponent == SHAPE::sizzor) && (me == SHAPE::rock))
                     ? OUTCOME::win
                     : OUTCOME::lost},
        _shape{me} {}
  auto score() const {
    return static_cast<Score_t>(_shape) + static_cast<Score_t>(_outcome);
  }
};

class Round2 {
  OUTCOME _outcome;
  SHAPE _shape;

 public:
  typedef unsigned Score_t;
  Round2(char opponent, char me) : Round2{to_shape(opponent), to_outcome(me)} {}
  Round2(SHAPE opponent, OUTCOME outcome)
      : _outcome{outcome},
        _shape{(outcome == OUTCOME::draw) ? opponent
               : (outcome == OUTCOME::win)
                   ? ((opponent == SHAPE::paper)  ? SHAPE::sizzor
                      : (opponent == SHAPE::rock) ? SHAPE::paper
                                                  : SHAPE::rock)
               : (opponent == SHAPE::paper) ? SHAPE::rock
               : (opponent == SHAPE::rock)  ? SHAPE::sizzor
                                            : SHAPE::paper} {}
  auto score() const {
    return static_cast<Score_t>(_shape) + static_cast<Score_t>(_outcome);
  }
};

template <class Round>
class Game {
 public:
  typedef Round::Score_t Score_t;
  explicit Game(std::istream &input) {
    auto puzzle = std::ranges::istream_view<char>(input);
    std::ranges::for_each(puzzle.begin(), puzzle.end(),
                          [opponent = '\0', this](char me) mutable {
                            if (opponent) {
                              _overall_score += Round{opponent, me}.score();
                              me = '\0';
                            }
                            std::exchange(opponent, me);
                          });
  }

  auto play() const { return _overall_score; }

 private:
  Score_t _overall_score = 0;
};

auto main_pt1(int argc, char **argv) -> int;
auto main_pt2(int argc, char **argv) -> int;
}  // namespace aoc::day2