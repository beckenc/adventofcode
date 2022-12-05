add_executable(
  day5.test
  day5.test.cpp
)
target_link_libraries(
  day5.test
  day5
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(day5.test)
