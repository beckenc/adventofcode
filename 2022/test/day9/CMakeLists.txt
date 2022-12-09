add_executable(
  day9.test
  day9.test.cpp
)
target_link_libraries(
  day9.test
  day9
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(day9.test)
