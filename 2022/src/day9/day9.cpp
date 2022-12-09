#include "day9/day9.hpp"

#include <iostream>
#include <ranges>

namespace aoc::day9 {

auto main_pt1(int argc, char **argv) -> int {
  Motions motions;
  std::ranges::for_each(std::ranges::istream_view<Motion>(std::cin),
                        [&motions](auto &&motion) {
                          motions.append(std::forward<Motion>(motion));
                        });
  std::cout << motions << std::endl;

  Grid tail_places;
  std::ranges::for_each(
      motions.get(), [head = Head{}, tail = Tail{}, &tail_places](Motion motion) mutable {
        for (auto num_steps = 0; num_steps < motion.num_steps(); ++num_steps) {
          head.move(Motion::motion_t{motion.direction(), 1});
          tail.follow(head);
          tail_places.visit(tail.pos());
        }
      });
  //std::cout << "tail:\n" << tail_places << std::endl;
  std::cout << "Part1:" << tail_places.visited_fields() << std::endl;
  
  return 0;
}

auto main_pt2(int argc, char **argv) -> int { return 0; }
}  // namespace aoc::day9
