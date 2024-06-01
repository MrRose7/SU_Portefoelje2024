#ifndef DBFETCH_H
#define DBFETCH_H
#include <QCoreApplication>
#include <QtSql>
#include <QSqlDatabase>
#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <vector>
#include "hero.h"
#include "enemy.h"
#include "cave.h"
#include "magic.h"

/* Class to fetch data from database*/
class DBFetch {
private:
    int _heroSelection;             // Variable to store user input that is selection for which hero to choose
    int _enemySelection;            // Variable to store user input that is selection for which enemy to fight
    int _caveSelection;             // Variable to store user input that is selection for which cave to enter
    std::vector<int> _enemyIdVec;   // Vector to store enemy_id's
    int _buyMagicSelection;         // Variable to store user input that is selection for which magic to buy
    int _magicSelection;            // Variable to store user input that is selection for which magic to use in fight
    int _heroMagicCount;            // Variable to store the count of how many magics hero has acquired

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
        db.setDatabaseName("su_portefoelje2024_it3");
        db.setUserName(QdbUsername);    // MYSQL localhost username
        db.setPassword(QdbPassword);    // MYSQL localhost password
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
            std::cout << "-------------------------------------------------------------------------------------------" << std::endl;
            while (query.next()) {
                    QString hero_id = query.value(0).toString();
                    QString name = query.value(1).toString();
                    QString xp = query.value(2).toString();
                    QString level = query.value(3).toString();
                    QString hp = query.value(4).toString();
                    QString strength = query.value(5).toString();
                    QString gold = query.value(6).toString();
                    QString magicNiveau = query.value(7).toString();

                    std::cout << "id=" << hero_id.toStdString() << ", name=" << name.toStdString() << ", xp=" << xp.toStdString() << ", lvl=" << level.toStdString() << ", hp=" << hp.toStdString() << ", strength=" << strength.toStdString() << ", gold=" << gold.toStdString() << ", magic_niveau=" << magicNiveau.toStdString() << std::endl;
            }
            std::cout << "-------------------------------------------------------------------------------------------" << std::endl;
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

        // Query gets heroes name, xp, level, hp, strength and gold from the database
        QSqlQuery query;
        query.prepare("SELECT name, xp, level, hp, strength, gold, magic_niveau FROM hero WHERE hero.hero_id=?");
        query.addBindValue(_heroSelection);
        query.exec();

        std::string name;
        int xp;
        int level;
        int hp;
        int strength;
        int gold;
        int magicNiveau;
        while(query.next()) {
            QString tempName = query.value(0).toString();
            name = tempName.toStdString();
            xp = query.value(1).toInt();
            level = query.value(2).toInt();
            hp = query.value(3).toInt();
            strength = query.value(4).toInt();
            gold = query.value(5).toInt();
            magicNiveau = query.value(6).toInt();
        }

        Hero hero(name, xp, level, hp, strength, gold, magicNiveau);
        hero.print();
        return hero;
    }

    void printEnemies() {       // Method for printing enemies in the database, outside of caves, to showcase their stats
        QSqlQuery query;

        query.prepare("SELECT * FROM enemy WHERE enemy.enemy_id NOT IN (SELECT cave_enemy.enemy_id FROM cave_enemy)");
        query.exec();

        std::cout << "LIST OF ENEMIES TO FIGHT" << std::endl;
        std::cout << "----------------------------------------------------------------------" << std::endl;
        while (query.next()) {
                QString enemy_id = query.value(0).toString();
                QString name = query.value(1).toString();
                QString hp = query.value(2).toString();
                QString strength = query.value(3).toString();
                QString xp_drop = query.value(4).toString();
                QString element = query.value(5).toString();

                std::cout << "id=" << enemy_id.toStdString() << ", name=" << name.toStdString() << ", hp=" << hp.toStdString() << ", strength=" << strength.toStdString() << ", xpDrop=" << xp_drop.toStdString() << ", element=" << element.toStdString() << std::endl;

        }
        std::cout << "----------------------------------------------------------------------" << std::endl;
        std::cout << std::endl;
    }

    Enemy selectEnemy() {         // Method for creating instance of enemy from users selection of enemy to fight
        // Vector to store enemy_id's in
        std::vector<int> enemy_idVec;
        int enemy_id;

        // SQL query to get all enemies id's from the database
        QSqlQuery queryCheck;
        queryCheck.prepare("SELECT enemy.enemy_id FROM enemy WHERE enemy.enemy_id NOT IN (SELECT cave_enemy.enemy_id FROM cave_enemy)");
        queryCheck.exec();
        while(queryCheck.next()) {  // Loops through all enemy id's in database and appends them to enemy_idVec
            enemy_id = queryCheck.value(0).toInt();
            enemy_idVec.push_back(enemy_id);
        }

        bool checkSelection = true;
        while(checkSelection) {     // Checks if selected enemy exists in list of enemies
            std::cout << "FIGHTING TIME...   " << std::endl;
            std::cout << "Choose an enemy to fight by writing the enemies ID:   ";
            std::cin >> _enemySelection;
            std::cout << std::endl;

            // Checks if hero id exists
            auto findEnemy_id = std::find(enemy_idVec.begin(), enemy_idVec.end(), _enemySelection);
            if (findEnemy_id != enemy_idVec.end()) {
                checkSelection = false;
                system("clear");
            }
            else
            {
                std::cout << "ERROR: Enemy not found in list of enemies..." << std::endl;
            }
        }

        QSqlQuery query;

        query.prepare("SELECT name, hp, strength, xp_drop, element FROM enemy WHERE enemy.enemy_id=?");
        query.addBindValue(_enemySelection);
        query.exec();

        std::string name;
        int hp;
        int strength;
        int xp_drop;
        std::string element;
        while (query.next()){
            QString tempName = query.value(0).toString();
            name = tempName.toStdString();
            hp = query.value(1).toInt();
            strength = query.value(2).toInt();
            xp_drop = query.value(3).toInt();
            QString tempElement = query.value(4).toString();
            element = tempElement.toStdString();
        }

        Enemy enemy(name, hp, strength, xp_drop, element);
//        enemy.print();
        return enemy;
    }

    void printCaveEnemies() {       // Method for printing enemies in a cave
        QSqlQuery query;

        query.prepare("SELECT * FROM enemy WHERE enemy.enemy_id IN (SELECT cave_enemy.enemy_id FROM cave_enemy WHERE cave_enemy.cave_id=?)");
        query.addBindValue(_caveSelection);
        query.exec();

        _enemyIdVec = {};           // Clearing vector storing cave enemies id's

        std::cout << "LIST OF ENEMIES TO FIGHT IN THIS CAVE" << std::endl;
        std::cout << "----------------------------------------------------------------------" << std::endl;
        while (query.next()) {
                QString enemy_id = query.value(0).toString();
                QString name = query.value(1).toString();
                QString hp = query.value(2).toString();
                QString strength = query.value(3).toString();
                QString xp_drop = query.value(4).toString();
                QString element = query.value(5).toString();

                std::cout << "name=" << name.toStdString() << ", hp=" << hp.toStdString() << ", strength=" << strength.toStdString() << ", xpDrop=" << xp_drop.toStdString() << ", element=" << element.toStdString() << std::endl;


                _enemyIdVec.push_back(enemy_id.toInt());    // Storing id's of enemies from choosen cave in a vector
        }
        std::cout << "----------------------------------------------------------------------" << std::endl;
        std::cout << std::endl;
    }

    std::vector<int> getEnemyIdVec() {  // Getter method for getting vector with cave enemies id's
        return _enemyIdVec;
    }

    Enemy selectCaveEnemy(int id) {     // Method for selecting cave enemies (used for automatically figting all enemies in choosen cave)
        QSqlQuery query;

        query.prepare("SELECT name, hp, strength, xp_drop, element FROM enemy WHERE enemy.enemy_id=?");
        query.addBindValue(id);
        query.exec();

        std::string name;
        int hp;
        int strength;
        int xp_drop;
        std::string element;
        while (query.next()){
            QString tempName = query.value(0).toString();
            name = tempName.toStdString();
            hp = query.value(1).toInt();
            strength = query.value(2).toInt();
            xp_drop = query.value(3).toInt();
            QString tempElement = query.value(4).toString();
            element = tempElement.toStdString();
        }

        Enemy enemy(name, hp, strength, xp_drop, element);
        enemy.print();
        return enemy;
    }

    void printCaves() {             // Method for printing all caves
        QSqlQuery query;

        query.prepare("SELECT * FROM cave");
        query.exec();

        std::cout << "LIST OF CAVES" << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        while (query.next()) {
                QString cave_id = query.value(0).toString();
                QString name = query.value(1).toString();
                QString gold = query.value(2).toString();

                std::cout << "id=" << cave_id.toStdString() << ", name=" << name.toStdString() << ", gold=" << gold.toStdString() << std::endl;

        }
        std::cout << "----------------------------------------" << std::endl;
        std::cout << std::endl;
    }

    Cave selectCave() {
        // Vector to store cave_id's in
        std::vector<int> cave_idVec;
        int cave_id;

        // SQL query to get all cave_id's from the database
        QSqlQuery queryCheck;
        queryCheck.prepare("SELECT cave.cave_id FROM cave");
        queryCheck.exec();
        while(queryCheck.next()) {  // Loops through all cave_id's in database and appends them to cave_idVec
            cave_id = queryCheck.value(0).toInt();
            cave_idVec.push_back(cave_id);
        }

        bool checkSelection = true;
        while(checkSelection) {     // Checks if selected cave exists in list of caves
            std::cout << "Choose a cave to enter:   ";
            std::cin >> _caveSelection;
            std::cout << std::endl;

            // Checks if hero id exists
            auto findCave_id = std::find(cave_idVec.begin(), cave_idVec.end(), _caveSelection);
            if (findCave_id != cave_idVec.end()) {
                checkSelection = false;
                system("clear");
            }
            else
            {
                std::cout << "ERROR: Cave not found in list of caves..." << std::endl;
            }
        }

        QSqlQuery query;

        query.prepare("SELECT name, gold FROM cave WHERE cave.cave_id=?");
        query.addBindValue(_caveSelection);
        query.exec();

        std::string name;
        int gold;
        while (query.next()){
            QString tempName = query.value(0).toString();
            name = tempName.toStdString();
            gold = query.value(1).toInt();
        }

        Cave cave(name, gold);
        cave.print();
        return cave;
    }

    void printMagic() {             // Method for printing list of magic in the magic shop
        QSqlQuery query;

        query.prepare("SELECT * FROM magic");
        query.exec();

        std::cout << "LIST OF MAGIC TO BUY" << std::endl;
        std::cout << "-----------------------------------------------------------------------------------------------------------------------" << std::endl;
        while (query.next()) {
                QString magic_id = query.value(0).toString();
                QString name = query.value(1).toString();
                QString strength = query.value(2).toString();
                QString self_damage = query.value(3).toString();
                QString element = query.value(4).toString();
                QString required_magic_id = query.value(5).toString();
                QString price = query.value(6).toString();

                std::cout << "id=" << magic_id.toStdString() << ", name=" << name.toStdString() << ", strength=" << strength.toStdString() << ", self_damage=" << self_damage.toStdString() << ", element=" << element.toStdString() << ", required_magic_id=" << required_magic_id.toStdString() << ", price=" << price.toStdString() << std::endl;

        }
        std::cout << "-----------------------------------------------------------------------------------------------------------------------" << std::endl;
        std::cout << std::endl;
    }

    void printRequiredMagic(int required_magic_id) {        // Method for printing name of the required magic needed to purchase the wanted magic
        std::string requiredMagicName;
        std::string wantedMagicName;

        QSqlQuery query1;

        query1.prepare("SELECT magic.name FROM magic WHERE magic.magic_id=?");
        query1.addBindValue(required_magic_id);
        query1.exec();

        while(query1.next()) {
            QString tempName = query1.value(0).toString();
            requiredMagicName = tempName.toStdString();
        }

        QSqlQuery query2;

        query2.prepare("SELECT magic.name FROM magic WHERE magic.magic_id=?");
        query2.addBindValue(_buyMagicSelection);
        query2.exec();

        while(query2.next()) {
            QString tempName = query2.value(0).toString();
            wantedMagicName = tempName.toStdString();
        }

        std::cout << "Acquire " << requiredMagicName << " to buy " << wantedMagicName << std::endl;
        std::cout << std::endl;
    }

    Magic buyMagic() {
        // Vector to store magic_id's in
        std::vector<int> magic_idVec;
        int magic_id;

        // SQL query to get all magic_id's from the database
        QSqlQuery queryCheck;
        queryCheck.prepare("SELECT magic.magic_id FROM magic");
        queryCheck.exec();
        while(queryCheck.next()) {  // Loops through all magic_id's in database and appends them to magic_idVec
            magic_id = queryCheck.value(0).toInt();
            magic_idVec.push_back(magic_id);
        }

        bool checkSelection = true;
        while(checkSelection) {     // Checks if selected magic exists in list of magic
            std::cout << "Choose the magic you want to buy by writing the magic ID:   ";
            std::cin >> _buyMagicSelection;
            std::cout << std::endl;

            // Checks if magic_id exists
            auto findMagic_id = std::find(magic_idVec.begin(), magic_idVec.end(), _buyMagicSelection);
            if (findMagic_id != magic_idVec.end()) {
                checkSelection = false;
                system("clear");
            }
            else
            {
                std::cout << "ERROR: Magic not found in list of magic..." << std::endl;
            }
        }

        QSqlQuery query;

        query.prepare("SELECT magic_id, name, strength, self_damage, element, required_magic_id, price FROM magic WHERE magic.magic_id=?");
        query.addBindValue(_buyMagicSelection);
        query.exec();

        int magicId;
        std::string name;
        int strength;
        int self_damage;
        std::string element;
        int required_magic_id;
        int price;
        while (query.next()){
            magicId = query.value(0).toInt();
            QString tempName = query.value(1).toString();
            name = tempName.toStdString();
            strength = query.value(2).toInt();
            self_damage = query.value(3).toInt();
            QString tempElement = query.value(4).toString();
            element = tempElement.toStdString();
            required_magic_id = query.value(5).toInt();
            price = query.value(6).toInt();
        }

        Magic magic(magicId, name, strength, self_damage, element, required_magic_id, price);
        magic.print();

        return magic;
    }

    Magic selectMagic() {           // Method for selecting a magic to use in a fight
        // Vector to store magic_id's in
        std::vector<int> magic_idVec;
        int magic_id;

        // SQL query to get all magic_id's from the database
        QSqlQuery queryCheck;
        queryCheck.prepare("SELECT hero_magic.magic_id FROM hero_magic WHERE hero_magic.hero_id=?");
        queryCheck.addBindValue(_heroSelection);
        queryCheck.exec();
        while(queryCheck.next()) {  // Loops through all magic_id's in database and appends them to magic_idVec
            magic_id = queryCheck.value(0).toInt();
            magic_idVec.push_back(magic_id);
        }

        bool checkSelection = true;
        while(checkSelection) {     // Checks if selected magic exists in list of magic
            std::cout << "Choose a magic to use in fight by writing the magic ID:   ";
            std::cin >> _magicSelection;
            std::cout << std::endl;

            // Checks if magic_id exists
            auto findMagic_id = std::find(magic_idVec.begin(), magic_idVec.end(), _magicSelection);
            if (findMagic_id != magic_idVec.end()) {
                checkSelection = false;
            }
            else {
                std::cout << "ERROR: Magic not found in list of acquired magic..." << std::endl;
            }
        }

        QSqlQuery query;

        query.prepare("SELECT magic_id, name, strength, self_damage, element, required_magic_id, price FROM magic WHERE magic.magic_id=?");
        query.addBindValue(_magicSelection);
        query.exec();

        int magicId;
        std::string name;
        int strength;
        int self_damage;
        std::string element;
        int required_magic_id;
        int price;
        while (query.next()){
            magicId = query.value(0).toInt();
            QString tempName = query.value(1).toString();
            name = tempName.toStdString();
            strength = query.value(2).toInt();
            self_damage = query.value(3).toInt();
            QString tempElement = query.value(4).toString();
            element = tempElement.toStdString();
            required_magic_id = query.value(5).toInt();
            price = query.value(6).toInt();
        }

        Magic magic(magicId, name, strength, self_damage, element, required_magic_id, price);
        return magic;
    }

    int getHeroMagicCount() {           // Method for checking if hero has any magic acquired
        QSqlQuery queryCount;

        queryCount.prepare("SELECT count(hero_magic.magic_id) FROM hero_magic WHERE hero_magic.hero_id=?");
        queryCount.addBindValue(_heroSelection);
        queryCount.exec();

        while(queryCount.next()) {
            _heroMagicCount = queryCount.value(0).toInt();
        }

        return _heroMagicCount;
    }

    void printAcquiredMagic() {         // Method for printing a list of heroes acquired magic
        QSqlQuery query;

        query.prepare("SELECT magic.magic_id, name, strength, self_damage, element FROM magic INNER JOIN hero_magic ON magic.magic_id=hero_magic.magic_id WHERE hero_magic.hero_id=?");
        query.addBindValue(_heroSelection);
        query.exec();

        std::cout << "LIST OF ACQUIRED MAGIC" << std::endl;
        std::cout << "------------------------------------------------------------------------" << std::endl;
        while(query.next()) {
            QString magic_id = query.value(0).toString();
            QString name = query.value(1).toString();
            QString strength = query.value(2).toString();
            QString self_damage = query.value(3).toString();
            QString element = query.value(4).toString();

            std::cout << "id=" << magic_id.toStdString() << ", name=" << name.toStdString() << ", strength=" << strength.toStdString() << ", self_damage=" << self_damage.toStdString() << ", element=" << element.toStdString() << std::endl;

        }
        std::cout << "------------------------------------------------------------------------" << std::endl;
        std::cout << std::endl;
    }

    bool checkHeroMagics(int magicId) {     // Method for checking if hero already has the magic they want to buy
        bool checkId = false;

        QSqlQuery query;

        query.prepare("SELECT hero_magic.magic_id FROM hero_magic WHERE hero_magic.hero_id=?");
        query.addBindValue(_heroSelection);
        query.exec();

        int magic_id;
        while(query.next()) {
            magic_id = query.value(0).toInt();
            if(magicId == magic_id) {
                checkId = true;
                break;
            }
        }

        return checkId;
    }

    double checkElements(std::string magicElement, std::string enemyElement) {
        double damageBoost;

        if((magicElement=="Water" && enemyElement=="Fire") || (magicElement=="Fire" && enemyElement=="Metal") || (magicElement=="Metal" && enemyElement=="Wood") || (magicElement=="Wood" && enemyElement=="Earth") || (magicElement=="Earth" && enemyElement=="Water")) {
            return damageBoost = 2;
        }
        else if((enemyElement=="Water" && magicElement=="Fire") || (enemyElement=="Fire" && magicElement=="Metal") || (enemyElement=="Metal" && magicElement=="Wood") || (enemyElement=="Wood" && magicElement=="Earth") || (enemyElement=="Earth" && magicElement=="Water")) {
            return damageBoost = 0.5;
        }
        else {
            return damageBoost = 1;
        }
    }

    void updateHeroMagics(int magicId) {
        QSqlQuery query;

        query.prepare("INSERT INTO hero_magic(hero_id, magic_id) VALUES(?, ?)");
        query.addBindValue(_heroSelection);
        query.addBindValue(magicId);
        query.exec();
    }

    void updateHero(int heroXp, int heroLevel, int heroHp, int heroStrength, int heroGold, int heroMagicNiveau) {  // Method for updating heroes stats in the database (used when saving a game)
        QSqlQuery query;

        query.prepare("UPDATE hero SET xp=?, level=?, hp=?, strength=?, gold=?, magic_niveau=? WHERE hero.hero_id=?");
        query.addBindValue(heroXp);
        query.addBindValue(heroLevel);
        query.addBindValue(heroHp);
        query.addBindValue(heroStrength);
        query.addBindValue(heroGold);
        query.addBindValue(heroMagicNiveau);
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
