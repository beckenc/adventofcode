add_executable(
  day21.test
  day21.test.cpp
)
target_link_libraries(
  day21.test
  day21
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(day21.test)
