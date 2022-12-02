#pragma once
#include <istream>
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

class Round1 {
 public:
  typedef unsigned Score_t;
  explicit Round1(char opponent, char me)
      : Round1{to_shape(opponent), to_shape(me)} {}
  explicit Round1(SHAPE opponent, SHAPE me)
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

 private:
  SHAPE _shape;
  OUTCOME _outcome;
};

class Game {
  typedef std::vector<Round1> Rounds_t;

 public:
  typedef Round1::Score_t Score_t;
  explicit Game(std::istream &input);
  auto play() -> Score_t;

 private:
  Score_t _overall_score = 0;
  Rounds_t _rounds;
};

auto main(int argc, char **argv) -> int;
}  // namespace aoc::day2