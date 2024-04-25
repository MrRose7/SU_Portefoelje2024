#ifndef ENEMY_H
#define ENEMY_H
#include <iostream>

class Enemy {
private:
    std::string _name;
    int _hp;
    int _strength;
    int _xpDrop;

public:
    Enemy(std::string name, int hp, int strength, int xpDrop) : _name(name), _hp(hp), _strength(strength), _xpDrop(xpDrop) {}

    void print() {
        std::cout << "----------------------------------" << std::endl;
        std::cout << "Enemy info:" << std::endl;
        std::cout << "Name:     " << _name << std::endl;
        std::cout << "HP:       " << _hp << std::endl;
        std::cout << "Strength: " << _strength << std::endl;
        std::cout << "XP dropped if killed: " << _xpDrop << std::endl;
    }
};

#endif // ENEMY_H
