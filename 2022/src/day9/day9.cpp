#include "day9/day9.hpp"

#include <iostream>
#include <ranges>

namespace aoc::day9 {

void Knot::follow(Knot head) {
  auto [hx, hy] = head.pos().get();
  auto [tx, ty] = _pos.get();

  if (!((abs(hy - ty) > 1) || (abs(hx - tx) > 1))) {
    return;  // keep position
  }

  if (hy == ty) {
    if (hx > tx) {
      _pos = {hx - 1, hy};  // follow right
    } else if (hx < tx) {
      _pos = {hx + 1, hy};  // follow left
    } else {
      throw std::runtime_error("missing case");
    }

  } else if (hx == tx) {
    if (hy > ty) {
      _pos = {hx, hy - 1};  // follow up
    } else if (hy < ty) {
      _pos = {hx, hy + 1};  // follow down
    } else {
      throw std::runtime_error("missing case");
    }

  } else if (hy > (ty + 1)) {
    _pos = {hx, hy - 1};  // follow up     ....H.
                          //               ....x.
                          //               ...T.T
  } else if (hy < (ty - 1)) {
    _pos = {hx, hy + 1};  // follow down   ..T.T.
                          //               ...x..
                          //               ...H..
  } else if (hx < (tx - 1)) {
    _pos = {hx + 1, hy};  // follow left   ....T.
                          //               ..Hx..
                          //               ....T.
  } else if (hx > (tx + 1)) {
    _pos = {hx - 1, hy};  // follow right  ..T...
                          //               ...xH.
                          //               ..T...
  } else {
    throw std::runtime_error("missing case");
  }
}

auto main_pt1(int argc, char **argv) -> int {
  Motions motions;
  std::ranges::for_each(std::ranges::istream_view<Motion>(std::cin),
                        [&motions](auto &&motion) {
                          motions.append(std::forward<Motion>(motion));
                        });
  std::cout << motions << std::endl;

  Grid tail_places;
  std::ranges::for_each(motions.get(), [head = Knot{}, tail = Knot{},
                                        &tail_places](Motion motion) mutable {
    for (auto num_steps = 0; num_steps < motion.num_steps(); ++num_steps) {
      head.move(Motion::motion_t{motion.direction(), 1});
      tail.follow(head);
      tail_places.visit(tail.pos());
    }
  });
  // std::cout << "tail:\n" << tail_places << std::endl;
  std::cout << "Part1:" << tail_places.visited_fields() << std::endl;

  return 0;
}

auto main_pt2(int argc, char **argv) -> int {
  Motions motions;
  std::ranges::for_each(std::ranges::istream_view<Motion>(std::cin),
                        [&motions](auto &&motion) {
                          motions.append(std::forward<Motion>(motion));
                        });
  std::cout << motions << std::endl;

  Grid tail_places;
  std::ranges::for_each(
      motions.get(), [head = Knot{}, knots = std::vector<Knot>{9},
                      &tail_places](Motion motion) mutable {
        for (auto num_steps = 0; num_steps < motion.num_steps(); ++num_steps) {
          head.move(Motion::motion_t{motion.direction(), 1});

          auto tail = head;
          for(auto& knot : knots)
          {
            knot.follow(tail);
            tail = knot;
          }

          tail_places.visit(tail.pos());
        }
      });
  // std::cout << "tail:\n" << tail_places << std::endl;
  std::cout << "Part2:" << tail_places.visited_fields() << std::endl;

  return 0;
}
}  // namespace aoc::day9
