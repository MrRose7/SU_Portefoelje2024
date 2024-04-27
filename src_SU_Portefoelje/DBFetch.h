#ifndef DBFETCH_H
#define DBFETCH_H
#include <QCoreApplication>
#include <QtSql>
#include <QSqlDatabase>
#include <iostream>

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

};



#endif // DBFETCH_H
