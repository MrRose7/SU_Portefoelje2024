#ifndef MAGIC_H
#define MAGIC_H
#include <iostream>

class Magic {
private:
    int _magicId;
    std::string _name;
    int _strength;
    int _selfDamage;
    std::string _element;
    int _requiredMagic;
    int _price;

public:
    Magic(int magicId, std::string name, int strength, int selfDamage, std::string element, int requiredMagic, int price) : _magicId(magicId), _name(name), _strength(strength), _selfDamage(selfDamage), _element(element), _requiredMagic(requiredMagic), _price(price) {}    // Constructor to create instance of magic in game

    int getMagicId() { return _magicId; }               // Getter method for getting magics id

    int getStrength() { return _strength; }             // Getter method for getting magics strength

    int getSelfDamage() { return _selfDamage; }         // Getter method for getting magics self damage

    std::string getElement() { return _element; }       // Getter method for getting magics element

    int getRequiredMagic() { return _requiredMagic; }   // Getter method for getting magics required magic id

    int getPrice() { return _price; }                   // Getter method for getting magics price

    void print() {      // Method for printing magic info
        std::cout << "----------------------------------" << std::endl;
        std::cout << "Acquired magic info:" << std::endl;
        std::cout << "Name:         " << _name << std::endl;
        std::cout << "Strength:     " << _strength << std::endl;
        std::cout << "Self Damage:  " << _selfDamage << std::endl;
        std::cout << "Element:      " << _element << std::endl;
        std::cout << "----------------------------------" << std::endl;
    }

};


#endif // MAGIC_H
