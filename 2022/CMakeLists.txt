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
  day5
  day6
  day7
  day8
  day9
  day10
  day11
  day12
  day13
  day14
  day15
  # day16
  # day17
  # day18
  # day19
  day20
  day21
  # day22
  # day23
  # day24
  # day25
  pthread
)

foreach(day RANGE 1 25 1)
  add_custom_command(TARGET aoc POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E create_symlink "aoc" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/day${day}_1"
    COMMAND ${CMAKE_COMMAND} -E create_symlink "aoc" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/day${day}_2"    
    MAIN_DEPENDENCY aoc
  )    
endforeach()