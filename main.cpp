#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

#include "gator_library.hpp"

#include "gl_input.cpp"

using namespace std;

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
