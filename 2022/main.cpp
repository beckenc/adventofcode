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
  day_fn.insert({"day6_2", [](int ac, char **av) { return aoc::day5::main_pt2(ac, av); }});

  auto app = fs::path(argv[0]).filename().string();
  if (auto fn = day_fn[app])
  {
    std::cout << "Advent of code " << app << "\n";
    return fn(argc, argv);
  }
  std::cerr << "Invalid applet \"" << app << "\"...\n";
  return 1;
}
