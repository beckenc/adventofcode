#pragma once
#include <algorithm>
#include <exception>
#include <iostream>
#include <optional>
#include <ranges>
#include <set>
#include <tuple>
#include <vector>

namespace aoc::day8 {

typedef unsigned Tree;

class Grid : public std::vector<std::vector<Tree>> {
  auto update_visibily_map(auto&& trees, unsigned i, auto&& inserter) {
    std::ranges::for_each(
        trees, [&inserter, &i, j = 0,
                highest = std::optional<Tree>{}](auto&& tree) mutable {
          if (!highest || tree > *highest) {
            inserter(i, j);
            highest = tree;
          }
          j++;
        });
  }

 public:
  auto get_row(unsigned row) const { 
    return at(row);
  }

  auto get_column(unsigned col) const {
    std::vector<unsigned> column;
    std::ranges::for_each(*this, [&column, col](auto&& row) {
      column.emplace_back(row[col]);
    });
    return column;
  }

  auto get_score(unsigned irow, unsigned icol) const {
    auto row = get_row(irow);
    auto col = get_column(icol);
    auto considered_tree = at(irow).at(icol);

    auto count_score = [considered_tree, blocked = false](Tree tree) mutable {
      if (blocked) return false;
      if (tree >= considered_tree) blocked = true;
      return true;
    };

    // to the right
    auto c = std::ranges::count_if(row | std::views::drop(icol + 1), count_score);
    // to the left
    c *= std::ranges::count_if(row | std::views::reverse | std::views::drop(col.size() - icol), count_score);
    // to the bottom
    c *= std::ranges::count_if(col | std::views::drop(irow + 1), count_score);
    // to the top
    c *= std::ranges::count_if(col | std::views::reverse | std::views::drop(row.size() - irow), count_score);

    return c;
  }

  auto get_high_score() const {
    unsigned high_score = 0;
    for (auto irow = 0; irow < size(); ++irow)
      for (auto icol = 0; icol < at(irow).size(); ++icol)
        if (auto c = get_score(irow, icol); c > high_score) {
          high_score = c;
        }
    return high_score;
  }

  auto get_visibilities() {
    std::set<std::pair<unsigned, unsigned>> visibilites;

    auto row_inserter = [&visibilites](auto row, auto col) {
      visibilites.insert({row, col});
    };
    auto row_reverse_inserter = [&visibilites, this](auto row, auto col) {
      visibilites.insert({row, this->at(row).size() - 1 - col});
    };
    auto col_inserter = [&visibilites](auto col, auto row) {
      visibilites.insert({row, col});
    };
    auto col_reverse_inserter = [&visibilites, this](auto col, auto row) {
      visibilites.insert({size() - 1 - row, col});
    };

    for (auto i = 0; i < size(); ++i) {
      auto row = get_row(i);
      update_visibily_map(row, i, row_inserter);
      update_visibily_map(row | std::views::reverse, i, row_reverse_inserter);
    }
    for (auto i = 0; i < this->at(0).size(); ++i) {
      auto col = get_column(i);
      update_visibily_map(col, i, col_inserter);
      update_visibily_map(col | std::views::reverse, i, col_reverse_inserter);
    }
    return visibilites;
  }
};

inline std::istream& operator>>(std::istream& is, Grid& rs) {
  for (auto line : std::ranges::istream_view<std::string>(is)) {
    rs.emplace_back(std::vector<Tree>{});
    rs.back().resize(line.size());
    std::ranges::copy(line | std::views::transform([](char c) {
                        return static_cast<unsigned>(c - 48);
                      }),
                      std::begin(rs.back()));
  }

  return is;
}

auto main_pt1(int argc, char** argv) -> int;
auto main_pt2(int argc, char** argv) -> int;
}  // namespace aoc::day8
