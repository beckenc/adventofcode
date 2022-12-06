add_executable(
  day6.test
  day6.test.cpp
)
target_link_libraries(
  day6.test
  day6
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(day6.test)
