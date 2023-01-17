#include "utils.hpp"

namespace aoc::utils {

std::istream& operator>>(std::istream& is, Coordinates& point) {
  auto x = int{};
  auto y = int{};
  auto c = char{};
  is >> x >> c >> y;
  point = Coordinates{{x, y}};
  return is;
}
}  // namespace aoc::utils