#include "../include/arguments.h"

#include <cstdlib> //size_t
#include <iostream> // STL general( std:: )
#include <string> // STL string library( file and paths manip )
#include <vector> // STL vector library( initial config board )
#include <cassert>
#include <cstring>

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
