add_executable(
  day7.test
  day7.test.cpp
)
target_link_libraries(
  day7.test
  day7
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(day7.test)
