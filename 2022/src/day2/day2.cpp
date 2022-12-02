#include "day2/day2.hpp"

#include <algorithm>
#include <exception>
#include <iostream>
#include <numeric>
#include <ranges>
#include <sstream>

namespace aoc::day2 {

Game::Game(std::istream &input) {
  auto puzzle = std::ranges::istream_view<char>(input);

  std::ranges::for_each(
      puzzle.begin(), puzzle.end(), [opponent = '\0', this](char me) mutable {
        if (opponent) {
          _overall_score += Round1{opponent, me}.score();
          me = '\0';
        }
        std::exchange(opponent, me);
      });
}

auto Game::play() -> Game::Score_t { return _overall_score; }

auto main(int argc, char **argv) -> int {
  std::cout << "Part1:" << Game{std::cin}.play() << "\n";
  return 0;
}
}  // namespace aoc::day2