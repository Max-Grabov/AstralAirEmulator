
add_library(Data INTERFACE
  data.hpp 
)

set_target_properties(Data PROPERTIES INTERFACE_LINK_LIBRARIES stdc++fs)
