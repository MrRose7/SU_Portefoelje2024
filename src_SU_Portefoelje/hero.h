#ifndef HERO_H
#define HERO_H
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <QCoreApplication>
#include <QtSql>
#include <QSqlDatabase>

class Hero {
private:
    std::string _name;
    int _xp;
    int _level;
    int _hp;
    int _strength;
    int _gold;
    int _magicNiveau;

public:
    Hero() {}   // Default constructor to create an instance of Hero

    Hero(std::string name) : _name(name), _xp(0), _level(1), _hp(10), _strength(2), _gold(0), _magicNiveau(0) {    // Constructor to load new hero into the database

        QString _name(name.c_str());

        QSqlQuery query;
        query.prepare("INSERT INTO hero (name, xp, level, hp, strength, gold, magic_niveau) VALUES (:name, :xp, :level, :hp, :strength, :gold, :magic_niveau)");
        query.bindValue(":name", _name);
        query.bindValue(":xp", _xp);
        query.bindValue(":level", _level);
        query.bindValue(":hp", _hp);
        query.bindValue(":strength", _strength);
        query.bindValue(":gold", _gold);
        query.bindValue(":magic_niveau", _magicNiveau);
        query.exec();
    }

    Hero(std::string name, int xp, int level, int hp, int strength, int gold, int magicNiveau) : _name(name), _xp(xp), _level(level), _hp(hp), _strength(strength), _gold(gold), _magicNiveau(magicNiveau) {} // Constructor to edit existing hero

    std::string newHero() {     // Method for creating a new character by getting name as user input
        std::string newHeroName;

        bool checkName = true;
        while(checkName) {
            std::cout << "Choose a name for your hero (one word only):  ";
            std::cin >> newHeroName;
            std::cout << std::endl;

            // Checks if name for the hero is empty
            if(newHeroName.empty()) {
                system("clear");
                std::cout << "ERROR: Name must not be empty" << std::endl;
            }
            else { checkName = newHeroName.empty(); }
        }

        return newHeroName;
    }

    std::string getName() { return _name; }         // Getter method for getting heroes name

    int getXp() { return _xp; }                     // Getter method for getting heroes current xp

    int getLevel() { return _level; }               // Getter method for getting heroes current level

    int getHp() { return _hp; }                     // Getter method for getting heroes current hp

    int getStrength() { return _strength; }         // Getter method for getting heroes strength

    int getGold() { return _gold; }                 // Getter method for getting heroes amount of gold

    int getMagicNiveau () { return _magicNiveau; }  // Getter method for getting heroes magic niveau

    void incGold(int x) { _gold += x; }             // Method for increasing heroes amount of gold upon defeating a cave

    void decGold(int x) { _gold -= x; }             // Method for decreasion heroeas amount of gold upon purchase of new magic

    void decHp(int x) { _hp -= x; }                 // Method for decreasing heroes hp

    void incXp(int x) { _xp += x; }                 // Method for increasing heroes xp

    void levelUp() {                                // Method for increasing heroes level when reaching level*1000xp
        while(_xp >= _level*1000) {                 // While-loop checks if xp is greater than the level*1000xp
            // Updating hero stats when leveling up
            _xp -= _level*1000;
            _level++;
            _hp += 2;
            _strength += 1;
            _magicNiveau += 2;

            // Printing a level up message
            if(_level < 10) {
                std::cout << "+-----------------------------+" << std::endl;
                std::cout << "| LEVEL UP!                   |" << std::endl;
                std::cout << "| You have reached level " << _level << "    |" << std::endl;
                std::cout << "| HP increased by 2           |" << std::endl;
                std::cout << "| Strength increased by 1     |" << std::endl;
                std::cout << "| Magic Niveau increased by 2 |" << std::endl;
                std::cout << "+-----------------------------+" << std::endl;
            }
            else if(_level >= 10 && _level < 100) {
                std::cout << "+-----------------------------+" << std::endl;
                std::cout << "| LEVEL UP!                   |" << std::endl;
                std::cout << "| You have reached level " << _level << "   |" << std::endl;
                std::cout << "| HP increased by 2           |" << std::endl;
                std::cout << "| Strength increased by 1     |" << std::endl;
                std::cout << "| Magic Niveau increased by 2 |" << std::endl;
                std::cout << "+-----------------------------+" << std::endl;
            }
            else {
                std::cout << "+-----------------------------+" << std::endl;
                std::cout << "| LEVEL UP!                   |" << std::endl;
                std::cout << "| You have reached level " << _level << "  |" << std::endl;
                std::cout << "| HP increased by 2           |" << std::endl;
                std::cout << "| Strength increased by 1     |" << std::endl;
                std::cout << "| Magic Niveau increased by 2 |" << std::endl;
                std::cout << "+-----------------------------+" << std::endl;
            }

            std::cout << std::endl;
        }
    }

    void print() {                              // Method for printing heroes info
        std::cout << "----------------------------------" << std::endl;
        std::cout << "Your heroes info:    " << std::endl;
        std::cout << "Name:         " << _name << std::endl;
        std::cout << "XP:           " << _xp << std::endl;
        std::cout << "Level:        " << _level << std::endl;
        std::cout << "HP:           " << _hp << std::endl;
        std::cout << "Strength:     " << _strength << std::endl;
        std::cout << "Gold:         " << _gold << std::endl;
        std::cout << "Magic Niveau: " << _magicNiveau << std::endl;
        std::cout << "----------------------------------" << std::endl;
    }

};

#endif // HERO_H
