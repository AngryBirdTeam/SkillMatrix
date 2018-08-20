#include "MySQlDBConnect.h"
#include<QDebug>

// MySQLDBConnect - Default Constructor of the MySQLDBConnect class
MySQLDBConnect::MySQLDBConnect(QString HostName,QString DBName,QString UserName,
                               QString password)
{
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName(HostName);
    db.setDatabaseName(DBName);
    db.setUserName(UserName);
    db.setPassword(password);   // set password as that of your db

    qDebug() << QSqlDatabase::drivers();

    db.open();
}

// isDBOpen - Check whether the Database is Open
bool MySQLDBConnect::isDBOpen()
{
    qDebug() << "------------------------------DB Open is " << db.isOpen();

    return db.isOpen();
}

void MySQLDBConnect::CloseDatabase()
{
    db.close();
}

// ~MySQLDBConnect - Destructor
MySQLDBConnect::~MySQLDBConnect()
{

}


