#ifndef GAME_MNG_H
#define GAME_MNG_H

/*!
 *  Define a game manager interface that implements the game loop.
 */
class GameManager
{
    public:
        GameManager( ){}
        virtual ~GameManager(){}

        virtual void initialize(  int argc, char *argv[] )=0;
        virtual void render()=0;
        virtual void update()=0;
        virtual void process_events()=0;
        virtual bool game_over( void ) const=0;
}; // GameManager class.
#endif
