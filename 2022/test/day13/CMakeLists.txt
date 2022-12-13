add_executable(
  day13.test
  day13.test.cpp
)
target_link_libraries(
  day13.test
  day13
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(day13.test)
