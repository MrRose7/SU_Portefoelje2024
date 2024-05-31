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
    bool _runCave;
    bool _runCaveFight;
    bool _gameOver;
    bool _runShop;

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
                    _db.printAcquiredMagic();
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
            std::cout << "Fight enemy (2), Enter a cave (3), Visit magic shop (7), Save & exit (9):   ";
            std::cin >> _option;
            std::cout << std::endl;
            system("clear");

            if(_option == 2) {      // If option 2 is choosen enemy fight begins
                hero.print();
                _db.printAcquiredMagic();

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

                hero.print();
                _db.printAcquiredMagic();

                _db.printCaveEnemies(); // Printing list of enemies in the choosen cave

                std::cout << "Dare to take on all these cave monsters?" << std::endl;
                std::cout << "Defeat them all and you will be rewarded with " << cave.getGold() << " gold!" << std::endl;
                std::cout << std::endl;

                // While loop to run the cave fight
                _runCave = true;
                while(_runCave) {
                    std::cout << "Begin fight (4), Exit cave (5):   ";
                    std::cin >> _option;

                    if(_option == 4) {              // If option 4 is choosen hero fights all enemies in the cave
                        system("clear");
                        std::vector<int> caveEnemyIdVec = _db.getEnemyIdVec();

                        _runCaveFight = true;
                        int i = 0;
                        while(i < caveEnemyIdVec.size() && _runCaveFight) {
                            _db.printCaveEnemies();
                            hero.print();
                            _db.printAcquiredMagic();

                            Enemy enemy = _db.selectCaveEnemy(caveEnemyIdVec[i]);
                            i++;

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
                                _runCaveFight = false;
                                _runCave = false;
                                _runGame = false;
                                _gameOver = true;
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
                                std::cout << std::endl;

                                if(i < caveEnemyIdVec.size()) {
                                    std::cout << "Press SPACEBAR then ENTER to begin next fight:";
                                }
                                else {
                                    std::cout << "Press SPACEBAR then ENTER to continue:";
                                }

                                while(1) {
                                    if(' ' == getchar()) {
                                        break;
                                    }
                                }

                                system("clear");

                            }
                            else {
                                std::cout << "Ops something went wrong..." << std::endl;
                            }

                        }

                        if(!_gameOver) {
                            std::cout << "You made it through the cave. Nicely done!" << std::endl;
                            std::cout << "Your reward for this bravery is " << cave.getGold() << " gold!" << std::endl;
                            std::cout << std::endl;

                            hero.incGold(cave.getGold());   // Increasing heroes amount of gold based on what cave was defeated
                            hero.print();
                            std::cout << std::endl;
                        }

                        _runCave = false;
                    }

                    else if(_option == 5) {     // If option 5 is choosen hero exits cave
                        system("clear");
                        std::cout << "Come back later and try to defeat the cave monsters to get your gold!" << std::endl;
                        _runCave = false;
                    }
                    else {                      // If user types incorrect option print error and let user try again
                        std::cout << std::endl;
                        std::cout << "ERROR: Choose a correct option" << std::endl;
                    }
                }
            }

            else if(_option == 7) {     // If option 7 is choosen hero visits magic shop
                std::cout << "Weolcome to the magic shop!" << std::endl;
                std::cout << "Here you can acquire new magic to help you fight enemies" << std::endl;
                std::cout << std::endl;

                bool _runShop = true;
                while(_runShop) {
                    _db.printMagic();
                    hero.print();
                    std::cout << std::endl;

                    std::cout << "Buy new magic (1), Leave magic shop (5):  ";
                    std::cin >> _option;

                    if(_option == 1) {          // If optoin 1 is choosen hero is able to buy new magic
                        system("clear");

                        _db.printMagic();

                        hero.print();
                        std::cout << std::endl;

                        Magic magic = _db.buyMagic();

                        if(magic.getRequiredMagic() != 0 && _db.checkHeroMagics(magic.getRequiredMagic()) == false) {
                            system("clear");
                            _db.printRequiredMagic(magic.getRequiredMagic());
                        }
                        else if(_db.checkHeroMagics(magic.getMagicId())) {  // Checks if hero already has the magic
                            system("clear");
                            std::cout << "Magic already acquired!" << std::endl;
                        }
                        else if(hero.getGold() < magic.getPrice()) {        // Checks if hero has enough gold for the purchase
                            system("clear");
                            std::cout << "Not enough gold!" << std::endl;
                            std::cout << "Acquire " << magic.getPrice() - hero.getGold() << " more gold to buy choosen magic..." << std::endl;
                        }
                        else if(hero.getGold() >= magic.getPrice() && _db.checkHeroMagics(magic.getMagicId()) == false) {   // Updates hero_magic table in database with the new magic
                            _db.updateHeroMagics(magic.getMagicId());

                            system("clear");
                            std::cout << "New magic acquired!" << std::endl;
                            std::cout << magic.getPrice() << " gold has been deducted from your overall amount" << std::endl;
                            std::cout << std::endl;

                            magic.print();

                            hero.decGold(magic.getPrice());                 // Decreasing heroes amount of gold based on price of purchase

                        }

                    }
                    else if(_option == 5) {     // If option 5 is choosen hero exits magic shop
                        system("clear");

                        std::cout << "Come back later to buy new magic!" << std::endl;
                        _runShop = false;
                    }
                    else {                      // If user types incorrect option print error and let user try again
                        system("clear");
                        std::cout << "ERROR: Choose a correct option" << std::endl;
                    }
                    std::cout << std::endl;

                }
            }

            else if(_option == 9) {     // If option 5 is choosen game is saved and exited
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
                int heroGold = hero.getGold();
                int heroMagicNiveau = hero.getMagicNiveau();

                _db.updateHero(heroXp, heroLevel, heroHp, heroStrength, heroGold, heroMagicNiveau);    // Updating hero in database for the game to be saved

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
