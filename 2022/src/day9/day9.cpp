#include "day9/day9.hpp"

#include <iostream>
#include <ranges>

namespace aoc::day9 {

void Knot::follow(Knot head) {
  auto [hx, hy] = head.pos().get();
  auto [tx, ty] = _pos.get();

  auto ydiff = hy - ty;
  auto xdiff = hx - tx;

  if (!(abs(ydiff) > 1 || abs(xdiff) > 1)) {
    return;  // keep position
  }

  if (ydiff > 1)  // move up
    ydiff = 1;
  else if (ydiff < -1)  // move down
    ydiff = -1;
  if (xdiff > 1)  // move right
    xdiff = 1;
  else if (xdiff < -1)  // move left
    xdiff = -1;

  _pos = { tx + xdiff, ty + ydiff };
}

auto main_pt1([[maybe_unused]] int argc, [[maybe_unused]] char **argv) -> int {
  Motions motions;
  std::ranges::for_each(std::ranges::istream_view<Motion>(std::cin),
                        [&motions](auto &&motion) {
                          motions.append(std::forward<Motion>(motion));
                        });
  std::cout << motions << std::endl;

  Grid tail_places;
  std::ranges::for_each(motions.get(), [head = Knot{}, tail = Knot{},
                                        &tail_places](Motion motion) mutable {
    for (auto num_steps = 0u; num_steps < motion.num_steps(); ++num_steps) {
      head.move(Motion::motion_t{motion.direction(), 1});
      tail.follow(head);
      tail_places.visit(tail.pos());
    }
  });
  //std::cout << "tail:\n" << tail_places << std::endl;
  std::cout << "Part1:" << tail_places.visited_fields() << std::endl;

  return 0;
}

auto main_pt2([[maybe_unused]] int argc, [[maybe_unused]] char **argv) -> int {
  Motions motions;
  std::ranges::for_each(std::ranges::istream_view<Motion>(std::cin),
                        [&motions](auto &&motion) {
                          motions.append(std::forward<Motion>(motion));
                        });
  std::cout << motions << std::endl;

  Grid tail_places;
  std::ranges::for_each(motions.get(), [knots = std::vector<Knot>{10},
                                        &tail_places](Motion motion) mutable {
    for (auto num_steps = 0u; num_steps < motion.num_steps(); ++num_steps) {
      auto &head = knots.front();
      head.move(Motion::motion_t{motion.direction(), 1});

      auto tail = head;
      for (auto &knot : knots) {
        knot.follow(tail);
        tail = knot;
      }
      tail_places.visit(knots.back().pos());
    }
  });
  // std::cout << "tail:\n" << tail_places << std::endl;
  std::cout << "Part2:" << tail_places.visited_fields() << std::endl;

  return 0;
}
}  // namespace aoc::day9
