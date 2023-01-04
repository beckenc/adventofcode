#include "day7/day7.hpp"

#include <algorithm>
#include <iostream>
#include <limits>
#include <map>
#include <ranges>
#include <sstream>
#include <tuple>
#include <vector>


namespace aoc::day7 {

struct Line : public std::string {};

typedef std::vector<std::string> dir_stack_t;
typedef std::map<std::string, std::pair<dir_stack_t, unsigned>> dir_tree_t;

inline std::istream& operator>>(std::istream& is, Line& rs) {
  return std::getline(is, rs);
}

static auto dir_path(const dir_stack_t& dir_stack) -> std::string {
  auto path = std::string{};
  for (const auto& dir : dir_stack)
    if (dir != "/")
      path += dir + "/";
    else
      path = dir;
  return path;
}

static auto build_dir_tree(std::istream& is) {
  auto tree = dir_tree_t{};
  std::ranges::for_each(
      std::ranges::istream_view<Line>(is),
      [&tree, dir_stack = dir_stack_t{}](auto&& line) mutable {
        
        if (line[0] == '$') {
          if (auto found = line.find("cd .."); found != std::string::npos) {
            dir_stack.pop_back();
          } else if (found = line.find("cd "); found != std::string::npos) {
            dir_stack.emplace_back(line.substr(found + 3));
          }
        } else {
          auto curdir = dir_path(dir_stack);
          auto& [subdir_stack, curdir_size] = tree[curdir];

          unsigned file_size;
          if (std::stringstream{line} >> file_size; file_size) {
            curdir_size += file_size;
          } else {
            auto subdir = curdir + line.substr(4) + "/";
            subdir_stack.push_back(subdir);

            // add subdirectory also to its parent
            for (auto& [root, subtree] : tree) {
              if (auto result = std::ranges::find(subtree.first, curdir);
                  result != subtree.first.end())
                subtree.first.push_back(subdir);
            }
          }
        }
      });
  return tree;
}

auto total_dir_size(std::string dir, dir_tree_t& tree) {
  const auto& [subtree, dirsize] = tree[dir];
  auto result = dirsize;
  for (const auto& subdir : subtree) result += tree[subdir].second;
  return result;
}

auto main_pt1([[maybe_unused]] int argc, [[maybe_unused]] char **argv) -> int {
  auto tree = build_dir_tree(std::cin);

  auto result = 0;
  for (const auto& [root, subtree] : tree) {
    auto& [subdir_stack, size] = subtree;
    auto total_dir_size = size;
    for (auto subdir : subdir_stack) {
      total_dir_size += tree[subdir].second;
    }
    if (total_dir_size <= 100000) {
      std::cout << total_dir_size << std::endl;
      result += total_dir_size;
    }
  }
  std::cout << "Part1:" << result << std::endl;
  return 0;
}

auto main_pt2([[maybe_unused]] int argc, [[maybe_unused]] char **argv) -> int {
  auto tree = build_dir_tree(std::cin);

  auto free = 70000000 - total_dir_size("/", tree);
  auto missing = 30000000 - free;

  auto to_delete = std::numeric_limits<unsigned>::max();
  for (const auto& [dir, size] : tree) {
    if (auto total = total_dir_size(dir, tree);
        total >= missing && total < to_delete)
      to_delete = total;
  }
  std::cout << "Part2:" << to_delete << std::endl;

  return 0;
}
}  // namespace aoc::day7
