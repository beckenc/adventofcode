#pragma once
#include <array>
#include <iostream>
#include <iterator>
#include <ranges>
#include <sstream>
#include <string>

namespace aoc::day3 {

inline auto calc_item_prio(char c) {
  auto dec = static_cast<unsigned>(c);
  return std::make_tuple(c, std::islower(c) ? dec - 96 : dec - 38);
}

class Rucksack {
 public:
  typedef std::string Compartment;
  Rucksack() = default;
  explicit Rucksack(std::istream& is);
  explicit Rucksack(Compartment&& comp1, Compartment&& comp2);

  auto get_shared_item() const { return calc_item_prio(_shared_item); }
  auto get_supplies() const { return _compartment[0] + _compartment[1]; }

 private:
  std::array<Compartment, 2> _compartment;
  char _shared_item = '\0';
};

class ElfGroup {
 public:
  typedef std::array<Rucksack, 3> Rucksacks;
  ElfGroup() = default;
  ElfGroup(Rucksacks&& rs);

  auto get_badge_item() const { return calc_item_prio(_badge); }

 private:
  Rucksacks _rucksacks;
  char _badge = '\0';
};

inline std::istream& operator>>(std::istream& is, Rucksack& rs) {
  rs = Rucksack{is};
  return is;
}

inline std::istream& operator>>(std::istream& is, ElfGroup& eg) {
  auto rucksacks = ElfGroup::Rucksacks{};
  std::for_each(rucksacks.begin(), rucksacks.end(),
                [&is](Rucksack& rs) { rs = Rucksack{is}; });
  eg = ElfGroup{std::move(rucksacks)};
  return is;
}

auto main_pt1([[maybe_unused]] int argc, [[maybe_unused]] char **argv) -> int;
auto main_pt2([[maybe_unused]] int argc, [[maybe_unused]] char **argv) -> int;
}  // namespace aoc::day3