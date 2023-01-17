include_directories(src)

add_subdirectory(src)
if(BUILD_TESTING)
  add_subdirectory(test)
endif()

add_executable(aoc main.cpp)

target_link_libraries(aoc
PRIVATE
  utils
  dayX
  pthread
)

foreach(day RANGE 1 25 1)
  add_custom_command(TARGET aoc POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E create_symlink "aoc" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/day${day}_1"
    COMMAND ${CMAKE_COMMAND} -E create_symlink "aoc" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/day${day}_2"
    MAIN_DEPENDENCY aoc
  )
endforeach()
