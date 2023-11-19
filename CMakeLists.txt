cmake_minimum_required(VERSION 3.23.5)

project(GatorLibrary VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add your source and header files to the project
add_executable(gatorLibrary
    main.cpp
    book.cpp
    reservation.cpp
    redblack_tree.cpp
    gator_library.cpp
    gl_input.cpp
)

target_include_directories(gatorLibrary PRIVATE gatorLibrary)