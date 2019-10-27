#ifndef CLASSES_H
#define CLASSES_H

#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <iterator>
#include <cctype>
#include <algorithm>
#include <utility>

//==========================================================================================
// Variables for options.
//==========================================================================================
struct Options{
    std::string imgdirpath; // image directory name.
    size_t maxgen; // number of generations.
    size_t fps; // generations presented per second.
    size_t pixel_size=5; // cell size in image( pixel size ). >>DEFAULT = 5.
    std::string bkgcolor="GREEN"; // background color name. >>DEFAULT = GREEN.
    std::string alivecolor; // alive cells color name. >>DEFAULT = RED.
    std::string outfile; // filename for representation of the simulation.
    std::string configFile; // initial config filename.
    size_t nLin; // number of rows( config ).
    size_t nCol; // number of columns( config ).
    char aliveCell; // alive cell character.
    std::vector< std::vector< char > > starter_config; // matrix for initial configuration.
    std::vector< std::pair< size_t, size_t > > coordinates; // alive cells coordinates.
};
//==========================================================================================


//==========================================================================================
// Cell
//==========================================================================================
struct Cell{
    bool Status; // true --> alive, false --> dead.
    size_t neighbours; // alive cells count(around).
    bool nextStatus; // true --> stay or will be alive, false --> stay or will be dead.
};

namespace life
{
    class LifeConfig
    {
        private:
            std::vector< std::vector< Cell > > Gen; // Generation grid;
            std::vector< std::pair< size_t, size_t > > coordinates; // generation coords.


        public:
            LifeConfig( size_t nLin, size_t nCol )
            {
                std::vector< Cell > cells;
                cells.resize( nCol );
                Gen.resize( nLin, cells );
            }

            // waiting for gamemanager implementation.
            void set_alive( Options & arguments ); // vector::gen = vector::starter_config.
            // coordinate keep ( i, j ) of the alive cells.


            /* --- Operators --- */


    };



} // namespace life
#endif
