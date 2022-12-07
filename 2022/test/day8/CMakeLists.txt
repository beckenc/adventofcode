add_executable(
  day8.test
  day8.test.cpp
)
target_link_libraries(
  day8.test
  day8
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(day8.test)
