/**
 * @file main.cpp
 * @brief This file contains the main function.
 * 
*/
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

#include "gator_library.hpp"

#include "gl_input.cpp"

using namespace std;

/**
 * @brief The main function.
 * 
 * @param argc The number of command line arguments.
 * @param argv The command line arguments.
 * @return int The exit code.
 */
int main(int argc, char** argv)
{
    gl_input gl;
    if (argc == 1)
    {
        gl.runwith_stdin();
    }
    else
    {
        gl.runwith_file(argv[1]);
    }
    return 0;
}
