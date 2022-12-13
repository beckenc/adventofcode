add_executable(
  day11.test
  day11.test.cpp
)
target_link_libraries(
  day11.test
  day11
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(day11.test)
