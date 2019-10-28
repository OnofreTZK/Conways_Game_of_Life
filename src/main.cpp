#include "../include/arguments.h"
#include "../include/life_game.h"

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

int main( int argc, char const *argv[] )
{
    // Struct with arguments data.
    Options arguments;

    if( processing_arguments( arguments, argc, argv ) )
    {
        life::LifeConfig firstman(arguments);
        firstman.PrintTable();
        firstman.RefreshGeneration();
        firstman.PrintTable();
        // firstman.printtable();


        cout << "\n\x1b[32m[ OK ]\x1b[0m Get data \n"; // need improvement
    }
    else
    {
        cout << "\n\x1b[31m[ FAILED ]\x1b[0m Get data \n"; // need improvement
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
