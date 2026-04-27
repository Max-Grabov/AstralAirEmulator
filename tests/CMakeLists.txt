add_library(Base INTERFACE)

add_library(AudioBase INTERFACE)

add_library(FormatsBase INTERFACE)

# Fetch content later
target_link_libraries(Base INTERFACE
  gtest
  gtest_main
)

target_link_libraries(AudioBase INTERFACE
  Audio
  Base
)

target_link_libraries(FormatsBase INTERFACE
  Formats
  Base
)

target_include_directories(AudioBase INTERFACE
  ${CMAKE_SOURCE_DIRECTORY}/src/audio
)

target_include_directories(FormatsBase INTERFACE
  ${CMAKE_SOURCE_DIRECTORY}/src/formats
)

add_executable(decoder_tests decoder_tests.cpp)

add_executable(file_view_tests file_view_tests.cpp)

add_executable(bin_tests bin_tests.cpp)

target_link_libraries(decoder_tests PUBLIC 
  AudioBase 
  FormatsBase
)

target_link_libraries(file_view_tests PUBLIC 
  FormatsBase 
)

target_link_libraries(bin_tests PUBLIC
  FormatsBase
)

set_target_properties(decoder_tests PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/tests/audio"
)

set_target_properties(file_view_tests PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/tests/formats"
)

set_target_properties(bin_tests PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/tests/formats"
)

