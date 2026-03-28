
add_executable(file_view_tests file_view_tests.cpp)

target_link_libraries(file_view_tests PUBLIC 
  Formats
  # Find Package shit
  gtest
  gtest_main
)

target_include_directories(file_view_tests PUBLIC
  ${CMAKE_SOURCE_DIRECTORY}/src/formats
)

set_target_properties(file_view_tests PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/tests/formats"
)

