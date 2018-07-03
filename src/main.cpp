#include <iostream>
#include <set>

#include "core.hpp"

int main(int argc, char * argv[])
{
    try
    {
        Core program("QArt - Drop an image to start.", 700, 700);
        program.execute();
    }
    catch(const char * msg)
    {
        std::cerr << msg << std::endl;
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}