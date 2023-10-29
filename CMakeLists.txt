cmake_minimum_required(VERSION 3.23.5)

project(GatorLibrary)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add your source and header files to the project
add_executable(GatorLibrary
    main.cpp
    book.cpp
    redblacktree.cpp
    GatorLibrary.cpp
)

target_include_directories(GatorLibrary PRIVATE GatorLibrary)

# Set the project version
project(GatorLibrary VERSION 1.0)
