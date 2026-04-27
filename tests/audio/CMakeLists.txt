
add_library(AudioBase INTERFACE)

target_link_libraries(AudioBase INTERFACE
  Audio
  # Find Package shit
  gtest
  gtest_main
)

target_include_directories(AudioBase INTERFACE
  ${CMAKE_SOURCE_DIRECTORY}/src/audio
)

add_executable(decoder_tests decoder_tests.cpp)

target_link_libraries(decoder_tests PUBLIC 
  AudioBase 
)

set_target_properties(decoder_tests PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/tests/audio"
)

