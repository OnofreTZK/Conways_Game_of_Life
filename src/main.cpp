#include "../include/arguments.h"

#include <cstdlib> //size_t
#include <iostream> // STL general( std:: )
#include <string> // STL string library( file and paths manip )
#include <vector> // STL vector library( initial config board )
#include <cassert>

/*
===============================
Conway's Life Game Simulator  |
===============================
Authors:
Tiago Onofre and Rafael Fortunato.
*/


//ALIAS for in/out streams.
using std::cout;
using std::cin;
//ALIAS for STL vector
using std::vector;


//==========================================================================================
// Variables for options.
//==========================================================================================
struct Options{
    std::string imgdirpath; // image directory name.
    size_t maxgen; // number of generations.
    size_t fps; // generations presented per second.
    size_t pixel_size; // cell size in image( pixel size ).
    std::string bkgcolor; // background color name.
    std::string alivecolor; // alive cells color name.
    std::string outfile; // filename for representation of the simulation.
    std::string configFile; // initial config filename.
    vector< vector< char > > starter_config; // matrix for initial configuration;
};
//==========================================================================================



int main( int argc, char const *argv[] )
{
    Options arguments;

    if( processing_arguments( arguments, argc, argv ) )
    {
        cout << "Get data [ OK ]\n"; // need improvement
    }
    else
    {
        cout << "Get data [ FAILED ]\n"; // need improvement
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
