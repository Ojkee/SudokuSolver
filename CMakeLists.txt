cmake_minimum_required(VERSION 3.20)
project(sudoku_solver LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(core src/grid.cpp src/solver.cpp)
target_include_directories(core PUBLIC include)
add_subdirectory(src/rules)

add_executable(app src/main.cpp)
target_link_libraries(app PRIVATE core)

enable_testing()
add_subdirectory(tests)

