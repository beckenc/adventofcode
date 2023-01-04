#include <filesystem>
#include <functional>
#include <iostream>
#include <map>
#include <string_view>

#include "day1/day1.hpp"
#include "day2/day2.hpp"

namespace fs = std::filesystem;

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) {
  std::map<std::string_view, std::function<int(int, char **)> > day_fn;
  day_fn.insert({"day1", [](int ac, char **av) { return aoc::day1::main(ac, av); }});
  day_fn.insert({"day2", [](int ac, char **av) { return aoc::day1::main(ac, av); }});

  auto app = fs::path(argv[0]).filename().string();
  if (auto fn = day_fn[app]) return fn(argc, argv);
  std::cerr << "Invalid applet \"" << app << "\"...\n";
  return 1;
}
