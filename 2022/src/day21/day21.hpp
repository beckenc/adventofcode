#pragma once
#include <functional>
#include <iostream>
#include <map>
#include <optional>
#include <string>
#include <variant>

namespace aoc::day21 {

class Monkey;
typedef std::map<std::string, Monkey> Monkeys;

class Monkey {
 public:
  struct ArithmeticOp {
    typedef std::function<int64_t(int64_t, int64_t)> type_t;
    std::pair<std::string, std::string> _param;
    type_t _op;
    auto operator()(auto&& monkeys) const {
      auto lhs = monkeys[_param.first];
      auto rhs = monkeys[_param.second];
      return _op(lhs(std::forward<decltype(monkeys)>(monkeys)),
                 rhs(std::forward<decltype(monkeys)>(monkeys)));
    }
  };
  typedef std::variant<int64_t, ArithmeticOp> op_type;

  Monkey() = default;
  Monkey(auto&& name, auto&& op)
      : _name{std::forward<std::string>(name)},
        _op{std::forward<op_type>(op)} {}

  auto name() const { return _name; }
  auto fix_arithmetic(int64_t value) { _op = value; }
  auto fix_arithmetic(ArithmeticOp::type_t op) {
    std::get<ArithmeticOp>(_op)._op = op;
  }

  auto operator()(auto&& monkeys) const {
    return std::visit(
        [&monkeys](auto&& op) {
          using T = std::decay_t<decltype(op)>;
          if constexpr (std::is_same_v<T, int64_t>) {
            return op;
          } else if constexpr (std::is_same_v<T, ArithmeticOp>) {
            return op(std::forward<decltype(monkeys)>(monkeys));
          }
        },
        _op);
  }

 private:
  std::string _name;
  op_type _op;
};

inline auto operator>>(std::istream& is, Monkey& monkey) -> std::istream& {
  auto name = std::string{};
  auto tmp = std::string{};
  auto lhs = std::string{};
  auto op = char{};
  auto rhs = std::string{};

  is >> name >> lhs;
  if (name.empty()) {
    return is;
  }
  name.erase(4);  // delete :

  if (lhs.find_first_not_of("0123456789") == std::string::npos) {
    auto v = stoi(lhs);
    monkey = Monkey{std::move(name), v};
  } else {
    is >> op >> rhs;
    auto fn = Monkey::ArithmeticOp::type_t{};
    switch (op) {
      case '+':
        fn = std::plus();
        break;
      case '-':
        fn = std::minus();
        break;
      case '*':
        fn = std::multiplies();
        break;
      case '/':
        fn = std::divides();
        break;
      case '%':
        fn = std::modulus();
        break;
    }
    auto arithmetic_op =
        Monkey::ArithmeticOp{._param{std::move(lhs), std::move(rhs)}, ._op{fn}};
    monkey = Monkey{std::move(name), std::move(arithmetic_op)};
  }

  return is;
}

auto main_pt1([[maybe_unused]] int argc, [[maybe_unused]] char **argv) -> int;
auto main_pt2([[maybe_unused]] int argc, [[maybe_unused]] char **argv) -> int;
}  // namespace aoc::day21
