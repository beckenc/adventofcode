#include <filesystem>
#include <functional>
#include <iostream>
#include <map>
#include <string_view>

#include "day1/day1.hpp"
#include "day2/day2.hpp"
#include "day3/day3.hpp"
#include "day4/day4.hpp"
#include "day5/day5.hpp"
#include "day6/day6.hpp"
#include "day7/day7.hpp"
#include "day8/day8.hpp"
#include "day9/day9.hpp"
#include "day10/day10.hpp"
#include "day11/day11.hpp"
#include "day12/day12.hpp"
#include "day13/day13.hpp"
#include "day14/day14.hpp"
#include "day15/day15.hpp"
// #include "day16/day16.hpp"
// #include "day17/day17.hpp"
// #include "day18/day18.hpp"
// #include "day19/day19.hpp"
// #include "day20/day20.hpp"
// #include "day21/day21.hpp"
// #include "day22/day22.hpp"
// #include "day23/day23.hpp"
// #include "day24/day24.hpp"
// #include "day25/day25.hpp"


namespace fs = std::filesystem;

int main(int argc, char **argv) {
  std::map<std::string_view, std::function<int(int, char **)> > day_fn;
  day_fn.insert({"day1_1", [](int ac, char **av) { return aoc::day1::main_pt1(ac, av); }});
  day_fn.insert({"day1_2", [](int ac, char **av) { return aoc::day1::main_pt2(ac, av); }});
  day_fn.insert({"day2_1", [](int ac, char **av) { return aoc::day2::main_pt1(ac, av); }});
  day_fn.insert({"day2_2", [](int ac, char **av) { return aoc::day2::main_pt2(ac, av); }});
  day_fn.insert({"day3_1", [](int ac, char **av) { return aoc::day3::main_pt1(ac, av); }});
  day_fn.insert({"day3_2", [](int ac, char **av) { return aoc::day3::main_pt2(ac, av); }});
  day_fn.insert({"day4_1", [](int ac, char **av) { return aoc::day4::main_pt1(ac, av); }});
  day_fn.insert({"day4_2", [](int ac, char **av) { return aoc::day4::main_pt2(ac, av); }});
  day_fn.insert({"day5_1", [](int ac, char **av) { return aoc::day5::main_pt1(ac, av); }});
  day_fn.insert({"day5_2", [](int ac, char **av) { return aoc::day5::main_pt2(ac, av); }});
  day_fn.insert({"day6_1", [](int ac, char **av) { return aoc::day6::main_pt1(ac, av); }});
  day_fn.insert({"day6_2", [](int ac, char **av) { return aoc::day6::main_pt2(ac, av); }});
  day_fn.insert({"day7_1", [](int ac, char **av) { return aoc::day7::main_pt1(ac, av); }});
  day_fn.insert({"day7_2", [](int ac, char **av) { return aoc::day7::main_pt2(ac, av); }});
  day_fn.insert({"day8_1", [](int ac, char **av) { return aoc::day8::main_pt1(ac, av); }});
  day_fn.insert({"day8_2", [](int ac, char **av) { return aoc::day8::main_pt2(ac, av); }});
  day_fn.insert({"day9_1", [](int ac, char **av) { return aoc::day9::main_pt1(ac, av); }});
  day_fn.insert({"day9_2", [](int ac, char **av) { return aoc::day9::main_pt2(ac, av); }});
  day_fn.insert({"day10_1", [](int ac, char **av) { return aoc::day10::main_pt1(ac, av); }});
  day_fn.insert({"day10_2", [](int ac, char **av) { return aoc::day10::main_pt2(ac, av); }});
  day_fn.insert({"day11_1", [](int ac, char **av) { return aoc::day11::main_pt1(ac, av); }});
  day_fn.insert({"day11_2", [](int ac, char **av) { return aoc::day11::main_pt2(ac, av); }});
  day_fn.insert({"day12_1", [](int ac, char **av) { return aoc::day12::main_pt1(ac, av); }});
  day_fn.insert({"day12_2", [](int ac, char **av) { return aoc::day12::main_pt2(ac, av); }});
  day_fn.insert({"day13_1", [](int ac, char **av) { return aoc::day13::main_pt1(ac, av); }});
  day_fn.insert({"day13_2", [](int ac, char **av) { return aoc::day13::main_pt2(ac, av); }});
  day_fn.insert({"day14_1", [](int ac, char **av) { return aoc::day14::main_pt1(ac, av); }});
  day_fn.insert({"day14_2", [](int ac, char **av) { return aoc::day14::main_pt2(ac, av); }});
  day_fn.insert({"day15_1", [](int ac, char **av) { return aoc::day15::main_pt1(ac, av); }});
  day_fn.insert({"day15_2", [](int ac, char **av) { return aoc::day15::main_pt2(ac, av); }});
  // day_fn.insert({"day16_1", [](int ac, char **av) { return aoc::day16::main_pt1(ac, av); }});
  // day_fn.insert({"day16_2", [](int ac, char **av) { return aoc::day16::main_pt2(ac, av); }});
  // day_fn.insert({"day17_1", [](int ac, char **av) { return aoc::day17::main_pt1(ac, av); }});
  // day_fn.insert({"day17_2", [](int ac, char **av) { return aoc::day17::main_pt2(ac, av); }});
  // day_fn.insert({"day18_1", [](int ac, char **av) { return aoc::day18::main_pt1(ac, av); }});
  // day_fn.insert({"day18_2", [](int ac, char **av) { return aoc::day18::main_pt2(ac, av); }});
  // day_fn.insert({"day19_1", [](int ac, char **av) { return aoc::day19::main_pt1(ac, av); }});
  // day_fn.insert({"day19_2", [](int ac, char **av) { return aoc::day19::main_pt2(ac, av); }});
  // day_fn.insert({"day20_1", [](int ac, char **av) { return aoc::day20::main_pt1(ac, av); }});
  // day_fn.insert({"day20_2", [](int ac, char **av) { return aoc::day20::main_pt2(ac, av); }});
  // day_fn.insert({"day21_1", [](int ac, char **av) { return aoc::day21::main_pt1(ac, av); }});
  // day_fn.insert({"day21_2", [](int ac, char **av) { return aoc::day21::main_pt2(ac, av); }});
  // day_fn.insert({"day22_1", [](int ac, char **av) { return aoc::day22::main_pt1(ac, av); }});
  // day_fn.insert({"day22_2", [](int ac, char **av) { return aoc::day22::main_pt2(ac, av); }});
  // day_fn.insert({"day23_1", [](int ac, char **av) { return aoc::day23::main_pt1(ac, av); }});
  // day_fn.insert({"day23_2", [](int ac, char **av) { return aoc::day23::main_pt2(ac, av); }});
  // day_fn.insert({"day24_1", [](int ac, char **av) { return aoc::day24::main_pt1(ac, av); }});
  // day_fn.insert({"day24_2", [](int ac, char **av) { return aoc::day24::main_pt2(ac, av); }});
  // day_fn.insert({"day25_1", [](int ac, char **av) { return aoc::day25::main_pt1(ac, av); }});
  // day_fn.insert({"day25_2", [](int ac, char **av) { return aoc::day25::main_pt2(ac, av); }});

  auto app = fs::path(argv[0]).filename().string();
  if (auto fn = day_fn[app])
  {
    std::cout << "Advent of code " << app << "\n";
    return fn(argc, argv);
  }
  std::cerr << "Invalid applet \"" << app << "\"...\n";
  return 1;
}
