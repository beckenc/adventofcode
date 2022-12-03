add_executable(
  day4.test
  day4.test.cpp
)
target_link_libraries(
  day4.test
  day4
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(day4.test)
