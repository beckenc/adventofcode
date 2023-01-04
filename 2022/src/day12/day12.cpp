#include "day12/day12.hpp"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <limits>
#include <queue>
#include <ranges>

namespace aoc::day12 {

void Heightmap::search(pos_t spos) {
  constexpr auto can_step = [](char c1, char c2) {
    return (c1 >= c2) ? true : (c1 + 1) == c2;
  };

  auto step_count = [this](auto pos) {
    auto [row, col] = pos;
    return std::get<1>(_map[row][col]);
  };

  auto square_value = [this](auto pos) {
    auto [row, col] = pos;
    auto v = std::get<0>(_map[row][col]);
    if (v == 'S')
      v = 'a';
    else if (v == 'E')
      v = 'z';
    return v;
  };

  auto mark_visited = [this](auto pos, auto step) {
    auto [row, col] = pos;
    if (auto &sc = std::get<1>(_map[row][col]); !sc) {  //
      sc = step;
      return true;
    }
    return false;
  };

  auto neighbors = [this](auto pos) {
    auto result = std::vector<Heightmap::pos_t>{};
    auto [row, col] = pos;
    if (col > 0) {  // on the left
      result.emplace_back(Heightmap::pos_t{row, col - 1});
    }
    if (col < (std::ssize(_map[row]) - 1)) {  // on the right
      result.emplace_back(Heightmap::pos_t{row, col + 1});
    }
    if (row > 0) {  // above
      result.emplace_back(Heightmap::pos_t{row - 1, col});
    }
    if (row < (std::ssize(_map) - 1)) {  // below
      result.emplace_back(Heightmap::pos_t{row + 1, col});
    }
    return result;
  };

  std::queue<Heightmap::pos_t> queue;
  queue.push(spos);
  mark_visited(spos, 0);

  while (!queue.empty()) {
    auto square = queue.front();
    queue.pop();

    auto step_cnt = step_count(square);
    for (auto neighbor : neighbors(square)) {
      if (can_step(square_value(square), square_value(neighbor))) {
        assert(step_cnt.has_value());
        if (mark_visited(neighbor, step_cnt.value() + 1)) {  //
          queue.push(neighbor);
        }
      }
    }
  }
}

auto main_pt1([[maybe_unused]] int argc, [[maybe_unused]] char **argv) -> int {
  auto input = std::ranges::istream_view<std::string>(std::cin);

  auto heightmap = Heightmap{};
  heightmap.create(std::move(std::cin));
  heightmap.search(heightmap._spos);

  auto [row, col] = heightmap._epos;
  auto square = heightmap._map[row][col];
  assert(std::get<0>(square) == 'E');
  assert(std::get<1>(square));

  std::cout << "Part#1: " << std::get<1>(square).value() << std::endl;

  return 0;
}

auto main_pt2([[maybe_unused]] int argc, [[maybe_unused]] char **argv) -> int {
  auto input = std::ranges::istream_view<std::string>(std::cin);

  auto org_heightmap = Heightmap{};
  org_heightmap.create(std::move(std::cin));

  auto min_steps = std::numeric_limits<unsigned>::max();
  for (auto spos : org_heightmap._alt_spos) {
    auto heightmap = org_heightmap;

    heightmap.search(spos);

    auto [row, col] = heightmap._epos;
    auto square = heightmap._map[row][col];
    assert(std::get<0>(square) == 'E');

    if (auto steps = std::get<1>(square);
        steps && steps.value() < min_steps)  //
      min_steps = steps.value();
  }
  std::cout << "Part#2: " << min_steps << std::endl;

  return 0;
}
}  // namespace aoc::day12
