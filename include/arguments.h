#ifndef HELP_H
#define HELP_H

#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <cstdlib>


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
    std::vector< std::vector< char > > starter_config; // matrix for initial configuration;
};
//==========================================================================================

// help menu.
void printHelp();

// verify if last argument is a filename.
bool filename_verification( char const & filename );

// Arguments processing.
bool processing_arguments( Options & arguments, int argc, char const *argv[] );

#endif

// class cfg
// class life
// class manager
//    -manager configs.
//    -run simulations.
//    -call canvas
//    -hash table
//    -entry options( struct )
//
//LifeGame extended GameManager
