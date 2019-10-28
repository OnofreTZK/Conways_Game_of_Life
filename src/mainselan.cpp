/*
===============================
Conway's Life Game Simulator  |
===============================
Authors:
Tiago Onofre & Rafael Fortunato.
*/

#include <cstdlib> // EXIT_SUCCESS

#include "../include/game_manager.h"

int main( int argc, char *argv[] )
{
    life::GameManager game;

    // Set up simulation.
    game.initialize( argc, argv );

    // Initial message.
    game.render();

    // The Game Loop.

    while( not game.game_over() )
    {
        game.process_events();
        game.update();
        game.render();
    }

    return EXIT_SUCCESS;
}


