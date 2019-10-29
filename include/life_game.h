#ifndef LIFE_GAME_H
#define LIFE_GAME_H

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
struct Options
{
    std::string imgdirpath;                             // image directory name.
    size_t maxgen =0;                                      // number of generations.
    size_t fps;                                         // generations presented per second.
    size_t pixel_size = 5;                              // cell size in image( pixel size ). >>DEFAULT = 5.
    std::string bkgcolor = "GREEN";                     // background color name. >>DEFAULT = GREEN.
    std::string alivecolor = "RED";                             // alive cells color name. >>DEFAULT = RED.
    std::string outfile;                                // filename for representation of the simulation.
    std::string configFile;                             // initial config filename.
    size_t nLin;                                        // number of rows( config ).
    size_t nCol;                                        // number of columns( config ).
    char aliveCell;                                     // alive cell character.
    std::vector<std::vector<char>> starter_config;      // matrix for initial configuration.
    std::vector<std::pair<size_t, size_t>> coordinates; // alive cells coordinates.
};
//==========================================================================================

//==========================================================================================
// Cell
//==========================================================================================
struct Cell
{
    bool Status{false}; // true --> alive, false --> dead.
    size_t neighbours{0}; // alive cells count(around).
    // bool nextStatus{false};   // true --> stay or will be alive, false --> stay or will be dead.
};

namespace life
{
class LifeConfig
{
    private:
    std::vector<std::vector<Cell>> firstManCells;
    std::vector<std::vector<char>> firstManChars;

    public:
        /* Must be access by the rest of program.  */
        size_t hashKey;
        Options firstMan;
        size_t aliveCells;
        size_t genNumber =1; // generation ID.
        /*-----------------------------------------*/


        // Constructors.
        LifeConfig(){};
        LifeConfig(Options);

        void assign(Options); // Passing data.
        void PrintTable();
        void RenderNeighbours(); // count alive neighbours.
        void RefreshGeneration(); // update generation
        void RenderCharTable(std::vector<std::vector<char>> &myCharVector); // update vector
        void printNeighboursTable();
        void writeFile( std::string filename, size_t genNumber, std::string dirpath ); // create file.
};

} // namespace life
#endif
