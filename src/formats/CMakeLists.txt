
message("-- Entering Formats --")

add_library(Formats
  bin.cpp
)

target_include_directories(Formats PUBLIC 
  ${CMAKE_SOURCE_DIRECTORY}/src
  ${CMAKE_SOURCE_DIRECTORY}/src/formats
)

set_target_properties(Formats PROPERTIES 
  CMAKE_CXX_STANDARD 20
) 

