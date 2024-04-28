#include <iostream>
#include "hero.h"
#include "enemy.h"
#include "DBFetch.h"
#include "game.h"

int main()
{
    // Initialises database
    DBFetch DB;
    DB.dbInit();

    Game game;
    game.gameInit();

    return 0;
}
