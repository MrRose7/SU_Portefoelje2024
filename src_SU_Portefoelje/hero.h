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

public:
    Hero() {}   // Default constructor to create an instance of Hero

    Hero(std::string name) : _name(name), _xp(0), _level(1), _hp(10), _strength(2) {    // Constructor to load new hero into the database

        QString _name(name.c_str());

        QSqlQuery query;
        query.prepare("INSERT INTO hero (name, xp, level, hp, strength) VALUES (:name, :xp, :level, :hp, :strength)");
        query.bindValue(":name", _name);
        query.bindValue(":xp", _xp);
        query.bindValue(":level", _level);
        query.bindValue(":hp", _hp);
        query.bindValue(":strength", _strength);
        query.exec();
    }

    Hero(std::string name, int xp, int level, int hp, int strength) {

    }

    std::string newHero() {     // Method for creating a new character by getting name as user input
        std::string newHeroName;
        std::cout << "Choose a name for your Hero (one word only):  ";
        std::cin >> newHeroName;
        return newHeroName;
    }

    void selectHero() {         // VIKRER IKKE
        int selection;
        std::cout << "Chose a Hero to plays as, by writing the heroes ID:   ";
        std::cin >> selection;
        std::cout << std::endl;

        QSqlQuery query;

        query.prepare("SELECT name, xp, level, hp, strength FROM hero WHERE hero.hero_id=?");
        query.addBindValue(selection);
        query.exec();


        while (query.next()){
            QString tempName = query.value(0).toString();
            _name = tempName.toStdString();
            _xp = query.value(1).toInt();
            _level = query.value(2).toInt();
            _hp = query.value(3).toInt();
            _strength = query.value(4).toInt();
        }
    }

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
