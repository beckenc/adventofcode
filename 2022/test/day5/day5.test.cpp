#include "day5/day5.hpp"

#include <iostream>
#include <sstream>
#include <ranges>

#include "gtest/gtest.h"

namespace aoc::day5 {

TEST(SimpleTestPt1, Day5) {
  auto input = std::stringstream{
      "\
    [D]    \n\
[N] [C]    \n\
[Z] [M] [P]\n\
 1   2   3 \n\
\n\
move 1 from 2 to 1\n\
move 3 from 1 to 3\n\
move 2 from 2 to 1\n\
move 1 from 1 to 2\n"};

  auto crate_stacks = CrateStacks{input};
  crate_stacks.print_stacks();

  for(auto rearrangement : std::ranges::istream_view<Rearrangement>(input))
  {
    crate_stacks.rearrange(std::move(rearrangement));
    crate_stacks.print_stacks();    
  }
}

TEST(SimpleTestPt2, Day5) {
  auto input = std::stringstream{
      "\
    [D]    \n\
[N] [C]    \n\
[Z] [M] [P]\n\
 1   2   3 \n\
\n\
move 1 from 2 to 1\n\
move 3 from 1 to 3\n\
move 2 from 2 to 1\n\
move 1 from 1 to 2\n"};

  auto crate_stacks = CrateStacks{input};
  crate_stacks.print_stacks();

  for(auto rearrangement : std::ranges::istream_view<Rearrangement>(input))
  {
    crate_stacks.rearrange_wo_reordering(std::move(rearrangement));
    crate_stacks.print_stacks();    
  }
}

}  // namespace aoc::day5