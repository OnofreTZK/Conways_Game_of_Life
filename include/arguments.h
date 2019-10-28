#ifndef HELP_H
#define HELP_H

#include "./life_game.h"

// help menu.
void printHelp();

// verify if last argument is a filename.
bool filename_verification( char const & filename );

// Arguments processing.
bool processing_arguments( Options & arguments, int argc, char *argv[] );

// Read initial config file.
void readFile( Options & arguments );

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
