set(ENGINE_SRC ${CORE_SRC}/engine)

add_library(Engine INTERFACE)

target_include_directories(Engine INTERFACE
  ${ENGINE_SRC}
  ${PROJECT_ROOT}
)
