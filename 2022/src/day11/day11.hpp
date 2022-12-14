#pragma once
#include <algorithm>
#include <iostream>
#include <list>
#include <numeric>
#include <optional>
#include <ranges>
#include <tuple>
#include <vector>

namespace aoc::day11 {

enum class Operation { add, mul };

class Monkey {
 public:
  typedef int monkey_t;
  typedef int divider_t;
  typedef int64_t worry_level_t;
  typedef std::optional<int> operand_t;
  typedef std::tuple<divider_t, monkey_t, monkey_t> test_t;
  typedef std::list<worry_level_t> starting_items_t;

  Monkey(monkey_t monkey, starting_items_t starting_items, Operation op,
         operand_t operand, test_t test)
      : _monkey{monkey},
        _starting_items{starting_items},
        _op{op},
        _operand{operand},
        _test{test},
        _inspections{0} {}

  auto enqueue_worry_level(worry_level_t worry_level) {
    _starting_items.emplace_back(worry_level);
  }

  auto inspect() -> std::optional<worry_level_t> {
    if (_starting_items.empty()) return std::nullopt;
    auto worry_level = _starting_items.front();
    _starting_items.pop_front();
    _inspections++;
    return worry_level;
  }

  auto get_bored(worry_level_t worry_level) { return worry_level /= 3; }

  auto throw_away(worry_level_t worry_level) {
    auto [divider, monkey_true, monkey_false] = _test;
    if (0 == (worry_level % divider)) {
      return monkey_true;
    }
    return monkey_false;
  }

  auto operation(worry_level_t worry_level) {
    if (_op == Operation::add) {
      worry_level += _operand.value_or(worry_level);
    } else if (_op == Operation::mul) {
      worry_level *= _operand.value_or(worry_level);
    } else {
      throw std::runtime_error("Invalid operation");
    }
    return worry_level;
  }

  auto its_me(monkey_t monkey) const { return _monkey == monkey; }
  auto num_inspections() const { return _inspections; }
  auto id() const { return _monkey; }
  auto divider() const { return std::get<0>(_test); }

 private:
  monkey_t _monkey;
  starting_items_t _starting_items;
  Operation _op;
  operand_t _operand;
  test_t _test;
  uint64_t _inspections;
};

class MonkeyGame {
 public:
  typedef std::vector<Monkey> Participants_t;

  MonkeyGame(Participants_t participants) : _participants{participants} {}

  auto lcm() -> uint64_t {
    auto lcm = 1;
    auto do_lcm = [&lcm](auto& monkey) {
      lcm = std::lcm(lcm, monkey.divider());
    };
    std::ranges::for_each(_participants, do_lcm);
    return lcm;
  }

  auto play_game1(auto rounds) {
    for (auto i : std::views::iota(0, rounds)) {
      play_game1();
    }
    return *this;
  }

  auto play_game2(auto rounds) {
    for (auto i : std::views::iota(0, rounds)) {
      play_game2();
    }
    return *this;
  }

  auto print_result(std::ostream& os) {
    std::ranges::for_each(_participants, [&os](auto&& monkey) {
      os << "Monkey " << monkey.id() << " inspected items "
         << monkey.num_inspections() << " times.\n";
    });
  }

 private:
  auto play_game1() {
    std::ranges::for_each(_participants, [this](auto&& monkey) {
      while (auto item = monkey.inspect()) {
        auto worry_level = monkey.operation(*item);
        worry_level = monkey.get_bored(worry_level);
        auto recipient_id = monkey.throw_away(worry_level);
        auto recipient = std::ranges::find_if(
            _participants,
            [recipient_id](auto&& m) { return m.its_me(recipient_id); });
        recipient->enqueue_worry_level(worry_level);
      }
    });
  }
  auto play_game2() {
    std::ranges::for_each(_participants, [this](auto&& monkey) {
      while (auto item = monkey.inspect()) {
        uint64_t worry_level = monkey.operation(*item);
        worry_level %= lcm();
        auto recipient_id = monkey.throw_away(worry_level);
        auto recipient = std::ranges::find_if(
            _participants,
            [recipient_id](auto&& m) { return m.its_me(recipient_id); });
        recipient->enqueue_worry_level(worry_level);
      }
    });
  }

  Participants_t _participants;
};

auto main_pt1(int argc, char** argv) -> int;
auto main_pt2(int argc, char** argv) -> int;
}  // namespace aoc::day11
