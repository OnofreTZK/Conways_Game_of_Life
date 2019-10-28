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
    size_t maxgen;                                      // number of generations.
    size_t fps;                                         // generations presented per second.
    size_t pixel_size = 5;                              // cell size in image( pixel size ). >>DEFAULT = 5.
    std::string bkgcolor = "GREEN";                     // background color name. >>DEFAULT = GREEN.
    std::string alivecolor;                             // alive cells color name. >>DEFAULT = RED.
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
    bool Status{false};       // true --> alive, false --> dead.
    size_t neighbours{0}; // alive cells count(around).
    // bool nextStatus{false};   // true --> stay or will be alive, false --> stay or will be dead.
};

namespace life
{
class LifeConfig
{
    private:
    Options firstMan;
    std::vector<std::vector<Cell>> firstManCells;
    std::vector<std::vector<char>> firstManChars;

    public:
        LifeConfig(Options);
        void PrintTable();
        void RenderNeighbours();
        void RefreshGeneration();
        void RenderCharTable(std::vector<std::vector<char>> &myCharVector);
        void printNeighboursTable();
};

} // namespace life
#endif
