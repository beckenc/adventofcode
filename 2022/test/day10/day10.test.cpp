#include "day10/day10.hpp"

#include <algorithm>
#include <iostream>
#include <ranges>

#include "gtest/gtest.h"

namespace aoc::day10 {

TEST(SimpleTest, day10) {
  auto input = std::vector<std::string>{
      "addx 15",  "addx -11", "addx 6",   "addx -3",  "addx 5",   "addx -1",
      "addx -8",  "addx 13",  "addx 4",   "noop",     "addx -1",  "addx 5",
      "addx -1",  "addx 5",   "addx -1",  "addx 5",   "addx -1",  "addx 5",
      "addx -1",  "addx -35", "addx 1",   "addx 24",  "addx -19", "addx 1",
      "addx 16",  "addx -11", "noop",     "noop",     "addx 21",  "addx -15",
      "noop",     "noop",     "addx -3",  "addx 9",   "addx 1",   "addx -3",
      "addx 8",   "addx 1",   "addx 5",   "noop",     "noop",     "noop",
      "noop",     "noop",     "addx -36", "noop",     "addx 1",   "addx 7",
      "noop",     "noop",     "noop",     "addx 2",   "addx 6",   "noop",
      "noop",     "noop",     "noop",     "noop",     "addx 1",   "noop",
      "noop",     "addx 7",   "addx 1",   "noop",     "addx -13", "addx 13",
      "addx 7",   "noop",     "addx 1",   "addx -33", "noop",     "noop",
      "noop",     "addx 2",   "noop",     "noop",     "noop",     "addx 8",
      "noop",     "addx -1",  "addx 2",   "addx 1",   "noop",     "addx 17",
      "addx -9",  "addx 1",   "addx 1",   "addx -3",  "addx 11",  "noop",
      "noop",     "addx 1",   "noop",     "addx 1",   "noop",     "noop",
      "addx -13", "addx -19", "addx 1",   "addx 3",   "addx 26",  "addx -30",
      "addx 12",  "addx -1",  "addx 3",   "addx 1",   "noop",     "noop",
      "noop",     "addx -9",  "addx 18",  "addx 1",   "addx 2",   "noop",
      "noop",     "addx 9",   "noop",     "noop",     "noop",     "addx -1",
      "addx 2",   "addx -37", "addx 1",   "addx 3",   "noop",     "addx 15",
      "addx -21", "addx 22",  "addx -6",  "addx 1",   "noop",     "addx 2",
      "addx 1",   "noop",     "addx -10", "noop",     "noop",     "addx 20",
      "addx 1",   "addx 2",   "addx 2",   "addx -6",  "addx -11", "noop",
      "noop",     "noop"};

  auto read_in_prog = [](auto&& input) {
    auto prog = CPU::prog_t{};
    std::ranges::for_each(input, [&prog](auto&& line) {
      auto inst = Instruction{};
      std::istringstream{line} >> inst;
      prog.emplace_back(std::move(inst));
    });
    return prog;
  };

  auto cpu = CPU{};
  cpu.load_programm(read_in_prog(input));

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
  EXPECT_EQ(signal_strength, 13140);


  auto crt = CRT{std::cout};
  crt.load_programm(read_in_prog(input));

  for (auto cycle = 0; !crt.eop(); ++cycle) {
    ++crt;
  }

}

}  // namespace aoc::day10