#ifndef HERO_H
#define HERO_H
#include <iostream>

class Hero {
private:
    std::string _name;
    int _xp;
    int _level;
    int _hp;
    int _strength;

public:
    Hero(std::string name) : _name(name), _xp(0), _level(1), _hp(10), _strength(2) {}

    void print() {
        std::cout << "----------------------------------" << std::endl;
        std::cout << "Your heroes info:    " << std::endl;
        std::cout << "Name:     " << _name << std::endl;
        std::cout << "XP:       " << _xp << std::endl;
        std::cout << "Level:    " << _level << std::endl;
        std::cout << "HP:       " << _hp << std::endl;
        std::cout << "Strength: " << _strength << std::endl;
        std::cout << "----------------------------------\n" << std::endl;
    }
};

#endif // HERO_H
