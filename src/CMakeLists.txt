# Compile sources as library
add_library(turinglib)

add_subdirectory(data)
add_subdirectory(core)
add_subdirectory(state)
add_subdirectory(utils)

target_include_directories(
  turinglib
  PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries(turinglib coverage_config)

# Generate executable
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} turinglib)
