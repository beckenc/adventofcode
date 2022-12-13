add_executable(
  day10.test
  day10.test.cpp
)
target_link_libraries(
  day10.test
  day10
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(day10.test)
