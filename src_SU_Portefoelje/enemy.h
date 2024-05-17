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
    Enemy(std::string name, int hp, int strength, int xpDrop) : _name(name), _hp(hp), _strength(strength), _xpDrop(xpDrop) {}   // Constructor to create instance of an enemy

    int getStrength() {     // Getter method for getting enemies strength
        return _strength;
    }

    int getHp() {           // Getter method for getting enemies current hp
        return _hp;
    }

    int getXpDrop() {       // Getter method for getting enemies xp that is dropped when defeated
        return _xpDrop;
    }

    std::string getName() { // Getter method for getting enemies name
        return _name;
    }

    void decHp(int x) {     // Method for decreasing enemies hp
        _hp -= x;
    }

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
