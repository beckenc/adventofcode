#include "day3/day3.hpp"

namespace aoc::day3 {

Rucksack::Rucksack(Compartment &&comp1, Compartment &&comp2)
    : _compartment{comp1, comp2} {
  auto pos = std::all_of(
      _compartment[0].begin(), _compartment[0].end(), [this](const char &c) {
        if (auto pos = _compartment[1].find(c); pos == std::string::npos) {
          return true;  // keep on searching
        } else {
          _shared_item = _compartment[1][pos];
          return false;
        }
      });
};

auto Rucksack::get_shared_item() const -> std::tuple<char, unsigned> {
  auto dec = static_cast<unsigned>(_shared_item);
  return std::make_tuple(_shared_item,
                         std::islower(_shared_item) ? dec - 96 : dec - 38);
}

auto main_pt1(int argc, char **argv) -> int {
  auto overall_prio = 0;
  for (auto rucksaecke = std::ranges::istream_view<Rucksack>(std::cin);
       const auto &rucksack : rucksaecke) {
    auto [shared, prio] = rucksack.get_shared_item();
    overall_prio += prio;
  }

  return 0;
}

auto main_pt2(int argc, char **argv) -> int { return 0; }
}  // namespace aoc::day3