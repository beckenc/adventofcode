add_executable(
  day1.test
  day1.test.cpp
)
target_link_libraries(
  day1.test
  day1
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(day1.test WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
