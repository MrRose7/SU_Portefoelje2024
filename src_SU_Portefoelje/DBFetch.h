#ifndef DBFETCH_H
#define DBFETCH_H
#include <QCoreApplication>
#include <QtSql>
#include <QSqlDatabase>
#include <iostream>
#include "hero.h"

/* Class to fetch data from database*/
class DBFetch {
private:
//    std::string _name = "noHero";
//    int _xp = 0;
//    int _level = 0;
//    int _hp = 0;
//    int _strength = 0;

public:
    void dbInit() {         // Method for initialising database
        QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
        db.setHostName("localhost");
        db.setDatabaseName("su_portefoelje2024");
        db.setUserName("lucas");        // Change to username
        db.setPassword("password");     // Change to password
        db.open();
    }

    void printHeroes() {
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

    void selectHero() {         // VIKRER IKKE
        int selection;
        std::cout << "Chose a Hero to plays as, by writing the heroes ID:   ";
        std::cin >> selection;
        std::cout << std::endl;

        QSqlQuery query;

        query.prepare("SELECT name, xp, level, hp, strength FROM hero WHERE hero.hero_id=?");
        query.addBindValue(selection);
        query.exec();

        std::string name;
        int xp;
        int level;
        int hp;
        int strength;
        while (query.next()){
            QString tempName = query.value(0).toString();
            name = tempName.toStdString();
            xp = query.value(1).toInt();
            level = query.value(2).toInt();
            hp = query.value(3).toInt();
            strength = query.value(4).toInt();
        }

        Hero hero(name, xp, level, hp, strength);
        hero.print();
    }

};



#endif // DBFETCH_H
