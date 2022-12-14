#include "day11/day11.hpp"

#include <iostream>

namespace aoc::day11 {

static auto participants = MonkeyGame::Participants_t{
    // Monkey 0:
    //   Starting items: 73, 77
    //   Operation: new = old * 5
    //   Test: divisible by 11
    //     If true: throw to monkey 6
    //     If false: throw to monkey 5
    {0, {73, 77}, Operation::mul, 5, Monkey::test_t{11, 6, 5}},
    // Monkey 1:
    //   Starting items: 57, 88, 80
    //   Operation: new = old + 5
    //   Test: divisible by 19
    //     If true: throw to monkey 6
    //     If false: throw to monkey 0
    {1, {57, 88, 80}, Operation::add, 5, Monkey::test_t{19, 6, 0}},
    // Monkey 2:
    //   Starting items: 61, 81, 84, 69, 77, 88
    //   Operation: new = old * 19
    //   Test: divisible by 5
    //     If true: throw to monkey 3
    //     If false: throw to monkey 1
    {2, {61, 81, 84, 69, 77, 88}, Operation::mul, 19, Monkey::test_t{5, 3, 1}},
    // Monkey 3:
    //   Starting items: 78, 89, 71, 60, 81, 84, 87, 75
    //   Operation: new = old + 7
    //   Test: divisible by 3
    //     If true: throw to monkey 1
    //     If false: throw to monkey 0
    {3, {78, 89, 71, 60, 81, 84, 87, 75}, Operation::add, 7, Monkey::test_t{3, 1, 0}},
    // Monkey 4:
    //   Starting items: 60, 76, 90, 63, 86, 87, 89
    //   Operation: new = old + 2
    //   Test: divisible by 13
    //     If true: throw to monkey 2
    //     If false: throw to monkey 7
    {4, {60, 76, 90, 63, 86, 87, 89}, Operation::add, 2, Monkey::test_t{13, 2, 7}},
    // Monkey 5:
    //   Starting items: 88
    //   Operation: new = old + 1
    //   Test: divisible by 17
    //     If true: throw to monkey 4
    //     If false: throw to monkey 7
    {5, {88}, Operation::add, 1, Monkey::test_t{17, 4, 7}},
    // Monkey 6:
    //   Starting items: 84, 98, 78, 85
    //   Operation: new = old * old
    //   Test: divisible by 7
    //     If true: throw to monkey 5
    //     If false: throw to monkey 4
    {6, {84, 98, 78, 85}, Operation::mul, std::nullopt, Monkey::test_t{7, 5, 4}}, 
    // Monkey 7:
    //   Starting items: 98, 89, 78, 73, 71
    //   Operation: new = old + 4
    //   Test: divisible by 2
    //     If true: throw to monkey 3
    //     If false: throw to monkey 2
    {7, {98, 89, 78, 73, 71}, Operation::add, 4, Monkey::test_t{2, 3, 2}}};

auto main_pt1(int argc, char **argv) -> int { 
    MonkeyGame{participants}.play(20).print_result(std::cout);
    return 0; 
}

auto main_pt2(int argc, char **argv) -> int { return 0; }
}  // namespace aoc::day11
