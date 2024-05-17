#ifndef DBFETCH_H
#define DBFETCH_H
#include <QCoreApplication>
#include <QtSql>
#include <QSqlDatabase>
#include <iostream>
#include <algorithm>
#include "hero.h"
#include "enemy.h"

/* Class to fetch data from database*/
class DBFetch {
public:
    void dbInit() {         // Method for initialising database
        QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
        db.setHostName("localhost");
        db.setDatabaseName("su_portefoelje2024");
        db.setUserName("lucas");        // Change to username
        db.setPassword("password");     // Change to password
        db.open();
    }

    void printHeroes() {    // Method for printing all heroes in the database, to showcase their stats
        QSqlQuery query;

        query.prepare("SELECT * FROM hero");
        query.exec();

        std::cout << "ALL SAVED GAMES" << std::endl;
        std::cout << "----------------------------------------------------------------------" << std::endl;
        std::cout << "hero_id:  " << "name:     " << "  xp:   " << "    level:    " << "    hp:     " << "strength:" << std::endl;
        std::cout << "----------------------------------------------------------------------" << std::endl;
        while (query.next()) {
                QString hero_id = query.value(0).toString();
                QString name = query.value(1).toString();
                QString xp = query.value(2).toString();
                QString level = query.value(3).toString();
                QString hp = query.value(4).toString();
                QString strength = query.value(5).toString();

                qDebug() << hero_id << ",   " << name << ", " << xp << ",       " << level << ",    " << hp << ",   " << strength;
        }
        std::cout << "----------------------------------------------------------------------" << std::endl;
        std::cout << std::endl;
    }

    Hero selectHero() {             // Method for creating instance of hero from users selection of a hero to play as
        // Vector to store hero_id's in
        std::vector<int> hero_idVec;
        int hero_id;

        // SQL query to get all hero id's from the database
        QSqlQuery queryCheck;
        queryCheck.prepare("SELECT hero_id FROM hero");
        queryCheck.exec();
        while(queryCheck.next()) {  // Loops through all hero id's in database and appends them to hero_idVec
            hero_id = queryCheck.value(0).toInt();
            hero_idVec.push_back(hero_id);
        }

        int selection;              // Variable to store user input that is selection for which hero to choose

        bool checkSelection = true;
        while(checkSelection) {     // Checks if selected hero exists in list of heroes
            std::cout << "Chose a Hero to play as, by writing the heroes ID:   ";
            std::cin >> selection;  // Gets user input for which hero to choose
            std::cout << std::endl;

            // Checks if hero id exists
            auto findHero_id = std::find(hero_idVec.begin(), hero_idVec.end(), selection);
            if (findHero_id != hero_idVec.end()) {
                checkSelection = false;
            }
            else
            {
                std::cout << "ERROR: Hero not found in list of heroes..." << std::endl;
            }
        }

        // Query gets heroes name, xp, level, hp and strength from the database
        QSqlQuery query;
        query.prepare("SELECT name, xp, level, hp, strength FROM hero WHERE hero.hero_id=?");
        query.addBindValue(selection);
        query.exec();

        std::string name;
        int xp;
        int level;
        int hp;
        int strength;
        while(query.next()) {
            QString tempName = query.value(0).toString();
            name = tempName.toStdString();
            xp = query.value(1).toInt();
            level = query.value(2).toInt();
            hp = query.value(3).toInt();
            strength = query.value(4).toInt();
        }

        Hero hero(name, xp, level, hp, strength);
        hero.print();
        return hero;
    }

    void printEnemies() {       // Method for printing all enemies in the database, to showcase their stats
        QSqlQuery query;

        query.prepare("SELECT * FROM enemy");
        query.exec();

        std::cout << "HERE IS A LIST OF ALL ENEMIES" << std::endl;
        std::cout << "----------------------------------------------------------------------" << std::endl;
        std::cout << "enemy_id:  " << "name:     " << "  hp:   " << "    strength:    " << "    xp_drop:     " << std::endl;
        std::cout << "----------------------------------------------------------------------" << std::endl;
        while (query.next()) {
                QString enemy_id = query.value(0).toString();
                QString name = query.value(1).toString();
                QString hp = query.value(2).toString();
                QString strength = query.value(3).toString();
                QString xp_drop = query.value(4).toString();

                qDebug() << enemy_id << ",   " << name << ", " << hp << ",       " << strength << ",    " << xp_drop;
        }
        std::cout << "----------------------------------------------------------------------" << std::endl;
        std::cout << std::endl;
    }

    Enemy selectEnemy() {         // Method for creating instance of hero from users selection of a hero to play as
        int selection;
        std::cout << "FIGHTING TIME...   " << std::endl;
        std::cout << "Chose an enemy to fight by writing the enemies ID:   ";
        std::cin >> selection;
        std::cout << std::endl;

        QSqlQuery query;

        query.prepare("SELECT name, hp, strength, xp_drop FROM enemy WHERE enemy.enemy_id=?");
        query.addBindValue(selection);
        query.exec();

        std::string name;
        int hp;
        int strength;
        int xp_drop;
        while (query.next()){
            QString tempName = query.value(0).toString();
            name = tempName.toStdString();
            hp = query.value(1).toInt();
            strength = query.value(2).toInt();
            xp_drop = query.value(3).toInt();
        }

        Enemy enemy(name, hp, strength, xp_drop);
        enemy.print();
        return enemy;
    }

};



#endif // DBFETCH_H
