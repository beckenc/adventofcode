add_executable(
  dayX.test
  dayX.test.cpp
)
target_link_libraries(
  dayX.test
  dayX
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(dayX.test)
