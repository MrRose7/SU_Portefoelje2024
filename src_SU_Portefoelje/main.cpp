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

    Hero test;
    test.selectHero();

    Game chooseOption;
    chooseOption.gameInit();

    return 0;
}
