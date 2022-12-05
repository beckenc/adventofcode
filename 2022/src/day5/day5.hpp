#pragma once
#include <istream>
#include <list>
#include <tuple>
#include <vector>

namespace aoc::day5 {

struct Rearrangement {
  std::tuple<unsigned, unsigned, unsigned> _rule;
};

class CrateStacks {
 public:
  typedef std::list<char> CrateStack;
  CrateStacks() = default;
  explicit CrateStacks(std::istream& is);
  auto stacks() const { return _stacks; }
  void rearrange(Rearrangement&& rearrangement);
  void print_stacks() const;

 private:
  std::vector<CrateStack> _stacks;
};

inline std::istream& operator>>(std::istream& is, CrateStacks& rs) {
  rs = CrateStacks{is};
  return is;
}

inline std::istream& operator>>(std::istream& is, Rearrangement& rs) {
  auto devnull = std::string{};
  auto& [what, from, to] = rs._rule;
  is >> devnull >> what >> devnull >> from >> devnull >> to;
  from--;
  to--;
  return is;
}

auto main_pt1(int argc, char** argv) -> int;
auto main_pt2(int argc, char** argv) -> int;
}  // namespace aoc::day5
