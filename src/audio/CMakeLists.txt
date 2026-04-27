# We fetch content so users don't have to worry about installing vorbis library
include(FetchContent)

FetchContent_Declare(
  vorbis
  GIT_REPOSITORY https://github.com/xiph/vorbis.git
  GIT_TAG v1.3.7
)

FetchContent_MakeAvailable(vorbis)

add_library(Audio
  decoder.cpp
)

target_include_directories(Audio PUBLIC
  ${CMAKE_SOURCE_DIRECTORY}/src/audio
)

target_link_libraries(Audio PRIVATE vorbis)

set_target_properties(Audio PROPERTIES 
  CMAKE_CXX_STANDARD 20
)
