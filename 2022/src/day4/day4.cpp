#include "day4/day4.hpp"

#include <iomanip>
#include <iostream>
#include <ranges>
#include <string>
#include <string_view>
#include <algorithm>

namespace aoc::day4 {

using namespace std::literals;

auto main_pt1(int argc, char **argv) -> int {
  typedef std::array<unsigned, 2> range_t;
  typedef std::array<range_t, 2> elf_pair_t;

  auto result = unsigned{0};
  std::ranges::for_each(std::ranges::istream_view<std::string>(std::cin), [&result](auto&& elf_pair){
    auto elfs = elf_pair_t{};
    std::ranges::for_each(elf_pair | std::views::split(","sv), [eit=elfs.begin()](auto&& range) mutable {
      std::ranges::for_each(range | std::views::split("-"sv), [rit=eit->begin()](auto&& bound) mutable {
        std::stringstream ss;
        std::ranges::for_each(bound, [&ss](auto&& n){ ss << n; });
        ss >> *rit++;
      });
      eit++;
    });
    
    auto [low1, high1] = elfs[0];
    auto [low2, high2] = elfs[1];
    auto is_within = [](auto l1, auto h1, auto l2, auto h2){ return (l1 >= l2) && (h1 <= h2); };
    if(is_within(low1, high1, low2, high2) || is_within(low2, high2, low1, high1))
      result++;
  });
  std::cout << "Part1:" << result << std::endl;
  return 0;
}

auto main_pt2(int argc, char **argv) -> int { return 0; }
}  // namespace aoc::day4
