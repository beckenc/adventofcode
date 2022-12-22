add_executable(
  day20.test
  day20.test.cpp
)
target_link_libraries(
  day20.test
  day20
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(day20.test)
