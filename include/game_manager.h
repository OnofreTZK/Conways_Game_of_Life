#ifndef GAME_MNG_H
#define GAME_MNG_H
#include <map> // std::map
#include <functional> // std::hash
#include <chrono> // time
#include <thread> // thread control
#include <string.h>
#include <iostream>
#include <iomanip>

#include "./life_game.h"
#include "./arguments.h"
#include "./canvas.h"
#include "./lodepng.h"
#include "./common.h"


#define RUNNING 1
#define STABLE 2
#define EXTINCT 3
#define STOP 4


typedef std::map< size_t, size_t > genSet;
/*!
 *  Define a game manager interface that implements the game loop.
 */

namespace life
{

class GameManager
{
    public:

        size_t stateMachine =RUNNING;

        // Constructor and destructor.
        GameManager( ){}

        // Generation
        LifeConfig cfg;

        // options data.
        Options arguments;

        // Hash Table.
        genSet hashTable;

        // Destructor.
        virtual ~GameManager(){}

        bool isEXTINCT()
        {
            if( ( cfg.aliveCells == 0 ) and ( cfg.genNumber > 1 ) ){ return true; }

            return false;
        }

        /*------------------------------ HASH TABLE -------------------------------*/

        // transform coordinates in a string.
        std::string generateString( std::vector< std::pair<size_t,size_t> > & coords )
        {
            std::stringstream oss;

            // vector >> stringstream
            for( int i = 0; i < coords.size(); i++)
            {
                oss << coords[i].first << " " << coords[i].second << " ";
            }

            // stringstream to string.

            return oss.str();

        }

        // Generate hashkey
        void hashFunction()
        {
           std::hash< std::string > hasher;

           cfg.hashKey = hasher(generateString( cfg.firstMan.coordinates ) );
        }

        // Add gen and linking with generated hashkey
        void addTo_HashTable()
        {
            hashTable[cfg.hashKey] = cfg.genNumber;
        }

        bool isSTABLE()
        {
            return hashTable.count( cfg.hashKey ) == 1;
        }
        //=============================================================================


        // processing arguments and getting data.
        virtual void initialize( int argc, char *argv[] )
        {
            if( processing_arguments( arguments, argc, argv ) )
            {
                std::cout << "\n\x1b[32m[ OK ]\x1b[0m Get data \n";

                cfg.assign( arguments ); // passing all data from options.

            }
            else
            {
                std::cout << "\n\x1b[31m[ FAILED ]\x1b[0m Get data \n";
                exit(1); //FAILURE;
            }
        }

        virtual void render()
        {
            // canvas must be here.
            if( cfg.firstMan.outfile != "" )
            {
                cfg.writeFile( cfg.firstMan.outfile, cfg.genNumber, cfg.firstMan.imgdirpath );
                Canvas image(cfg.firstMan.nCol, cfg.firstMan.nLin, 50);
                image.clear(cfg.firstMan.bkgcolor);
                for(auto i : cfg.firstMan.coordinates){
                   image.pixel(Point2{(int)i.first,(int)i.second}, color_pallet["red"]); 
                }

                //Stream to write name for encode_png
                std::ostringstream temp_name;
                temp_name << "../"+cfg.firstMan.imgdirpath+"/";
                temp_name << cfg.firstMan.outfile2;
                temp_name << std::to_string(cfg.genNumber).c_str();
                temp_name << ".png";

                // const char * name = strcat(cfg.firstMan.outfile2, char_internal_generation);

                encode_png(temp_name.str().c_str(), image.pixels(), image.col(), image.row());
                // std::cout << temp_name.str().c_str() << std::endl;
                temp_name.str("");
            }
            else

            cfg.PrintTable();

        }

        virtual void update()
        {
            cfg.RefreshGeneration();

            hashFunction();

            if( isSTABLE() )
            {
                stateMachine = STABLE;
            }

            if( isEXTINCT () )
            {
                stateMachine = EXTINCT;
            }

            addTo_HashTable();
        }

        // Thread speed control.
        virtual void process_events()
        {
            size_t duration = 1000/cfg.firstMan.fps;

            std::this_thread::sleep_for( std::chrono::milliseconds( duration ) );
        }

        virtual bool game_over( void )
        {
            if( cfg.firstMan.maxgen == 0 )
            {
                if( stateMachine == EXTINCT )
                {
                    std::cout << "\nGeneration status: \x1b[31mEXTINCT\x1b[0m\n";
                    return true; 
                }

                if( stateMachine == STABLE )
                {
                    std::cout << "\nGeneration status: \x1b[36mSTABLE\x1b[0m\n";
                    return true; 
                }

                if( stateMachine == STOP ){ return true; }
            }
            else if( cfg.genNumber == cfg.firstMan.maxgen )
            {
                 return true;
            }

            return false;

        }
}; // GameManager class.

} // namespace life.
#endif
