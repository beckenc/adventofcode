add_executable(
  day3.test
  day3.test.cpp
)
target_link_libraries(
  day3.test
  day3
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(day3.test)
