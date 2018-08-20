#ifndef MYSQLDBCONNECT_H
#define MYSQLDBCONNECT_H

#include <QtSql>

class MySQLDBConnect
{
public:
    //Default Constructor- Establishes connection with the MySQL server by
    //accepting HostName, DBName, UserName, password as parameters
    MySQLDBConnect(QString HostName, QString DBName, QString UserName,
                   QString password);

    //Checks whether the Database is Open
    bool isDBOpen();

    //Destructor
    ~MySQLDBConnect();

    void CloseDatabase();

private:
    QSqlDatabase db;

};

#endif // MYSQLDBCONNECT_H
