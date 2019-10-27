/**
 * @file life_game.cpp
 *
 * @description
 * This program simulates the Conway's Game of Life.
 * It reads a initial game configuration from a input file and
 * keeps updating it, if the user so whishes.
 *
 * ===========================================================================
 * @license
 *
 * This file is part of GAME OF LIFE project.
 *
 * GAME OF LIFE is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * GAME OF LIFE is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GAME OF LIFE.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Copyright (C) 2014-2019 Selan R. dos Santos, http://www.dimap.ufrn.br/~selan
 * ===========================================================================
 *
 * @author	Selan R dos Santos, <selan.rds@gmail.com>
 * @date	2015, updated 2015-04-03
 *
 * @remark On 2015-09-19 changed the way stability is verified.
 * In the previous version we just looked back one configuration and compare it
 * with the current configuration.
 * Now, the stability may span more than one configuration. Because of that we
 * need to keep track of all configurations and check whether the current configuration
 * has already been generated. If this is the case, the game has reached stability and
 * must stop.
 */

#include <cstdlib> // EXIT_SUCCESS

#include "../include/life_game.h"

int main( int argc, char *argv[] )
{
    life::LifeGame game;

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
