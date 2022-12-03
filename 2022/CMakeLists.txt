include_directories(src)

add_subdirectory(src)
if(BUILD_TESTING)
  add_subdirectory(test)
endif()

add_executable(aoc main.cpp)

target_link_libraries(aoc
PRIVATE
  day1
  day2
  day3
  day4
  pthread
)
