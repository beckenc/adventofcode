add_executable(
  day2.test
  day2.test.cpp
)
target_link_libraries(
  day2.test
  day1
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(day2.test)
