#ifndef HELP_H
#define HELP_H

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

// help menu.
void printHelp();

// verify if last argument is a filename.
bool filename_verification( char const & filename );


template< typename T >
//==========================================================================================
// Arguments processing.
//==========================================================================================
bool processing_arguments( T & arguments, int argc, char const *argv[] )
{
    if( argc < 2 ) // min arguments.
    {
        std::cout << "\x1b[31mToo few arguments!\x1b[0m\n\nAt least inform initial configuration filename!\n\n";
        std::cout << "\x1b[93mUsage\x1b[0m: glife [<options>] <input_cfg_file>\n"
             << "Simulation options:\n\t\x1b[92m./glife\x1b[0m --help to see the menu.\n";
        return false;
    }
    if( argc > 16 ) // max arguments.
    {
        std::cout << "\x1b[31mToo many arguments!\x1b[0m\n\n";
        std::cout << "\x1b[93mUsage\x1b[0m: glife [<options>] <input_cfg_file>\n"
             << "Simulation options:\n\t\x1b[92m./glife\x1b[0m --help to see the menu.\n";
    }
    if( ( argc == 2 ) and ( strcmp( argv[1], "--help" ) == 0 ) ) // print help menu.
    {
        printHelp();

        return true;
    }
    // verify if second argument is a valid file.
    if( ( argc == 2 ) and ( filename_verification( *argv[1] ) == true )  )
    {
        //read file function TODO.
    }
    else if( ( argc == 2 ) and ( filename_verification( *argv[1] ) == false )  )
    {
        std::cout << "\x1b[31mInvalid file!\x1b[0m\n\nplease, input a .txt or .dat file.\n";
        return false;
    }

    if( argc > 2 )
    {
        for( int i = 1; i < argc; i++ )
        {
            if( arguments.configFile == "" )
            {
                if( ( argv[i][0] != '-' ) and ( argv[i][1] != '-') ) // filtering options
                {
                    if( filename_verification( *argv[i] ) == true ) // verify a valid filename.
                    {
                        arguments.configFile = argv[i];
                    }
                    else if( ( filename_verification( *argv[i] ) == false ) and ( i == argc - 1 ) )
                    {
                        // non valid file.
                        std::cout << "\x1b[31mInvalid file!\x1b[0m\n\nplease, input a .txt or .dat file.\n";
                        return false;
                    }
                    else if( filename_verification( *argv[i] ) == false )
                    {
                        continue;
                    }
                }
            }

            if( strcmp( argv[i], "--imgdir" ) == 0 )
            {
                arguments.imgdirpath = argv[i+1];
            }

            if( strcmp( argv[i], "--maxgen" ) == 0 )
            {
                arguments.maxgen = atoi(argv[i+1]);
            }

            if( strcmp( argv[i], "--fps" ) == 0 )
            {
                arguments.fps = atoi(argv[i+1]);
            }

            if( strcmp( argv[i], "--blocksize" ) == 0 )
            {
                arguments.pixel_size = atoi( argv[i+1]);
            }

            if( strcmp( argv[i], "--bkgcolor" ) == 0 )
            {
                arguments.bkgcolor = argv[i+1];
            }

            if( strcmp( argv[i], "--alivecolor" ) == 0 )
            {
                arguments.alivecolor = argv[i+1];
            }

            if( strcmp( argv[i], "--outfile" ) == 0 )
            {
                arguments.outfile = argv[i+1];
                std::cout << "output file = " << arguments.outfile << "\n";
            }


        }
    }

    return true;
}
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
