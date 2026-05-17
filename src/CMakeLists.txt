
set(FORMATS_SRC ${CMAKE_CURRENT_SOURCE_DIR}/formats)
set(DATA_SRC ${CMAKE_CURRENT_SOURCE_DIR}/data)
set(AUDIO_SRC ${CMAKE_CURRENT_SOURCE_DIR}/audio)

add_library(Formats
  ${FORMATS_SRC}/bin.cpp
  ${FORMATS_SRC}/file_view.cpp
)

add_library(Audio
  ${AUDIO_SRC}/decoder.cpp
)

target_include_directories(Formats PUBLIC  
  ${FORMATS_SRC} 
  ${DATA_SRC}
)

target_include_directories(Audio PUBLIC
  ${AUDIO_SRC}
)

# We fetch content so users don't have to worry about installing vorbis library
include(FetchContent)

FetchContent_Declare(
  vorbis
  GIT_REPOSITORY https://github.com/xiph/vorbis.git
  GIT_TAG v1.3.7
)

FetchContent_MakeAvailable(vorbis)

target_link_libraries(Audio PRIVATE vorbis)

