#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <stdlib.h>
#include "DBFetch.h"
#include "hero.h"

class Game {
private:
    int _option;
    DBFetch _db;
    Hero _initHero;
    bool _runGame;
    bool _runMenu;


public:
    void gameInit() {
        Hero hero;

        // While-loop to run the menu
        _runMenu = true;
        while(_runMenu) {
            std::cout << "Welcome to Dragon Slayer where you, as a hero, will try to fight of all the enemies" << std::endl;
            std::cout << "to get to the final boss, the migthy dragon Stormwing!" << std::endl;
            std::cout << "------------------------------------------------------------------------------------" << std::endl;
            std::cout << std::endl;

            std::cout << "New game (0), Load game (1):  ";
            std::cin >> _option;
            std::cout << std::endl;
            system("clear");

            if(_option == 0) {
                std::cout << "Welcome to your new game!" << std::endl;
                std::cout << "It is going to be a fun journey of slaying enemies." << std::endl;
                std::cout << std::endl;

                std::string newHeroName = _initHero.newHero();
                system("clear");
                Hero hero(newHeroName);
                hero.print();
                std::cout << std::endl;

                std::cout << "To play with your new hero, please choose option 1 to load a game with your new hero, whereafter you can choose your new hero!" << std::endl;

            }

            else if(_option == 1) {
                system("clear");

                // Initialising game by letting player choose a hero to play as and selecting an enemy to fight
                _runMenu = _db.printHeroes();
                if(_runMenu == false) {
                    hero = _db.selectHero();
                }
            }

            else {
                std::cout << "ERROR: Choose a correct option" << std::endl;
            }
            std::cout << std::endl;
        }

        // While-loop to run the game
        _runGame = true;
        while(_runGame) {
            std::cout << "Fight enemy (2), Enter a cave (3), Save & exit (5):   ";
            std::cin >> _option;
            std::cout << std::endl;
            system("clear");

            if(_option == 2) {      // If option 2 is choosen enemy fight begins
                hero.print();       // Printing heroes info
                std::cout << std::endl;

                // Printing list of enemies to fight and letting user choose which enemy to fight
                _db.printEnemies();
                Enemy enemy = _db.selectEnemy();

                // Getting hero and enemy stats
                int heroStrength = hero.getStrength();
                int heroHp = hero.getHp();
                std::string heroName = hero.getName();
                int enemyStrength = enemy.getStrength();
                int enemyHp = enemy.getHp();
                std::string enemyName = enemy.getName();

                // Creating fighting scene
                std::cout << "----------- FIGHT IS ON -----------" << std::endl;
                while(enemyHp > 0 && heroHp > 0) {
                    std::cout << heroName << " attacks " << enemyName << std::endl;
                    enemy.decHp(heroStrength);
                    enemyHp = enemy.getHp();
                    std::cout << enemyName << " has " << enemyHp << " hp left..." << std::endl;
                    std::cout << std::endl;
                    if(enemyHp <= 0) { break; }

                    std::cout << enemyName << " attacks " << heroName << std::endl;
                    hero.decHp(enemyStrength);
                    heroHp = hero.getHp();
                    std::cout << heroName << " has " << heroHp << " hp left..." << std::endl;
                    std::cout << std::endl;
                }

                // Choosing future game path based on the fights outcome
                if(heroHp <= 0) {
                    std::cout << "+---------------------------+" << std::endl;
                    std::cout << "| You have been defeated... |" << std::endl;
                    std::cout << "+---------------------------+" << std::endl;
                    std::cout << std::endl;

                    _db.gameOver();
                    _runGame = false;
                }
                else if(enemyHp <= 0) {
                    std::cout << "+-------------------------------------+" << std::endl;
                    std::cout << "| You have defeated the mighty enemy!" << " |" << std::endl;
                    std::cout << "+-------------------------------------+" << std::endl;
                    std::cout << std::endl;
                    int xpDropped = enemy.getXpDrop();
                    hero.incXp(xpDropped);

                    hero.levelUp();

                    std::cout << "----------- UPDATED STATS -----------" << std::endl;
                    hero.print();
                }
                else {
                    std::cout << "Ops something went wrong..." << std::endl;
                }

            }

            else if(_option == 3) {     // If option 3 is choosen hero gets to enter a cave
                // Printing list of caves and letting user choose which cave to enter
                _db.printCaves();
                Cave cave = _db.selectCave();

                _db.printCaveEnemies(); // Printing list of enemies in the choosen cave
            }

            else if(_option == 5) {     // If option 5 is choosen game is saved and exited
                hero.print();
                std::cout << std::endl;

                std::cout << "+-------------+" << std::endl;
                std::cout << "| Game saved! |" << std::endl;
                std::cout << "+-------------+" << std::endl;

                // Getting necessary hero stats
                int heroXp = hero.getXp();
                int heroLevel = hero.getLevel();
                int heroHp = hero.getHp();
                int heroStrength = hero.getStrength();

                _db.updateHero(heroXp, heroLevel, heroHp, heroStrength);    // Updating hero in database for the game to be saved

                _runGame = false;
            }

            else {                      // If user types incorrect option print error and let user try again
                std::cout << "ERROR: Choose a correct option" << std::endl;
            }
            std::cout << std::endl;
        }
    }



};


#endif // GAME_H
