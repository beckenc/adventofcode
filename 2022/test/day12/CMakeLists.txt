add_executable(
  day12.test
  day12.test.cpp
)
target_link_libraries(
  day12.test
  day12
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(day12.test)
