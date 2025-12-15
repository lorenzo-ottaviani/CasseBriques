/*
* Project : Breakout Game
* Authors : Joseph DMYTRIYEV, Lorenzo OTTAVIANI and Abdoullah TOURE.
* Date : 14/12/2025 20h21
* Aim of the program :
* A classic Breakout game implementation.
* The player controls a paddle to bounce a ball and destroy bricks.
* Input   : Keyboard (Left/Right Arrows to move, Space to restart)
* Output  : Console logs (Game Started/Over) and Window display.
*/


/* ===  INCLUDES  === */
#include <iostream>
#include "Game.hpp"


/* ===  ENTRY POINT  === */

int main() {
    std::cout << "=== BREAKOUT GAME STARTED ===" << std::endl;
    std::cout << "Controls: Left/Right Arrows to move, Space to restart." << std::endl;

    // Create the game engine instance
    Game game;

    // Start the game loop
    game.run();

    return 0;
}
