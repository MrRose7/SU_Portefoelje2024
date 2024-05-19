#ifndef DBFETCH_H
#define DBFETCH_H
#include <QCoreApplication>
#include <QtSql>
#include <QSqlDatabase>
#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include "hero.h"
#include "enemy.h"

/* Class to fetch data from database*/
class DBFetch {
private:
    int _heroSelection;     // Variable to store user input that is selection for which hero to choose
    int _enemySelection;    // Variable to store user input that is selection for which enemy to fight
//    Hero _hero;

public:
    void dbInit() {         // Method for initialising database
        std::string dbUsername;
        std::string dbPassword;

        std::cout << "For the database to properly be initialised please type the username and password used for your mysql localhost." << std::endl;
        std::cout << std::endl;
        std::cout << "Username:     ";
        std::cin >> dbUsername;
        std::cout << "Password:     ";
        std::cin >> dbPassword;

        system("clear");

        QString QdbUsername = QString::fromStdString(dbUsername);
        QString QdbPassword = QString::fromStdString(dbPassword);

        QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
        db.setHostName("localhost");
        db.setDatabaseName("su_portefoelje2024");
        db.setUserName(QdbUsername);    // Change to username
        db.setPassword(QdbPassword);    // Change to password
        db.open();
    }

    bool printHeroes() {    // Method for printing all heroes in the database, to showcase their stats
        bool noHeroExists;
        int heroCount;

        QSqlQuery queryCheck;

        queryCheck.prepare("SELECT count(hero_id) FROM hero");
        queryCheck.exec();
        while(queryCheck.next()) {
            heroCount = queryCheck.value(0).toInt();
        }

        if(heroCount == 0) {
            system("clear");
            std::cout << "+----------------------------------------------------------+" << std::endl;
            std::cout << "| ERROR: No games exist. Please create a new game to play! |" << std::endl;
            std::cout << "+----------------------------------------------------------+" << std::endl;
            std::cout << std::endl;

            noHeroExists = true;
        }

        else {
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

            noHeroExists = false;
        }

        return noHeroExists;
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

        bool checkSelection = true;
        while(checkSelection) {     // Checks if selected hero exists in list of heroes
            std::cout << "Choose a hero to play as, by writing the heroes ID:   ";
            std::cin >> _heroSelection;  // Gets user input for which hero to choose
            std::cout << std::endl;

            // Checks if hero id exists
            auto findHero_id = std::find(hero_idVec.begin(), hero_idVec.end(), _heroSelection);
            if (findHero_id != hero_idVec.end()) {
                checkSelection = false;
                system("clear");
            }
            else
            {
                std::cout << "ERROR: Hero not found in list of heroes..." << std::endl;
            }
        }

        // Query gets heroes name, xp, level, hp and strength from the database
        QSqlQuery query;
        query.prepare("SELECT name, xp, level, hp, strength FROM hero WHERE hero.hero_id=?");
        query.addBindValue(_heroSelection);
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

        std::cout << "LIST OF ENEMIES TO FIGHT" << std::endl;
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

    Enemy selectEnemy() {         // Method for creating instance of enemy from users selection of a hero to play as
        // Vector to store enemy_id's in
        std::vector<int> enemy_idVec;
        int enemy_id;

        // SQL query to get all enemies id's from the database
        QSqlQuery queryCheck;
        queryCheck.prepare("SELECT enemy_id FROM enemy");
        queryCheck.exec();
        while(queryCheck.next()) {  // Loops through all hero id's in database and appends them to hero_idVec
            enemy_id = queryCheck.value(0).toInt();
            enemy_idVec.push_back(enemy_id);
        }

        bool checkSelection = true;
        while(checkSelection) {     // Checks if selected enemy exists in list of heroes
            std::cout << "FIGHTING TIME...   " << std::endl;
            std::cout << "Choose an enemy to fight by writing the enemies ID:   ";
            std::cin >> _enemySelection;
            std::cout << std::endl;

            // Checks if hero id exists
            auto findEnemyero_id = std::find(enemy_idVec.begin(), enemy_idVec.end(), _enemySelection);
            if (findEnemyero_id != enemy_idVec.end()) {
                checkSelection = false;
                system("clear");
            }
            else
            {
                std::cout << "ERROR: Enemy not found in list of enemies..." << std::endl;
            }
        }

        QSqlQuery query;

        query.prepare("SELECT name, hp, strength, xp_drop FROM enemy WHERE enemy.enemy_id=?");
        query.addBindValue(_enemySelection);
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

    void updateHero(int heroXp, int heroLevel, int heroHp, int heroStrength) {  // Method for updating heroes stats in the database (used when saving a game)
        QSqlQuery query;

        query.prepare("UPDATE hero SET xp=?, level=?, hp=?, strength=? WHERE hero.hero_id=?");
        query.addBindValue(heroXp);
        query.addBindValue(heroLevel);
        query.addBindValue(heroHp);
        query.addBindValue(heroStrength);
        query.addBindValue(_heroSelection);
        query.exec();
    }

    void gameOver() {   // Method for deleting hero from database (used for when hero is defeated)
        std::cout << "+------------+" << std::endl;
        std::cout << "| GAME OVER! |" << std::endl;
        std::cout << "+------------+" << std::endl;

        QSqlQuery query;

        query.prepare("DELETE FROM hero WHERE hero.hero_id=?");
        query.addBindValue(_heroSelection);
        query.exec();
    }

};



#endif // DBFETCH_H
