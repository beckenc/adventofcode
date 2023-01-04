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
  int _maxRegX{1};
  int _minRegX{1};

  auto load_programm(prog_t&& prog) {
    _prog = std::forward<prog_t>(prog);
    _regX = 1;
    _cycle = 0;
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
    auto param = [this]() { return _prog[_pc]._param; };

    if (--_inst_cycle == 0) {
      _regX += param().value_or(0);
      if (_regX > _maxRegX) _maxRegX = _regX;
      if (_regX < _minRegX) _minRegX = _regX;
      load();
    }

    _cycle++;
    return *this;
  }

 private:
  unsigned _pc{0};
  unsigned _inst_cycle{0};
};

struct CRT {
  signed width = 40;

  explicit CRT(std::ostream& os) : _os{os} {};

  auto load_programm(CPU::prog_t&& prog) {
    _cycle = 0;
    _cpu.load_programm(std::forward<CPU::prog_t>(prog));
  }

  auto eop() const { return _cpu.eop(); }

  auto update_screen() {
    auto sprite_min = _cpu._regX - 1;
    auto sprite_max = _cpu._regX - 1 + 2;
    auto col = _cycle % width;
    if (!col) _os << "\n";
    auto pixel = ((col >= sprite_min) && (col <= sprite_max)) ? "#" : ".";
    _os << pixel;
  }

  CRT& operator++() {
    update_screen();
    ++_cycle;
    ++_cpu;
    return *this;
  }

 private:
  CPU _cpu;
  std::ostream& _os;
  signed _cycle{0};
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

auto main_pt1([[maybe_unused]] int argc, [[maybe_unused]] char **argv) -> int;
auto main_pt2([[maybe_unused]] int argc, [[maybe_unused]] char **argv) -> int;
}  // namespace aoc::day10
