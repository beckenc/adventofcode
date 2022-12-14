#pragma once
#include <iostream>
#include <istream>
#include <optional>
#include <vector>

namespace aoc::day10 {

enum class Command : unsigned { invalid = 0, noop = 1, addx = 2 };

struct Instruction {
  Command _command;
  std::optional<int> _param{};
};

struct CPU {
  typedef std::vector<Instruction> prog_t;

  unsigned _cycle{0};
  int _regX{1};
  prog_t _prog{};

  auto load_programm(prog_t&& prog) {
    _prog = std::forward<prog_t>(prog);
    _pc = 0;
    _inst_cycle = static_cast<unsigned>(_prog[_pc]._command);
  }

  auto eop() const {
    auto size = std::size(_prog);
    return _pc == size;
  }

  CPU& operator++() {
    auto load = [this]() {
      _pc++;
      _inst_cycle = static_cast<unsigned>(_prog[_pc]._command);
    };
    auto command = [this]() { return _prog[_pc]._command; };
    auto param = [this]() { return _prog[_pc]._param; };

    if (--_inst_cycle == 0) {
      _regX += param().value_or(0);
      load();
    }

    _cycle++;
    return *this;
  }

 private:
  unsigned _pc{0};
  unsigned _inst_cycle{0};
};

inline std::istream& operator>>(std::istream& is, Command& command) {
  std::string tmp;
  is >> tmp;
  if (tmp == "addx")
    command = Command::addx;
  else if (tmp == "noop")
    command = Command::noop;
  else if (tmp.empty())
    command = Command::invalid;
  else
    throw std::runtime_error("Invalid Instruciton " + tmp);
  return is;
}

inline std::istream& operator>>(std::istream& is, Instruction& instruction) {
  is >> instruction._command;
  if (instruction._command == Command::addx)
    is >> instruction._param.emplace();
  else
    instruction._param = std::nullopt;
  return is;
}

auto main_pt1(int argc, char** argv) -> int;
auto main_pt2(int argc, char** argv) -> int;
}  // namespace aoc::day10
