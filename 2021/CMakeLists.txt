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
  pthread
)

add_custom_command(TARGET aoc POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E create_symlink "aoc" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/day1"
    COMMAND ${CMAKE_COMMAND} -E create_symlink "aoc" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/day2"    
    MAIN_DEPENDENCY aoc
    COMMENT "Create symlinks for the multicall binary ${PROJECT_NAME}!"
)