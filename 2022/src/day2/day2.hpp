#pragma once
#include <algorithm>
#include <iostream>
#include <istream>
#include <ranges>
#include <sstream>
#include <vector>

namespace aoc::day2 {

enum class SHAPE : unsigned { rock = 1, paper = 2, sizzor = 3 };
enum class OUTCOME : unsigned { lost = 0, draw = 3, win = 6 };

auto to_shape(char c) -> SHAPE;
auto to_outcome(char c) -> OUTCOME;

class Round1 {
  OUTCOME _outcome;
  SHAPE _shape;

 public:
  typedef unsigned Score_t;
  Round1(char opponent, char me) : Round1{to_shape(opponent), to_shape(me)} {}
  Round1(SHAPE opponent, SHAPE me);
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
  Round2(SHAPE opponent, OUTCOME outcome);

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