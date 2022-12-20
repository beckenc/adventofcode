add_executable(
  day15.test
  day15.test.cpp
)
target_link_libraries(
  day15.test
  day15
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(day15.test)
