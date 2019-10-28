#ifndef GAME_MNG_H
#define GAME_MNG_H
#include <unordered_set>
#include <chrono> // time
#include <thread> // thread control

#include "./life_game.h"
#include "./arguments.h"

#define RUNNING 1
#define STABLE 2
#define EXTINCT 3
#define STOP 4

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


        virtual ~GameManager(){}

        bool isEXTINCT()
        {
            if( ( cfg.aliveCells == 0 ) and ( cfg.genNumber > 1 ) ){ return true; }

            return false;
        }

        // processing arguments and getting data.
        virtual void initialize( int argc, char *argv[] )
        {
            if( processing_arguments( arguments, argc, argv ) )
            {
                std::cout << "\n\x1b[32m[ OK ]\x1b[0m Get data \n";

                cfg.assign( arguments ); // passing all data from options.

                system("mkdir output");
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

            if( cfg.genNumber == cfg.firstMan.maxgen ){ return true; }

            if( isEXTINCT() ){ return true; }

            return false;

        }
}; // GameManager class.

} // namespace life.
#endif
