#include <algorithm>
#include <filesystem>
#include <iostream>
#include <limits>
#include <map>
#include <numeric>
#include <ranges>
#include <sstream>

#include "day7/day7.hpp"

namespace aoc::day7 {

struct Line : public std::string {};

typedef std::map<std::filesystem::path, unsigned> tree_t;

inline std::istream& operator>>(std::istream& is, Line& rs) {
  return std::getline(is, rs);
}

static auto build_dir_tree(std::istream& is) {
  auto tree = tree_t{};
  std::ranges::for_each(
      std::ranges::istream_view<Line>(is),
      [&tree, path = std::filesystem::path{"/"}](auto&& line) mutable {
        if (line[0] == '$') {
          if (line.find("cd ..") != std::string::npos) {
            path = path.parent_path();
          } else if (line.find("cd ") != std::string::npos) {
            path /= line.substr(5);
          }
        } else {
          unsigned file_size;
          if (std::stringstream{line} >> file_size; file_size)
            tree[path] += file_size;
          else
            tree[path / line.substr(4)];
        }
      });
  // accumulate directory
  std::ranges::for_each(tree, [&tree](auto&& dir) {
    auto& [dpath, dsize] = dir;
    for (auto [path, size] : tree) {
      if (path != dpath &&
          path.string().find(dpath.string()) != std::string::npos) {
        dsize += size;
      }
    }
  });

  return tree;
}

auto main_pt1(int argc, char** argv) -> int {
  auto tree = build_dir_tree(std::cin);

  auto values =
      tree |
      std::views::filter([](auto&& dir) { return dir.second <= 100000; }) |
      std::views::values;

  auto result = std::accumulate(values.begin(), values.end(), 0);
  std::cout << "Part1:" << result << std::endl;
  return 0;
}

auto main_pt2(int argc, char** argv) -> int {
  auto tree = build_dir_tree(std::cin);

  auto free = 70000000 - tree["/"];
  auto missing = 30000000 - free;
  auto result =
      std::ranges::min(tree | std::views::filter([missing](auto&& dir) {
                         return dir.second >= missing;
                       }) |
                       std::views::values);

  std::cout << "Part2:" << result << std::endl;
  return 0;
}
}  // namespace aoc::day7
