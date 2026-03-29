
add_library(Data 
  data.cpp 
)

target_include_directories(Data PUBLIC
  ${CMAKE_SOURCE_DIRECTORY}/src
  ${CMAKE_SOURCE_DIRECTORY}/src/data
)

set_target_properties(Data PROPERTIES 
  CMAKE_CXX_STANDARD 20
)
