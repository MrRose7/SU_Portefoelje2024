#include <iostream>
#include "hero.h"
#include "enemy.h"
#include "DBFetch.h"
#include "game.h"

int main()
{
    system("clear");    // Clearing terminal

    // Initialises database
    DBFetch DB;
    DB.dbInit();

    // Runs game
    Game game;
    game.gameInit();

    return 0;
}
