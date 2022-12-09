#include "day9/day9.hpp"

#include <iostream>
#include <sstream>
#include <vector>

#include "gtest/gtest.h"

namespace aoc::day9 {

TEST(SimpleTestPt1, day9) {
  auto input = std::vector<std::string>{"R 4", "U 4", "L 3", "D 1",
                                        "R 4", "D 1", "L 5", "R 2"};

  auto motions = Motions{};
  for (auto in : input) {
    auto motion = Motion{};
    std::stringstream{in} >> motion;
    motions.append(std::move(motion));
  }

  std::cout << motions << std::endl;

  Head head;
  Tail tail;
  Grid head_places;
  Grid tail_places;
  std::ranges::for_each(
      motions.get(), [&head, &tail, &head_places, &tail_places](Motion motion) {
        for (auto num_steps = 0; num_steps < motion.num_steps(); ++num_steps) {
          head.move(Motion::motion_t{motion.direction(), 1});
          head_places.visit(head.pos());

          tail.follow(head);
          tail_places.visit(tail.pos());
        }
      });
  EXPECT_EQ(tail_places.visited_fields(), 13);
  std::cout << "tail:\n" << tail_places << std::endl;  
}

TEST(SimpleTestPt2, day9) {}

}  // namespace aoc::day9