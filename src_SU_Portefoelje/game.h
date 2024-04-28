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
    bool _runGame;


public:
    void gameInit() {

        _runGame = true;
        while(_runGame) {
            std::cout << "New game (0), Load game (1), Save and exit (5):   ";
            std::cin >> _option;
            std::cout << std::endl;

            if(_option == 0) {
                std::cout << "Welcome to your new game!" << std::endl;
                std::cout << "It is going to be a fun journey of slaying enemies." << std::endl;
                std::cout << std::endl;

                std::string newHeroName = _initHero.newHero();
                Hero hero(newHeroName);
                hero.print();

                _runGame = false;
            }

            else if(_option == 1) {
                _DB.printHeroes();
                _DB.selectHero();

                _runGame = false;

            }

            else if(_option == 5) {
                std::cout << "Game saved!" << std::endl;

                _runGame = false;
            }

            else {
                std::cout << "ERROR: Choose a correct option" << std::endl;
            }
            std::cout << std::endl;
        }
    }



};


#endif // GAME_H
