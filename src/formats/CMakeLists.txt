
add_library(Formats INTERFACE
  bin.cpp
  bin.hpp 
)

target_include_directories(Formats INTERFACE ${CMAKE_SOURCE_DIRECTORY}/src)

set_target_properties(Formats PROPERTIES INTERFACE_LINK_LIBRARIES stdc++fs)

