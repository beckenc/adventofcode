#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <ranges>
#include <utility>

auto count_increasing(std::istream &input) {
  return std::ranges::count_if(
      std::ranges::istream_view<unsigned>(input),
      [prev = std::numeric_limits<unsigned>::max()](unsigned curr) mutable {
        return std::exchange(prev, curr) < curr;
      });
}

auto day1(int argc, char **argv) {
  std::cout << "Advent of code day1\n";
  std::cout << "The measured depth increased in " << count_increasing(std::cin)
            << " cases.\n";
  return 0;
}
