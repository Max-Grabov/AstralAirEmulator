
add_library(Formats
  bin.cpp
  file_view.cpp
)

target_include_directories(Formats PUBLIC 
  ${CMAKE_SOURCE_DIRECTORY}/src
  ${CMAKE_SOURCE_DIRECTORY}/src/formats
)

target_link_libraries(Formats PUBLIC 
  Data
)

set_target_properties(Formats PROPERTIES 
  CMAKE_CXX_STANDARD 20
) 

