#include "day10/day10.hpp"

#include <iostream>
#include <ranges>
#include <algorithm>

namespace aoc::day10 {

auto main_pt1(int argc, char **argv) -> int {
  auto prog = CPU::prog_t{};

  std::ranges::for_each(std::ranges::istream_view<Instruction>(std::cin), [&prog](auto&& instruction){
    prog.emplace_back(std::forward<Instruction>(instruction));
  });

  auto cpu = CPU{};
  cpu.load_programm(std::move(prog));

  auto signal_strength = 0;
  for (auto cycle = 0; !cpu.eop(); ++cycle) {
    switch (cycle) {
      case 19:
      case 59:
      case 99:
      case 139:
      case 179:
      case 219:
        signal_strength += (cycle + 1) * cpu._regX;
    }
    ++cpu;
  }

  std::cout << "Part1:" << signal_strength << std::endl;

  return 0;
}

auto main_pt2(int argc, char **argv) -> int {
  return 0;
}
}  // namespace aoc::day10

