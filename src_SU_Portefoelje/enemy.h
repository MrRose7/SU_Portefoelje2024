#ifndef ENEMY_H
#define ENEMY_H
#include <iostream>

class Enemy {
private:
    std::string _name;
    int _hp;
    int _strength;
    int _xpDrop;
    std::string _element;

public:
    Enemy(std::string name, int hp, int strength, int xpDrop, std::string element) : _name(name), _hp(hp), _strength(strength), _xpDrop(xpDrop), _element(element) {}   // Constructor to create instance of an enemy

    std::string getName() { return _name; }         // Getter method for getting enemies name

    int getHp() { return _hp; }                     // Getter method for getting enemies current hp

    int getStrength() { return _strength; }         // Getter method for getting enemies strength

    int getXpDrop() { return _xpDrop; }             // Getter method for getting enemies xp that is dropped when defeated

    std::string getElement() { return _element; }   // Getter method for getting enemies element

    void decHp(int x) { _hp -= x; }                 // Method for decreasing enemies hp

    void print() {                                  // Method for printing enemies info to the terminal
        std::cout << "----------------------------------" << std::endl;
        std::cout << "Enemy info:" << std::endl;
        std::cout << "Name:     " << _name << std::endl;
        std::cout << "HP:       " << _hp << std::endl;
        std::cout << "Strength: " << _strength << std::endl;
        std::cout << "Element:  " << _element << std::endl;
        std::cout << "XP dropped if killed: " << _xpDrop << std::endl;
        std::cout << "----------------------------------" << std::endl;
        std::cout << std::endl;
    }
};

#endif // ENEMY_H
