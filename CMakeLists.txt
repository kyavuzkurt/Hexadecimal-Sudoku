cmake_minimum_required(VERSION 3.10)
project(HexSudoku)

set(CMAKE_CXX_STANDARD 17)


find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Include directories
include_directories(include)

# Source files
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Executable
add_executable(HexSudoku ${SOURCES})


target_link_libraries(HexSudoku 
    sfml-graphics 
    sfml-window 
    sfml-system 
)


add_custom_command(TARGET HexSudoku POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/resources ${CMAKE_BINARY_DIR}/resources
)
