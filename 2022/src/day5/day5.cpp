#include "day5/day5.hpp"

#include <iostream>
#include <istream>
#include <ranges>
#include <regex>

namespace aoc::day5 {

CrateStacks::CrateStacks(std::istream &is) {
  auto line = std::string{};
  std::getline(is, line);
  for (_stacks.resize(((line.length() + 1) / 4)); !line.empty();
       std::getline(is, line)) {
    std::regex e("[A-Z]");
    std::for_each(std::sregex_iterator(line.begin(), line.end(), e),
                  std::sregex_iterator(), [this](auto &&match) {
                    _stacks[match.position() / 4].push_front(match.str()[0]);
                  });
  };
}

void CrateStacks::rearrange(Rearrangement &&rearrangement) {
  for (auto [what, from, to] = rearrangement._rule; what; --what) {
    _stacks[to].push_back(_stacks[from].back());
    _stacks[from].pop_back();
  }
}

void CrateStacks::rearrange_wo_reordering(Rearrangement &&rearrangement) {
  auto moved_crates = std::list<char>{};
  auto [what, from, to] = rearrangement._rule;
  for (; what; --what) {
    moved_crates.push_front(_stacks[from].back());
    _stacks[from].pop_back();
  }
  _stacks[to].splice(_stacks[to].end(), moved_crates);
}

void CrateStacks::print_stacks() const {
  for (auto stack : _stacks) {
    std::cout << "Stack: ";
    for (auto crate : stack) std::cout << crate;
    std::cout << "\n";
  }
  std::cout << "\n";
}

auto main_pt1(int argc, char **argv) -> int {
  unsigned result;

  auto crate_stacks = CrateStacks{std::cin};
  for (auto rearrangement :
       std::ranges::istream_view<Rearrangement>(std::cin)) {
    crate_stacks.rearrange(std::move(rearrangement));
  }
  crate_stacks.print_stacks();
  return 0;
}

auto main_pt2(int argc, char **argv) -> int {
  unsigned result;
  auto crate_stacks = CrateStacks{std::cin};
  for (auto rearrangement :
       std::ranges::istream_view<Rearrangement>(std::cin)) {
    crate_stacks.rearrange_wo_reordering(std::move(rearrangement));
  }
  crate_stacks.print_stacks();
  return 0;
}
}  // namespace aoc::day5
