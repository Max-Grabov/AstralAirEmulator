
add_library(FormatsBase INTERFACE)

target_link_libraries(FormatsBase INTERFACE
  Formats
  # Find Package shit
  gtest
  gtest_main
)

target_include_directories(FormatsBase INTERFACE
  ${CMAKE_SOURCE_DIRECTORY}/src/formats
)

add_executable(file_view_tests file_view_tests.cpp)

add_executable(bin_tests bin_tests.cpp)

target_link_libraries(file_view_tests PUBLIC 
  FormatsBase 
)

target_link_libraries(bin_tests PUBLIC
  FormatsBase
)

set_target_properties(file_view_tests PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/tests/formats"
)

set_target_properties(bin_tests PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/tests/formats"
)

