#ifndef GAME_H
#define GAME_H
#include <iostream>
#include "DBFetch.h"
#include "hero.h"

class Game {
private:
    int _option;
    DBFetch _DB;
    Hero _initHero;


public:
    int gameInit() {

        bool runGame = true;
        while(runGame) {
            std::cout << "New game (0), Load game (1), Save and exit (5):   ";
            std::cin >> _option;

            if(_option == 0) {
                std::cout << "You chose case 0" << std::endl;

                std::string newHeroName = _initHero.newHero();
                Hero hero(newHeroName);
                hero.print();
            }

            else if(_option == 1) {
                _DB.printHeroes();
            }

            else if(_option == 5) {
                std::cout << "Game saved!" << std::endl;
                runGame = false;
            }

            else {
                std::cout << "ERROR: Choose a correct option" << std::endl;
                runGame = false;
            }
            std::cout << std::endl;
        }
        return _option;
    }



};


#endif // GAME_H
