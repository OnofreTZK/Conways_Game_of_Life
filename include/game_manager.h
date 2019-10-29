#ifndef GAME_MNG_H
#define GAME_MNG_H
#include <map> // std::map
#include <functional> // std::hash
#include <chrono> // time
#include <thread> // thread control

#include "./life_game.h"
#include "./arguments.h"

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


        void hashFunction()
        {
           std::hash< std::string> hasher;

           cfg.hashKey = hasher(generateString( cfg.firstMan.coordinates ) );
        }

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

                system("mkdir ../output");
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
                cfg.writeFile( cfg.firstMan.outfile, cfg.genNumber );
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
            if( stateMachine == STOP ){ return true; }

            if( stateMachine == STABLE ){ return true; }

            if( cfg.genNumber == cfg.firstMan.maxgen ){ return true; }

            if( isEXTINCT() ){ return true; }

            return false;

        }
}; // GameManager class.

} // namespace life.
#endif
