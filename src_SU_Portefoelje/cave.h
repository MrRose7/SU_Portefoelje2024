#ifndef CAVE_H
#define CAVE_H
#include <iostream>

class Cave {
private:
    std::string _name;
    int _gold;

public:
    Cave(std::string name, int gold) : _name(name), _gold(gold) {}  // Default constructor to create a cave

    int getGold() {         // Getter method to get amount of gold in a cave
        return _gold;
    }

    void print() {          // Method for printing cave information
        std::cout << "----------------------------------" << std::endl;
        std::cout << "Cave info:" << std::endl;
        std::cout << "Name: " << _name << std::endl;
        std::cout << "Gold to retrieve: " << _gold << std::endl;
        std::cout << "----------------------------------" << std::endl;
        std::cout << std::endl;
    }
};


#endif // CAVE_H
