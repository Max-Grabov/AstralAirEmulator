add_library(Base INTERFACE)

add_library(AudioBase INTERFACE)

add_library(FormatsBase INTERFACE)

add_library(ImageBase INTERFACE)

#Fetch content later
target_link_libraries(Base INTERFACE gtest gtest_main)

target_link_libraries(AudioBase INTERFACE Audio Base)

target_link_libraries(FormatsBase INTERFACE Formats Base)

target_link_libraries(ImageBase INTERFACE Image Base)

add_executable(audio_tests audio_tests.cpp)

add_executable(file_view_tests file_view_tests.cpp)

add_executable(bin_tests bin_tests.cpp)

add_executable(utility_tests utility_tests.cpp)

add_executable(image_tests image_tests.cpp)

target_link_libraries(audio_tests PUBLIC AudioBase FormatsBase)

target_link_libraries(file_view_tests PUBLIC FormatsBase)

target_link_libraries(bin_tests PUBLIC FormatsBase)

target_link_libraries(utility_tests PUBLIC Base)

target_link_libraries(image_tests PUBLIC FormatsBase ImageBase)

target_include_directories(
  utility_tests PUBLIC
    "${CMAKE_SOURCE_DIR}/src/util"
)

set_target_properties(
  audio_tests PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY
    "${CMAKE_BINARY_DIR}/tests/audio"
)

set_target_properties(
  image_tests PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY
    "${CMAKE_BINARY_DIR}/tests/image"
)

set_target_properties(
  file_view_tests PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY
    "${CMAKE_BINARY_DIR}/tests/formats"
)

set_target_properties(
  bin_tests PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY
    "${CMAKE_BINARY_DIR}/tests/formats"
)

set_target_properties(
  utility_tests PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY
    "${CMAKE_BINARY_DIR}/tests/util"
)
