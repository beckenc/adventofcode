#pragma once
#include <array>
#include <iostream>
#include <iterator>
#include <ranges>
#include <sstream>
#include <string>

namespace aoc::day3 {

class Rucksack {
 public:
  typedef std::string Compartment;
  Rucksack() = default;
  explicit Rucksack(Compartment&& comp1, Compartment&& comp2);

  auto get_shared_item() const -> std::tuple<char, unsigned>;

 private:
  std::array<Compartment, 2> _compartment;
  char _shared_item = '\0';
};

inline std::istream& operator>>(std::istream& is, Rucksack& rs) {
  auto supply = std::string{};
  is >> supply;
  if (!supply.empty())
    rs = Rucksack{supply.substr(0, supply.length() / 2),
                  supply.substr(supply.length() / 2)};
  return is;
}

auto main_pt1(int argc, char** argv) -> int;
auto main_pt2(int argc, char** argv) -> int;
}  // namespace aoc::day3