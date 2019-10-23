#include "../include/help.h"


// print help menu.
void printHelp()
{
  std::cout << "\n* --imgdir <path> Specify directory where output images are written to.\n"
            << "* --maxgen <num> Number of generations to simulate\n"
            << "* --fps <num> Number of generations presented per second.\n"
            << "* --blocksize <num> Pixel size of a cell. Default = 5.\n"
            << "* --bkgcolor <color> Color name for the background. Default GREEN.\n"
            << "* --alivecolor <color> Color name for representing alive cells. Default RED.\n"
            << "* --outfile <filename> Write the text representation of the simulation to the given filename.\n\n"
            << "\x1b[96mAvailable colors are:\x1b[0m\n"
            << "BLACK BLUE CRIMSON DARK_GREEN DEEP_SKY_BLUE DODGER_BLUE\n"
            << "GREEN LIGHT_BLUE LIGHT_GREY LIGHT_YELLOW RED STEEL_BLUE\n"
            << "WHITE YELLOW\n";
}


bool filename_verification( char const & filename )
{
    std::string aux = &filename;

    // verify .txt
    if(  aux[aux.length() - 1] == 't' )
    {
        if( aux[aux.length() - 2] == 'x' )
        {
            if( aux[aux.length() - 3] == 't')
            {
                if( aux[aux.length() - 4] == '.' )
                {
                    return true;
                }
            }
        }
    }

    // verify .dat
    if(  aux[aux.length() - 1] == 't' )
    {
        if( aux[aux.length() - 2] == 'a' )
        {
            if( aux[aux.length() - 3] == 'd')
            {
                if( aux[aux.length() - 4] == '.' )
                {
                    return true;
                }
            }
        }
    }



    return false;

}



