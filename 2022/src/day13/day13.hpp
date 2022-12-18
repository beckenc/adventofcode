#pragma once
#include <iostream>
#include <list>
#include <memory>
#include <optional>
#include <string>
#include <tuple>
#include <variant>

namespace aoc::day13 {

struct PacketPair {
  std::pair<std::string, std::string> lists;
};

struct ListNode;
struct List {
  typedef std::list<ListNode> type;
  type list;

  auto extract(std::string_view sv) -> std::string_view;
  auto compare(List lhs) -> int;
};

struct ListNode {
  typedef std::variant<std::monostate, int, List> value_type;

  ListNode() = default;
  ListNode(int i) : _elem{i} {}
  ListNode(List&& list) : _elem{list} {}

  auto is_list() const { return std::holds_alternative<List>(_elem); };
  auto is_int() const { return std::holds_alternative<int>(_elem); };
  auto& child() { return std::get<List>(_elem); }

  operator int() const { return std::get<int>(_elem); }

  operator List() const {
    if (is_list()) {
      return std::get<List>(_elem);
    }
    auto node = ListNode{List{}};
    node.child().list.emplace_back(std::get<int>(_elem));
    auto list = List{};
    list.list.emplace_back(std::move(node));
    return list;
  }

 private:
  value_type _elem;
};

std::istream& operator>>(std::istream& is, PacketPair& pp);

auto main_pt1(int argc, char** argv) -> int;
auto main_pt2(int argc, char** argv) -> int;
}  // namespace aoc::day13
