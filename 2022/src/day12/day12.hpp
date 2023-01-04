#pragma once

#include <algorithm>
#include <iostream>
#include <optional>
#include <ranges>
#include <string>
#include <tuple>
#include <vector>

namespace aoc::day12 {

struct Heightmap {
  typedef std::tuple<int, int> pos_t;
  typedef std::tuple<char, std::optional<unsigned>> square_t;
  typedef std::vector<std::vector<square_t>> map_t;

  map_t _map;
  pos_t _spos;  // start position
  pos_t _epos;  // end position
  std::vector<pos_t> _alt_spos;

  auto create(std::istream&& is) {
    std::ranges::for_each(
        std::ranges::istream_view<std::string>(is),
        [row = 0, this](auto&& line) mutable {
          _map.emplace_back(line.size());
          std::ranges::transform(
              line, _map.back().begin(),
              [&row, col = 0, this](auto&& c) mutable {
                auto square = square_t{c, std::nullopt};
                if (c == 'S') {
                  _spos = std::make_tuple(row, col);
                  _alt_spos.emplace_back(_spos);
                } else if (c == 'a') {
                  _alt_spos.emplace_back(std::make_tuple(row, col));
                } else if (c == 'E') {
                  _epos = std::make_tuple(row, col);
                }
                ++col;
                return square;
              });
          ++row;
        });
  }

  void search(pos_t spos);
};

auto main_pt1([[maybe_unused]] int argc, [[maybe_unused]] char **argv) -> int;
auto main_pt2([[maybe_unused]] int argc, [[maybe_unused]] char **argv) -> int;
}  // namespace aoc::day12
