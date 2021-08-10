project(C_plusplus)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)

include_directories(.)

add_executable(pegGame main.cpp move.cpp board.cpp space.cpp solution.cpp)
