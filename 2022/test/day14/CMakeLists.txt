add_executable(
  day14.test
  day14.test.cpp
)
target_link_libraries(
  day14.test
  day14
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(day14.test)
