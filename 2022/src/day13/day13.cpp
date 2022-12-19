#include "day13/day13.hpp"

#include <algorithm>
#include <cassert>
#include <cctype>
#include <iostream>
#include <list>
#include <ranges>
#include <sstream>
#include <string>
#include <string_view>

namespace aoc::day13 {

std::istream& operator>>(std::istream& is, PacketPair& pp) {
  is >> pp.lists.first >> pp.lists.second;
  return is;
}

auto List::extract(std::string_view sv) -> std::string_view {
  if (sv.front() == '[') {
    list.emplace_back(List{});
    sv = list.back().child().extract(sv.substr(sv[1] == ']' ? 2 : 1));
    if (!sv.empty()) {
      sv = extract(sv.substr(1));
    }
  } else if (std::isdigit(sv.front())) {
    int i;
    std::stringstream{} << sv >> i;
    list.emplace_back(i);
    sv = extract(sv.substr(sv.find_first_not_of("1234567890") + 1));
  }
  return sv;
}
auto List::compare(List& right) -> int {
  if (list.empty() && right.list.empty()) {
    return 0;
  } else if (list.empty() && !right.list.empty()) {
    return -1;
  } else if (!list.empty() && right.list.empty()) {
    return 1;
  }

  auto result = 0;
  if (list.front().is_int()) {
    if (right.list.front().is_int()) {
      auto left_i = static_cast<int>(list.front());
      auto right_i = static_cast<int>(right.list.front());
      result = left_i < right_i ? -1 : left_i > right_i ? 1 : 0;
    } else {
      result = static_cast<List>(list.front()).compare(right);
    }
  } else {
    if (right.list.front().is_int()) {
      auto right_list = static_cast<List>(right.list.front());
      result = compare(right_list);
    } else {
      result = list.front().child().compare(right.list.front().child());
    }
  }

  if (result == 0 && !list.empty() && !right.list.empty()) {
    list.pop_front();
    right.list.pop_front();
    result = compare(right);
  }

  return result;
}

static bool compare_lists(std::string_view left, std::string_view right) {
  auto left_list = List{};
  auto right_list = List{};
  std::ignore = left_list.extract(left.substr(1));
  std::ignore = right_list.extract(right.substr(1));
  auto result = left_list.compare(right_list);
  return (result == 0) || (result == -1);
}

auto main_pt1(int argc, char** argv) -> int {
  auto result = 0;
  std::ranges::for_each(
      std::ranges::istream_view<PacketPair>(std::cin),
      [&result, i = 1](auto&& pair) mutable {
        result +=
            compare_lists(pair.lists.first, pair.lists.second) != 0 ? i : 0;
        ++i;
      });

  std::cout << "\nPart1: " << result << std::endl;
  return 0;
}

auto main_pt2(int argc, char** argv) -> int {
  auto input = std::vector<std::string>{"[[2]]", "[[6]]"};
  std::ranges::for_each(std::ranges::istream_view<PacketPair>(std::cin),
                        [&input](auto&& pair) mutable {
                          input.emplace_back(pair.lists.first);
                          input.emplace_back(pair.lists.second);
                        });
  std::ranges::sort(input, compare_lists);

  auto n2 = std::distance(input.begin(), std::ranges::find(input, "[[2]]"));
  auto n6 = std::distance(input.begin(), std::ranges::find(input, "[[6]]"));

  std::cout << "\nPart2: " << (n2 + 1) * (n6 + 1) << std::endl;
  return 0;
}
}  // namespace aoc::day13
