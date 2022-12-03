#include "day3/day3.hpp"

namespace aoc::day3 {

Rucksack::Rucksack(Compartment &&comp1, Compartment &&comp2)
    : _compartment{comp1, comp2} {
  std::all_of(
      _compartment[0].begin(), _compartment[0].end(), [this](const char &c) {
        if (auto pos = _compartment[1].find(c); pos == std::string::npos) {
          return true;  // keep on searching
        } else {
          _shared_item = _compartment[1][pos];
          return false;
        }
      });
};

ElfGroup::ElfGroup(Rucksacks &&rs) : _rucksacks{rs} {
  auto supply = _rucksacks[0].get_supplies();
  std::for_each(supply.begin(), supply.end(), [this](const char &c) {
    if (auto pos = this->_rucksacks[1].get_supplies().find(c);
        pos != std::string::npos) {
      if (pos = this->_rucksacks[2].get_supplies().find(c);
          pos != std::string::npos) {
        _badge = c;
      }
    }
  });
};

auto main_pt1(int argc, char **argv) -> int {
  auto overall_prio = 0;
  for (auto rucksaecke = std::ranges::istream_view<Rucksack>(std::cin);
       const auto &rucksack : rucksaecke) {
    auto [shared, prio] = rucksack.get_shared_item();
    overall_prio += prio;
  }
  std::cout << "Part1:" << overall_prio << std::endl;
  return 0;
}

auto main_pt2(int argc, char **argv) -> int {
  auto overall_prio = 0;
  for (auto groups = std::ranges::istream_view<ElfGroup>(std::cin);
       auto &group : groups) {
    auto [badge, prio] = group.get_badge_item();
    overall_prio += prio;
  }
  std::cout << "Part2:" << overall_prio << std::endl;
  return 0;
}
}  // namespace aoc::day3